//
// This class manages data and files used
// in the Delay25 calibration
//
//
//
//

#include "CalibFormats/SiPixelObjects/interface/PixelDelay25Calib.h"
#include <iostream>
#include <assert.h>
#include <map>
#include <sstream>

using namespace pos;

using namespace std;

PixelDelay25Calib::PixelDelay25Calib(vector< vector<string> > &tableMat) : 
  PixelCalibBase(),
  PixelConfigBase("","","")
{
  std::cout<<"PixelDelay25Calib::PixelDelay25Calib"<<std::endl;
  std::map<std::string , int > colM;
  std::vector<std::string > colNames;
  /**

     View's name: CONF_KEY_PIXEL_CALIB_MV
     CONFIG_KEY_ID                             NOT NULL NUMBER(38)
     CONFG_KEY                                 NOT NULL VARCHAR2(80)
     VERSION                                            VARCHAR2(40)
     KIND_OF_COND                              NOT NULL VARCHAR2(40)
     RUN_TYPE                                           VARCHAR2(40)
     RUN_NUMBER                                         NUMBER(38)
     CALIB_OBJ_DATA_FILE                       NOT NULL VARCHAR2(200)
     CALIB_OBJ_DATA_CLOB                       NOT NULL CLOB
  */

  colNames.push_back("CONFIG_KEY_ID"      );
  colNames.push_back("CONFG_KEY"          );
  colNames.push_back("VERSION"            );
  colNames.push_back("KIND_OF_COND"       );
  colNames.push_back("RUN_TYPE"           );
  colNames.push_back("RUN_NUMBER"         );
  colNames.push_back("CALIB_OBJ_DATA_FILE");
  colNames.push_back("CALIB_OBJ_DATA_CLOB");
  
  for(unsigned int c = 0 ; c < tableMat[0].size() ; c++)
    {
      for(unsigned int n=0; n<colNames.size(); n++)
	{
	  if(tableMat[0][c] == colNames[n])
	    {
	      colM[colNames[n]] = c;
	      break;
	    }
	}
    }//end for
  for(unsigned int n=0; n<colNames.size(); n++)
    {
      if(colM.find(colNames[n]) == colM.end())
	{
	  std::cerr << "[PixelMaxVsf::PixelMaxVsf()]\tCouldn't find in the database the column with name " << colNames[n] << std::endl;
	  assert(0);
	}
    }

  
  std::istringstream in ;
  in.str(tableMat[1][colM["CALIB_OBJ_DATA_CLOB"]]) ;
  
  //Read initial SDa and RDa values, ranges,
  //and grid step size from file
  
  std::string tmp;

  in >> tmp;

  assert(tmp=="Mode:");
  in >> mode_;

  in >> tmp;

  assert(tmp=="Portcards:");
  in >> tmp;
  if(tmp=="All")
    {
      allPortcards_ = true;
    } else {
    allPortcards_ = false;
  }
  while (tmp!="AllModules:")
    {
      portcardNames_.insert(tmp);
      in >> tmp;
    }

  assert(tmp=="AllModules:");
  in >> allModules_;

  in >> tmp;

  assert(tmp=="OrigSDa:");
  in >> origSDa_;

  in >> tmp;

  assert(tmp=="OrigRDa:");
  in >> origRDa_;

  in >> tmp;

  assert(tmp=="Range:");
  in >> range_;

  in >> tmp;

  assert(tmp=="GridSize:");
  in >> gridSize_;

  in >> tmp;
  assert(tmp=="Tests:");
  in >> numTests_;

  in >> tmp;
  if(tmp=="Commands:") {
    in >> commands_;
  } else {
    commands_=0;
  }

  //Number of steps in the grid
  gridSteps_ = range_/gridSize_;
}


PixelDelay25Calib::PixelDelay25Calib(std::string filename) : 
  PixelCalibBase(),
  PixelConfigBase("","",""){

  //std::cout<<"PixelDelay25Calib::PixelDelay25Calib"<<std::endl;
  
  std::ifstream in(filename.c_str());
  
  if(!in.good()){
    std::cout<<"Could not open: "<<filename<<std::endl;
    assert(0);
  }
  else {
    std::cout<<"Opened: "<<filename<<std::endl;
  }

  //Read initial SDa and RDa values, ranges,
  //and grid step size from file
  
  std::string tmp;

  in >> tmp;

  assert(tmp=="Mode:");
  in >> mode_;

  //cout << "[PixelDelay25Calib::PixelDelay25Calib]:mode_="<<mode_<<endl;

  in >> tmp;

  assert(tmp=="Portcards:");
  in >> tmp;
  if(tmp=="All")
    {
      allPortcards_ = true;
    } else {
      allPortcards_ = false;
    }
  while (tmp!="AllModules:")
    {
      portcardNames_.insert(tmp);
      in >> tmp;
    }

  assert(tmp=="AllModules:");
  in >> allModules_;

  in >> tmp;

  assert(tmp=="OrigSDa:");
  in >> origSDa_;

  in >> tmp;

  assert(tmp=="OrigRDa:");
  in >> origRDa_;

  in >> tmp;

  assert(tmp=="Range:");
  in >> range_;

  in >> tmp;

  assert(tmp=="GridSize:");
  in >> gridSize_;

  in >> tmp;
  assert(tmp=="Tests:");
  in >> numTests_;

  in >> tmp;
  if(tmp=="Commands:") {
    in >> commands_;
  } else {
    commands_=0;
  }

  in.close();

  //Number of steps in the grid
  gridSteps_ = range_/gridSize_;

}

PixelDelay25Calib::~PixelDelay25Calib() {
}

void PixelDelay25Calib::openFiles(std::string portcardName, std::string moduleName, std::string path) {
  if (path!="") path+="/";
  graph_ = path+"graph_"+portcardName+"_"+moduleName+".dat";
  graphout_.open(graph_.c_str());
  return;
}

void PixelDelay25Calib::writeSettings(std::string portcardName, std::string moduleName) {
  graphout_ << "Portcard: " << portcardName << endl;
  graphout_ << "Module: " << moduleName << endl;
  graphout_ << "SDaOrigin: " << origSDa_ << endl;
  graphout_ << "RDaOrigin: " << origRDa_ << endl;
  graphout_ << "SDaRange: " << range_ << endl;
  graphout_ << "RDaRange: " << range_ << endl;
  graphout_ << "GridSize: " << gridSize_ << endl;
  graphout_ << "Tests: " << numTests_ << endl;
  return;
}

void PixelDelay25Calib::writeFiles( std::string tmp ) {
  graphout_ << tmp << endl;
  return;
}

void PixelDelay25Calib::writeFiles( int currentSDa, int currentRDa, int number ) {
  graphout_ << currentSDa << " " << currentRDa << " " << number << endl;
  return;
}

void PixelDelay25Calib::closeFiles() {
  graphout_.close();
  return;
}

void PixelDelay25Calib::writeASCII(std::string dir) const {


  //FIXME this is not tested for all the use cases...

  if (dir!="") dir+="/";
  std::string filename=dir+"delay25.dat";
  std::ofstream out(filename.c_str());

  out << "Mode: "<<mode_<<endl;
  
  out << "Portcards:" <<endl;

  std::set<std::string>::const_iterator i=portcardNames_.begin();
  while (i!=portcardNames_.end()) {
    out << *i << endl;
    ++i;
  }

  out << "AllModules:" <<endl;
  if (allModules_) {
    out << "1" <<endl;
  } else {
    out << "0" <<endl;
  }

  out << "OrigSDa:"<<endl;
  out << origSDa_<<endl;
  
  out << "OrigRDa:"<<endl;
  out << origRDa_<<endl;
  
  out << "Range:"<<endl;
  out << range_<<endl;
  
  out << "GridSize:"<<endl;
  out << gridSize_<<endl;
  
  out << "Tests:"<<endl;
  out << numTests_<<endl;

  out << "Commands:"<<endl;
  out << commands_<<endl;
  
  out.close();
}



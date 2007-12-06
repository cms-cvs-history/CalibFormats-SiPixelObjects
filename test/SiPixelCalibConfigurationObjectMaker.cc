// -*- C++ -*-
//
// Package:    SiPixelCalibConfigurationObjectMaker
// Class:      SiPixelCalibConfigurationObjectMaker
// 
/**\class SiPixelCalibConfigurationObjectMaker SiPixelCalibConfigurationObjectMaker.cc CalibFormats/SiPixelObjects/src/SiPixelCalibConfigurationObjectMaker.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Freya Blekman
//         Created:  Wed Sep 19 13:43:52 CEST 2007
// $Id: SiPixelCalibConfigurationObjectMaker.cc,v 1.4 2007/11/19 10:49:59 fblekman Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CalibFormats/SiPixelObjects/interface/SiPixelCalibConfiguration.h"
#include "CalibFormats/SiPixelObjects/interface/PixelCalibConfiguration.h"

#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include <string>
//
// class decleration
//

class SiPixelCalibConfigurationObjectMaker : public edm::EDAnalyzer {
   public:
      explicit SiPixelCalibConfigurationObjectMaker(const edm::ParameterSet&);
      ~SiPixelCalibConfigurationObjectMaker();

  virtual void beginJob(const edm::EventSetup&) {;}
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() {;}


   private:

      // ----------member data ---------------------------
   std::string inputfilename;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SiPixelCalibConfigurationObjectMaker::SiPixelCalibConfigurationObjectMaker(const edm::ParameterSet& iConfig):
  inputfilename( iConfig.getUntrackedParameter<std::string>( "inputFileName","/afs/cern.ch/cms/Tracker/Pixel/forward/ryd/calib_070106d.dat" ) )

{
   //now do what ever initialization is needed
  ::putenv("CORAL_AUTH_USER=testuser");
  ::putenv("CORAL_AUTH_PASSWORD=test"); 
}


SiPixelCalibConfigurationObjectMaker::~SiPixelCalibConfigurationObjectMaker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

void SiPixelCalibConfigurationObjectMaker::analyze(const edm::Event&, const edm::EventSetup&){

  pos::PixelCalibConfiguration fancyCalib(inputfilename);
  SiPixelCalibConfiguration *myCalib = new SiPixelCalibConfiguration(fancyCalib);
   
  std::string newtag = inputfilename.substr(inputfilename.rfind("/")+1);// only take file name (lets hope that is enough..
   std::cout << "filling content of  " << inputfilename << " in db with tag " << newtag << std::endl;
   
   edm::Service<cond::service::PoolDBOutputService> poolDbService;
   
   if(poolDbService.isAvailable()){
     try{
       if(poolDbService->isNewTagRequest("SiPixelCalibConfigurationRcd") ){
	 poolDbService->createNewIOV<SiPixelCalibConfiguration>(myCalib,poolDbService->endOfTime(), "SiPixelCalibConfigurationRcd");
       }
       else{
	 poolDbService->appendSinceTime<SiPixelCalibConfiguration>(myCalib,poolDbService->currentTime(), "SiPixelCalibConfigurationRcd");
       }
     }
     catch(const cond::Exception &er){
       edm::LogError("SiPixelCalibConfigurationObjectMaker") << er.what() << std::endl;
     }
     catch(const std::exception &er){
       edm::LogError("SiPixelCalibConfigurationObjectMaker") << "standard error caught: " << er.what() << std::endl;
     }
     catch(...){
       edm::LogError("SiPixelCalibConfigurationObjectMaker") << " caught unknown error, please check what you're doing!" << std::endl;
     }
   }
}


//define this as a plug-in
DEFINE_FWK_MODULE(SiPixelCalibConfigurationObjectMaker);

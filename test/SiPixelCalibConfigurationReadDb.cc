// -*- C++ -*-
//
// Package:    SiPixelCalibConfigurationReadDb
// Class:      SiPixelCalibConfigurationReadDb
// 
/**\class SiPixelCalibConfigurationReadDb SiPixelCalibConfigurationReadDb.cc CalibFormats/SiPixelObjects/test/SiPixelCalibConfigurationReadDb.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Freya Blekman
//         Created:  Thu Sep 20 12:13:20 CEST 2007
// $Id: SiPixelCalibConfigurationReadDb.cc,v 1.4 2007/10/03 13:45:00 fblekman Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "CalibFormats/SiPixelObjects/interface/SiPixelCalibConfiguration.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CondFormats/DataRecord/interface/SiPixelCalibConfigurationRcd.h"
#include <iostream>
//
// class decleration
//

class SiPixelCalibConfigurationReadDb : public edm::EDAnalyzer {
   public:
      explicit SiPixelCalibConfigurationReadDb(const edm::ParameterSet&);
      ~SiPixelCalibConfigurationReadDb();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
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
SiPixelCalibConfigurationReadDb::SiPixelCalibConfigurationReadDb(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


SiPixelCalibConfigurationReadDb::~SiPixelCalibConfigurationReadDb()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
SiPixelCalibConfigurationReadDb::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   LogInfo("") << " examining SiPixelCalibConfiguration database object..." << std::endl;

   ESHandle<SiPixelCalibConfiguration> calib;
   iSetup.get<SiPixelCalibConfigurationRcd>().get(calib);
   //   std::cout <<*calib<< std::endl;
   std::cout << "number of triggers: " << calib->NTriggers() << std::endl;
   std::vector<short> vcalvalues= calib->VCalValues();
   std::cout << "number of VCAL: " << vcalvalues.size() << std::endl;
   for(uint32_t i=0; i<vcalvalues.size(); ++i){
     std::cout << "Vcal values " << i << "," << i+1 << " : " << vcalvalues[i] << "," ;
     ++i;
     if(i<vcalvalues.size())
       std::cout << vcalvalues[i];
     std::cout << std::endl;
   }
   std::cout << "column patterns:" << std::endl;
   for(uint32_t i=0; i<calib->ColumnPattern().size(); ++i){
     if(calib->ColumnPattern()[i]!=-1)
       std::cout << calib->ColumnPattern()[i] ;
     if(i!=0)
       std::cout << " ";
     if(calib->ColumnPattern()[i]==-1)
       std::cout << "- " ;
   } 
   std::cout << std::endl;
   std::cout << "row patterns:" << std::endl;
   for(uint32_t i=0; i<calib->RowPattern().size(); ++i){
     if(calib->RowPattern()[i]!=-1)
       std::cout << calib->RowPattern()[i] ;
     if(i!=0)
       std::cout << " ";
     if(calib->RowPattern()[i]==-1)
       std::cout << "- ";
   }
   std::cout << std::endl;
   std::cout << "list of rocs: " << std::endl;
   for(uint32_t i=0; i<calib->ROCIds().size();++i){
     std::cout << calib->ROCIds()[i]  ;
     ++i;
     if(i<calib->ROCIds().size())
       std::cout << " \t"<< calib->ROCIds()[i];
     ++i;
     if(i<calib->ROCIds().size())
       std::cout << " \t"<< calib->ROCIds()[i];
     std::cout << std::endl;
   }
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
SiPixelCalibConfigurationReadDb::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SiPixelCalibConfigurationReadDb::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(SiPixelCalibConfigurationReadDb);

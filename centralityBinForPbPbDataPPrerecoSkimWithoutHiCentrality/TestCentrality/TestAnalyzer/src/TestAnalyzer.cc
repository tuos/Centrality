// -*- C++ -*-
//
// Package:    TestAnalyzer
// Class:      TestAnalyzer
// 
/**\class TestAnalyzer TestAnalyzer.cc TestCentrality/TestAnalyzer/src/TestAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo,,,
//         Created:  Sun May 24 04:52:05 CEST 2015
// $Id$
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

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "RecoHI/HiCentralityAlgos/interface/CentralityProvider.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TH1.h>
#include <TH1D.h>
//
// class declaration
//

class TestAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TestAnalyzer(const edm::ParameterSet&);
      ~TestAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

   edm::Service<TFileService> fs;
   CentralityProvider * centrality_;
   TH1D* hcent;
   TH1D* hhf;
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
TestAnalyzer::TestAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


TestAnalyzer::~TestAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TestAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   centrality_=0;
   if(!centrality_) centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup); 
   const reco::Centrality* centrality = centrality_->raw();
   int bin = centrality_->getBin();
   //cout<<"Centrality bin = "<<bin<<",  HF energy = "<<centrality->EtHFtowerSum()<<endl;
   if(bin>119&&bin<160){
   hcent->Fill(bin);
   hhf->Fill(centrality->EtHFtowerSum());
   }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TestAnalyzer::beginJob()
{
  TH1D::SetDefaultSumw2();
  hcent = fs->make<TH1D>("centrality","PbPb Centrality, 5_3_20",200,0,200);
  hhf = fs->make<TH1D>("hf","HF, 5_3_20",100000,0,1000);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TestAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TestAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TestAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TestAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TestAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TestAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestAnalyzer);

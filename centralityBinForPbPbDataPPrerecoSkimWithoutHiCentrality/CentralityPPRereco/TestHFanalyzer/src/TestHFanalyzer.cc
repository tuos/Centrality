// -*- C++ -*-
//
// Package:    TestHFanalyzer
// Class:      TestHFanalyzer
// 
/**\class TestHFanalyzer TestHFanalyzer.cc TestCentrality/TestHFanalyzer/src/TestHFanalyzer.cc

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
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
//
// class declaration
//

class TestHFanalyzer : public edm::EDAnalyzer {
   public:
      explicit TestHFanalyzer(const edm::ParameterSet&);
      ~TestHFanalyzer();

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
   TH1D* hedge;
   TH1D* hcheckcent;
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
TestHFanalyzer::TestHFanalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


TestHFanalyzer::~TestHFanalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TestHFanalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   centrality_=0;
   if(!centrality_) centrality_ = new CentralityProvider(iSetup);
   centrality_->newEvent(iEvent,iSetup); 
   const reco::Centrality* centrality = centrality_->raw();
   int bin = centrality_->getBin();
   double edge = centrality_->lowEdge();
   if(bin==119||bin==159) cout<<"!!! Centrality bin = "<<bin<<", lowEdge = "<<edge<<",  HF energy = "<<centrality->EtHFtowerSum()<<endl;
   else cout<<"Centrality bin = "<<bin<<", lowEdge = "<<edge<<",  HF energy = "<<centrality->EtHFtowerSum()<<endl;
   if(bin>119&&bin<160){
   hcent->Fill(bin);
   hhf->Fill(centrality->EtHFtowerSum());
   hedge->SetBinContent(bin+1, edge);
   }


// towerMaker
    double etHFtowerSumPlus=0;
    double etHFtowerSumMinus=0;
    double etHFtowerSum=0;
    Handle<CaloTowerCollection> towers;
    iEvent.getByLabel("towerMaker",towers);
    for( size_t i = 0; i<towers->size(); ++ i){
       const CaloTower & tower = (*towers)[ i ];
       double eta = tower.eta();
       bool isHF = tower.ietaAbs() > 29;
          if(isHF && eta > 0){
            etHFtowerSumPlus += tower.pt();
          }
          if(isHF && eta < 0){
            etHFtowerSumMinus += tower.pt();
          }
    }
    etHFtowerSum=etHFtowerSumPlus + etHFtowerSumMinus;
    cout<<"calculated HF energy = "<<etHFtowerSum<<", HF energy from centrality = "<<centrality->EtHFtowerSum()<<endl;

    if(etHFtowerSum>48.2599&&etHFtowerSum<216.241){
      hcheckcent->Fill(bin);
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
TestHFanalyzer::beginJob()
{
  TH1D::SetDefaultSumw2();
  hcent = fs->make<TH1D>("centrality","PbPb Centrality, 5_3_20",200,0,200);
  hhf = fs->make<TH1D>("hf","HF, 5_3_20",100000,0,1000);
  hedge = fs->make<TH1D>("edge","PbPb Centrality, 5_3_20",202,0,202);
  hcheckcent = fs->make<TH1D>("checkcentrality","PbPb Centrality, 5_3_20",200,0,200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TestHFanalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
TestHFanalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
TestHFanalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
TestHFanalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
TestHFanalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TestHFanalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestHFanalyzer);

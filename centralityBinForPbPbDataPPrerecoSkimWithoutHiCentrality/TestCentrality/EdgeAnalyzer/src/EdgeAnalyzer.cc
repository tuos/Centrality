// -*- C++ -*-
//
// Package:    EdgeAnalyzer
// Class:      EdgeAnalyzer
// 
/**\class EdgeAnalyzer EdgeAnalyzer.cc TestCentrality/EdgeAnalyzer/src/EdgeAnalyzer.cc

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

class EdgeAnalyzer : public edm::EDAnalyzer {
   public:
      explicit EdgeAnalyzer(const edm::ParameterSet&);
      ~EdgeAnalyzer();

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
EdgeAnalyzer::EdgeAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


EdgeAnalyzer::~EdgeAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
EdgeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
EdgeAnalyzer::beginJob()
{
  TH1D::SetDefaultSumw2();
  hcent = fs->make<TH1D>("centrality","PbPb Centrality, 5_3_20",200,0,200);
  hhf = fs->make<TH1D>("hf","HF, 5_3_20",100000,0,1000);
  hedge = fs->make<TH1D>("edge","PbPb Centrality, 5_3_20",202,0,202);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EdgeAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
EdgeAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
EdgeAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
EdgeAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
EdgeAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EdgeAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(EdgeAnalyzer);

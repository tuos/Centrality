// -*- C++ -*-
//
// Package:    CentralityPPrereco75X/FindEdges
// Class:      FindEdges
// 
/**\class FindEdges FindEdges.cc CentralityPPrereco75X/FindEdges/plugins/FindEdges.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sun, 06 Mar 2016 23:22:13 GMT
//
//


// system include files
#include <memory>
#include <iostream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TH1.h>
#include <TH1D.h>
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "CondFormats/HIObjects/interface/CentralityTable.h"
#include "CondFormats/DataRecord/interface/HeavyIonRcd.h"
#include "FWCore/Framework/interface/ESHandle.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class FindEdges : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit FindEdges(const edm::ParameterSet&);
      ~FindEdges();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
   edm::Service<TFileService> fs;
   TH1D* hcent;
   TH1D* hhf;
   TH1D* hedge;
edm::EDGetTokenT<reco::Centrality> centralityToken_;
edm::EDGetTokenT<int> centralityBinToken_;

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
FindEdges::FindEdges(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
centralityToken_ = consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"));
centralityBinToken_ = consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinSrc"));

}


FindEdges::~FindEdges()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
FindEdges::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

edm::Handle<reco::Centrality> centrality;
iEvent.getByToken(centralityToken_, centrality);
edm::Handle<int> cbin;
iEvent.getByToken(centralityBinToken_, cbin);
    edm::ESHandle<CentralityTable> centDB;
    iSetup.get<HeavyIonRcd>().get("HFtowers",centDB);
    //int nCentBins = centDB->m_table.size();
    //cout<<"nCentBins = "<<nCentBins<<endl;
int hiBin = *cbin;
cout<<"bin = "<<*cbin<<" ,  hf = "<<centrality->EtHFtowerSum()<<" , lowEdge = "<<centDB->m_table[hiBin].bin_edge<<endl;
hcent->Fill(hiBin);
hhf->Fill(centrality->EtHFtowerSum());
hedge->SetBinContent(hiBin+1, centDB->m_table[hiBin].bin_edge);

  cout<<endl;
  for(unsigned int i = 0; i < centDB->m_table.size(); ++i){
    cout<<centDB->m_table[i].bin_edge<<", ";
  }
  cout<<endl;

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
FindEdges::beginJob()
{
  TH1D::SetDefaultSumw2();
  hcent = fs->make<TH1D>("centrality","PbPb Centrality, 758p3",200,0,200);
  hhf = fs->make<TH1D>("hf","HF, 5_3_20",80000,0,8000);
  hedge = fs->make<TH1D>("edge","PbPb Centrality, 758p3",202,0,202);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
FindEdges::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FindEdges::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(FindEdges);

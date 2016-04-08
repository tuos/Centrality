// -*- C++ -*-
//
// Package:    AnalysisRECO/AnalysisEnergyHF
// Class:      AnalysisEnergyHF
// 
/**\class AnalysisEnergyHF AnalysisEnergyHF.cc AnalysisRECO/AnalysisEnergyHF/plugins/AnalysisEnergyHF.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Fri, 01 Apr 2016 14:02:37 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TH1.h>
#include <TH1D.h>

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class AnalysisEnergyHF : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit AnalysisEnergyHF(const edm::ParameterSet&);
      ~AnalysisEnergyHF();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
   edm::Service<TFileService> fs;
   TH1D* hLumiID;
   TH1D* hEvtID;
   TH1D* hHF;
   TH1D* hHFrechit;
   //TH1D* hCent;
   TH1D* hVz;
   TH1D* hVx;
   TH1D* hVy;
   Int_t evtNum;
   bool doPPRECO_;
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
AnalysisEnergyHF::AnalysisEnergyHF(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   doPPRECO_ = iConfig.getParameter<bool>("doPPRECO");
}


AnalysisEnergyHF::~AnalysisEnergyHF()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
AnalysisEnergyHF::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

    evtNum++;

    double etHFtowerSumPlus = 0;
    double etHFtowerSumMinus = 0;
    double etHFtowerSum = 0;
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
    etHFtowerSum = etHFtowerSumPlus + etHFtowerSumMinus;


    double etHFhitSumPlus = 0;
    double etHFhitSumMinus = 0;
    double etHFhitSum = 0;
    Handle<HFRecHitCollection> hits;
    iEvent.getByLabel("hfreco",hits);
    for( size_t ihit = 0; ihit<hits->size(); ++ ihit){
    const HFRecHit & rechit = (*hits)[ ihit ];
       if(rechit.id().ieta() > 0)
         etHFhitSumPlus += rechit.energy();
       if(rechit.id().ieta() < 0)
         etHFhitSumMinus += rechit.energy();
     }
     etHFhitSum = etHFhitSumPlus + etHFhitSumMinus;


  hHF->SetBinContent(evtNum, etHFtowerSum); 
  hHFrechit->SetBinContent(evtNum, etHFhitSum); 
  //hCent->SetBinContent(evtNum, bin); 
  hLumiID->SetBinContent(evtNum, iEvent.luminosityBlock());
  hEvtID->SetBinContent(evtNum, iEvent.id().event()); 

  edm::Handle<std::vector<reco::Vertex>> vertex;
  if(doPPRECO_)
    iEvent.getByLabel("offlinePrimaryVertices", vertex);
  else
    iEvent.getByLabel("hiSelectedVertex", vertex);
  hVz->SetBinContent(evtNum, vertex->begin()->z());  
  hVx->SetBinContent(evtNum, vertex->begin()->x());  
  hVy->SetBinContent(evtNum, vertex->begin()->y());  


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
AnalysisEnergyHF::beginJob()
{
  TH1D::SetDefaultSumw2();
  hLumiID = fs->make<TH1D>("hLumiID","cmssw 758p4",100,0,100);
  hEvtID = fs->make<TH1D>("hEvtID","cmssw 758p4",100,0,100);
  hHF = fs->make<TH1D>("hHF","cmssw 758p4",100,0,100);
  hHFrechit = fs->make<TH1D>("hHFrechit","cmssw 758p4",100,0,100);
  //hCent = fs->make<TH1D>("hCent","cmssw 758p4",100,0,100);
  hVz = fs->make<TH1D>("hVz","cmssw 758p4",100,0,100);
  hVx = fs->make<TH1D>("hVx","cmssw 758p4",100,0,100);
  hVy = fs->make<TH1D>("hVy","cmssw 758p4",100,0,100);
  evtNum = 0;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AnalysisEnergyHF::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AnalysisEnergyHF::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AnalysisEnergyHF);

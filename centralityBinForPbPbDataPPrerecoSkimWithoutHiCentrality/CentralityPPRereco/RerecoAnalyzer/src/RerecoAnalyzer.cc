// -*- C++ -*-
//
// Package:    RerecoAnalyzer
// Class:      RerecoAnalyzer
// 
/**\class RerecoAnalyzer RerecoAnalyzer.cc CentralityPPRereco/RerecoAnalyzer/src/RerecoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo,,,
//         Created:  Sun May 24 07:45:35 CEST 2015
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

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include <TH1.h>
#include <TH1D.h>
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
//
// class declaration
//

class RerecoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit RerecoAnalyzer(const edm::ParameterSet&);
      ~RerecoAnalyzer();

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
   TH1D* hntrkoffline;
   TH1D* hntrkoffline6080;
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
RerecoAnalyzer::RerecoAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


RerecoAnalyzer::~RerecoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
RerecoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

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
    //cout<<"calculated HF energy = "<<etHFtowerSum<<endl;

    if(etHFtowerSum>48.2599&&etHFtowerSum<216.241){ //this is centrality 60-80%
      // do analysis in 60-80%
    }

// vertex 
     double vx=-999.;
     double vy=-999.;
     double vz=-999.;
     double vxError=-999.;
     double vyError=-999.;
     double vzError=-999.;
     math::XYZVector vtxPos(0,0,0);

     edm::Handle<reco::VertexCollection> recoVertices;
     iEvent.getByLabel("offlinePrimaryVertices",recoVertices);
     unsigned int daughter = 0;
     int greatestvtx = 0;
    
     for (unsigned int i = 0 ; i< recoVertices->size(); ++i){
      daughter = (*recoVertices)[i].tracksSize();
      if( daughter > (*recoVertices)[greatestvtx].tracksSize()) greatestvtx = i;
     }

     if(recoVertices->size()>0){
      vx = (*recoVertices)[greatestvtx].position().x();
      vy = (*recoVertices)[greatestvtx].position().y();
      vz = (*recoVertices)[greatestvtx].position().z();
      vxError = (*recoVertices)[greatestvtx].xError();
      vyError = (*recoVertices)[greatestvtx].yError();
      vzError = (*recoVertices)[greatestvtx].zError();
     }
    
     vtxPos = math::XYZVector(vx,vy,vz);

// tracks
     edm::Handle<reco::TrackCollection> tracks;
     iEvent.getByLabel("generalTracks",tracks);
     int nTracks = 0;

     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];

       math::XYZPoint v1(vx,vy, vz);    
       double dz= track.dz(v1);
       double dzsigma = sqrt(track.dzError()*track.dzError()+vzError*vzError);    
       double dxy= track.dxy(v1);
       double dxysigma = sqrt(track.dxyError()*track.dxyError()+vxError*vyError);
       if( track.quality(reco::TrackBase::highPurity) && track.pt()>0.4 && fabs(track.eta())<2.4 && track.ptError()/track.pt()<0.1 && fabs(dz/dzsigma)<3.0 && fabs(dxy/dxysigma)<3.0) nTracks++;
     }


    cout<<"calculated HF energy = "<<etHFtowerSum<<",  NtrkOffline = "<<nTracks<<endl;
    hntrkoffline->Fill(nTracks);
    if(etHFtowerSum>48.2599&&etHFtowerSum<216.241){ //this is centrality 60-80%
      hntrkoffline6080->Fill(nTracks);
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
RerecoAnalyzer::beginJob()
{
  TH1D::SetDefaultSumw2();
  hntrkoffline = fs->make<TH1D>("ntrkoffline","PbPb Data pp rereco, 5_3_20",1000,0,1000);
  hntrkoffline6080 = fs->make<TH1D>("ntrkoffline6080","PbPb Data pp rereco in 60-80%, 5_3_20",1000,0,1000);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RerecoAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
RerecoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RerecoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RerecoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RerecoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RerecoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RerecoAnalyzer);

// -*- C++ -*-
//
// Package:    Analysis/TestAnalysis
// Class:      TestAnalysis
// 
/**\class TestAnalysis TestAnalysis.cc Analysis/TestAnalysis/plugins/TestAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sat, 05 Sep 2015 06:29:49 GMT
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
#include <TH1D.h>
#include <TH2D.h>
#include "TTree.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

  Int_t d_RunID; 
  Int_t d_LumiID; 
  Int_t d_EventID; 
  Int_t d_centralityBin; 
  Float_t d_ETHF;
  Int_t d_nTrack; 

using namespace std;
using namespace edm;
using namespace reco;
//
// class declaration
//

class TestAnalysis : public edm::EDAnalyzer {
   public:
      explicit TestAnalysis(const edm::ParameterSet&);
      ~TestAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  edm::Service<TFileService> fs;
  edm::Handle<int> cbin_;
  edm::InputTag CentralityTag_;
  edm::EDGetTokenT<int> CentralityBinTag_;
  edm::EDGetTokenT<TrackCollection> srcTracks_;
  edm::EDGetTokenT<VertexCollection> srcVertex_;
  bool useQuality_;
  reco::TrackBase::TrackQuality trackQuality_;
  double trackPtCut_;
  double trackEtaCut_;

   TH1D* centHist;
   TH1D* trkHist;
   TH1D* hfHist;

   TH1D* vxHist;
   TH1D* vyHist;
   TH1D* vzHist;
   TH1D* hiGeneralTracksHist;
   TH1D* ptHist;
   TH1D* etaHist;
   TH1D* phiHist;

   TH2D* etaphiHist;
   TH2D* etaphiptwHist;

  edm::EDGetTokenT<TrackCollection> srcTracksPixel_;
   TH1D* hiGeneralTracksPixelHist;
   TH1D* ptPixelHist;
   TH1D* etaPixelHist;
   TH1D* phiPixelHist;

   TTree *evttree; 

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
TestAnalysis::TestAnalysis(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
edm::Service<TFileService> fs;
CentralityTag_ = iConfig.getParameter<edm::InputTag> ("CentralitySrc");
CentralityBinTag_ = consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinLabel"));
srcTracks_ = consumes<TrackCollection>(iConfig.getParameter<edm::InputTag>("srcTracks"));
srcVertex_ = consumes<VertexCollection>(iConfig.getParameter<edm::InputTag>("srcVertex"));
useQuality_ = iConfig.getParameter<bool>("UseQuality");
trackQuality_ = TrackBase::qualityByName(iConfig.getParameter<std::string>("TrackQuality"));
trackPtCut_ = iConfig.getParameter<double>("trackPtCut");
trackEtaCut_ = iConfig.getParameter<double>("trackEtaCut");

trkHist = fs->make<TH1D>("ntrkhist","Ntracks Distribution", 100, 0., 3000.);
hfHist = fs->make<TH1D>("hfhist","EtHFtowerSum Distribution", 100, 0., 5000.);
centHist = fs->make<TH1D>("centhist","Centrality Distribution", 200, 0., 200.);
vxHist = fs->make<TH1D>("vxhist","hiSelectedVertex Vx Distribution", 100, -0.5, 0.5);
vyHist = fs->make<TH1D>("vyhist","hiSelectedVertex Vy Distribution", 100, -0.5, 0.5);
vzHist = fs->make<TH1D>("vzhist","hiSelectedVertex Vz Distribution", 120, -30., 30.);
hiGeneralTracksHist = fs->make<TH1D>("higeneraltrackshist","hiGeneralTracks Distribution", 100, 0., 3000.);
ptHist = fs->make<TH1D>("pthist","hiGeneralTracks pT Distribution", 100, 0., 10.);
etaHist = fs->make<TH1D>("etahist","hiGeneralTracks eta Distribution", 120, -3.0, 3.0);
phiHist = fs->make<TH1D>("phihist","hiGeneralTracks phi Distribution", 80, -4.0, 4.0);

etaphiHist = fs->make<TH2D>("etaphihist","phi vs. eta", 100,-2.5, 2.5, 80, -4.0, 4.0);
etaphiptwHist = fs->make<TH2D>("etaphiptwhist","phi vs. eta, pt weighted", 100,-2.5, 2.5, 80, -4.0, 4.0);


srcTracksPixel_ = consumes<TrackCollection>(iConfig.getParameter<edm::InputTag>("srcTracksPixel"));
hiGeneralTracksPixelHist = fs->make<TH1D>("higeneraltrackspixelhist","hiGeneralAndPixelTracks Distribution", 100, 0., 3000.);
ptPixelHist = fs->make<TH1D>("ptpixelhist","hiGeneralAndPixelTracks pT Distribution", 100, 0., 10.);
etaPixelHist = fs->make<TH1D>("etapixelhist","hiGeneralAndPixelTracks eta Distribution", 120, -3.0, 3.0);
phiPixelHist = fs->make<TH1D>("phipixelhist","hiGeneralAndPixelTracks phi Distribution", 80, -4.0, 4.0);

   evttree = fs->make<TTree>("evttree","event tree");
   evttree->Branch("RunID",&d_RunID,"RunID/I");  
   evttree->Branch("LumiID",&d_LumiID,"LumiID/I");  
   evttree->Branch("EventID",&d_EventID,"EventID/I");  
   evttree->Branch("centralityBin",&d_centralityBin,"centralityBin/I"); 
   evttree->Branch("ETHF",&d_ETHF,"ETHF/F");
   evttree->Branch("nTrack",&d_nTrack,"nTrack/I");

}


TestAnalysis::~TestAnalysis()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TestAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   d_RunID = iEvent.id().run();
   d_LumiID = iEvent.luminosityBlock();
   d_EventID = iEvent.id().event();

   iEvent.getByToken(CentralityBinTag_,cbin_);
   int bin = *cbin_;
   centHist->Fill(bin);

   d_centralityBin = bin;

    edm::Handle<reco::Centrality> centrality;
    iEvent.getByLabel(CentralityTag_, centrality);
    trkHist->Fill(centrality->Ntracks());
    hfHist->Fill(centrality->EtHFtowerSum());

    d_ETHF = centrality->EtHFtowerSum();
    d_nTrack = centrality->Ntracks();
    //cout<<"Centraliyt bin = "<<bin<<",  Ntracks= "<<centrality->Ntracks()<<", EtHFtowerSum= "<<centrality->EtHFtowerSum()<<endl;


     double vx=-999.;
     double vy=-999.;
     double vz=-999.;
     double vxError=-999.;
     double vyError=-999.;
     double vzError=-999.;
     math::XYZVector vtxPos(0,0,0);

     edm::Handle<VertexCollection> recoVertices;
     iEvent.getByToken(srcVertex_,recoVertices);
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
     vxHist->Fill(vx);
     vyHist->Fill(vy);
     vzHist->Fill(vz);

     edm::Handle<TrackCollection> tracks;
     iEvent.getByToken(srcTracks_,tracks);
     int nTracks = 0;

     for(unsigned int i = 0 ; i < tracks->size(); ++i){
       const Track& track = (*tracks)[i];
       if(useQuality_ && !track.quality(trackQuality_)) continue;

       math::XYZPoint v1(vx,vy, vz);
       double dz= track.dz(v1);
       double dzsigma2 = track.dzError()*track.dzError()+vzError*vzError;
       double dxy= track.dxy(v1);
       double dxysigma2 = track.dxyError()*track.dxyError()+vxError*vyError;

       const double pterrcut = 0.1;
       const double dzrelcut = 3.0;
       const double dxyrelcut = 3.0;

       if( track.quality(trackQuality_) &&
       track.pt()>trackPtCut_ && track.eta()<trackEtaCut_ &&
       track.eta()>-1.0*trackEtaCut_ &&
       track.ptError()/track.pt() < pterrcut &&
       dz*dz < dzrelcut*dzrelcut * dzsigma2 &&
       dxy*dxy < dxyrelcut*dxyrelcut * dxysigma2 ){
         ptHist->Fill(track.pt());
         etaHist->Fill(track.eta());
         phiHist->Fill(track.phi());
         nTracks++;
         if(centrality->Ntracks() == 2080) {
           etaphiHist->Fill(track.eta(), track.phi());
           etaphiptwHist->Fill(track.eta(), track.phi(), track.pt());
         }
       }
     }

     hiGeneralTracksHist->Fill(nTracks);

//generalAndPixelTracks
     edm::Handle<TrackCollection> tracksPixel;
     iEvent.getByToken(srcTracksPixel_,tracksPixel);
     int nTracksPixel = 0;

     for(unsigned int i = 0 ; i < tracksPixel->size(); ++i){
       const Track& trackPixel = (*tracksPixel)[i];
       if(useQuality_ && !trackPixel.quality(trackQuality_)) continue;

       math::XYZPoint v1(vx,vy, vz);
       double dz= trackPixel.dz(v1);
       double dzsigma2 = trackPixel.dzError()*trackPixel.dzError()+vzError*vzError;
       double dxy= trackPixel.dxy(v1);
       double dxysigma2 = trackPixel.dxyError()*trackPixel.dxyError()+vxError*vyError;

       const double pterrcut = 0.1;
       const double dzrelcut = 3.0;
       const double dxyrelcut = 3.0;

       if( trackPixel.quality(trackQuality_) &&
       trackPixel.pt()>trackPtCut_ && trackPixel.eta()<trackEtaCut_ &&
       trackPixel.eta()>-1.0*trackEtaCut_ &&
       trackPixel.ptError()/trackPixel.pt() < pterrcut &&
       dz*dz < dzrelcut*dzrelcut * dzsigma2 &&
       dxy*dxy < dxyrelcut*dxyrelcut * dxysigma2 ){
         ptPixelHist->Fill(trackPixel.pt());
         etaPixelHist->Fill(trackPixel.eta());
         phiPixelHist->Fill(trackPixel.phi());
         nTracksPixel++;
       }
     }

     hiGeneralTracksPixelHist->Fill(nTracksPixel);

     evttree->Fill(); 


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
TestAnalysis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TestAnalysis::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
TestAnalysis::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
TestAnalysis::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
TestAnalysis::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
TestAnalysis::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TestAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TestAnalysis);

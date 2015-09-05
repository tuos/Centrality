// -*- C++ -*-
//
// Package:    Analysis/EventIDFilter
// Class:      EventIDFilter
// 
/**\class EventIDFilter EventIDFilter.cc Analysis/EventIDFilter/plugins/EventIDFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Sat, 05 Sep 2015 08:24:44 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "/scratch/tuos/temp/cmssw/CMSSW_7_5_0/src/Analysis/EventIDFilter/plugins/EventIDFilter.h"
  Int_t d_RunID;
  Int_t d_LumiID;
  Int_t d_EventID;

//
// class declaration
//

class EventIDFilter : public edm::stream::EDFilter<> {
   public:
      explicit EventIDFilter(const edm::ParameterSet&);
      ~EventIDFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

   std::vector<int> selectedBins_;
  
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
EventIDFilter::EventIDFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   selectedBins_ = iConfig.getParameter<std::vector<int> >("selectedBins");
}


EventIDFilter::~EventIDFilter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
EventIDFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   bool select = false;

   d_RunID = iEvent.id().run();
   d_LumiID = iEvent.luminosityBlock();
   d_EventID = iEvent.id().event();

   int bin = -1;
   for(unsigned int i = 0; i < selectedBins_.size(); i++){
     for(int j = 0; j < 1000; j++){
       if(d_RunID==realRunID[j] && d_LumiID==realLumiID[j] && d_EventID==realEventID[j])
         bin = realCentID[j];
     }
     if(bin == selectedBins_[i]) select = true;
   }

   return select;

//#ifdef THIS_IS_AN_EVENT_EXAMPLE
//   Handle<ExampleData> pIn;
//   iEvent.getByLabel("example",pIn);
//#endif
//
//#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
//   ESHandle<SetupData> pSetup;
//   iSetup.get<SetupRecord>().get(pSetup);
//#endif
//   return true;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
EventIDFilter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
EventIDFilter::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
EventIDFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
EventIDFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
EventIDFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
EventIDFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EventIDFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(EventIDFilter);

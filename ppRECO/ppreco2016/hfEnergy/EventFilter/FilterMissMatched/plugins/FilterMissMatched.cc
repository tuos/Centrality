// -*- C++ -*-
//
// Package:    EventFilter/FilterMissMatched
// Class:      FilterMissMatched
// 
/**\class FilterMissMatched FilterMissMatched.cc EventFilter/FilterMissMatched/plugins/FilterMissMatched.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Fri, 01 Apr 2016 12:04:47 GMT
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

#include "/afs/cern.ch/user/t/tuos/work/public/run2015/pprereco/CMSSW_7_5_8_patch4/src/EventFilter/FilterMissMatched/plugins/FilterMissMatched.h"
  Int_t d_RunID;
  Int_t d_EventID;

//
// class declaration
//

class FilterMissMatched : public edm::stream::EDFilter<> {
   public:
      explicit FilterMissMatched(const edm::ParameterSet&);
      ~FilterMissMatched();

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

   std::vector<int> selectedEvents_;

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
FilterMissMatched::FilterMissMatched(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed
   selectedEvents_ = iConfig.getParameter<std::vector<int> >("selectedEvents");

}


FilterMissMatched::~FilterMissMatched()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
FilterMissMatched::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   bool select = false;

   d_RunID = iEvent.id().run();
   d_EventID = iEvent.id().event();

   int event = -1;
   for(unsigned int i = 0; i < selectedEvents_.size(); i++){
     for(int j = 0; j < 100; j++){
       if(d_RunID==realRunID[j] && d_EventID==realEventID[j])
         event = missMatchedID[j];
     }
     if(event == selectedEvents_[i]) select = true;
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
FilterMissMatched::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
FilterMissMatched::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
FilterMissMatched::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
FilterMissMatched::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
FilterMissMatched::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
FilterMissMatched::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FilterMissMatched::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(FilterMissMatched);

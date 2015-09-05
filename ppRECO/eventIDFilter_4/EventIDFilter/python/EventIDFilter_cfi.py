import FWCore.ParameterSet.Config as cms

eventIDFilter = cms.EDFilter("EventIDFilter",
                                selectedBins = cms.vint32(0),
                                )

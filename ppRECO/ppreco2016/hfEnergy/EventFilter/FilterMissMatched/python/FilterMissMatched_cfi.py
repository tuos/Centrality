import FWCore.ParameterSet.Config as cms

filterMissMatched = cms.EDFilter("FilterMissMatched",
                                selectedEvents = cms.vint32(0),
                                )

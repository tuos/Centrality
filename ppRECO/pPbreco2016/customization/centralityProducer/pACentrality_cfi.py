import FWCore.ParameterSet.Config as cms

pACentrality = cms.EDProducer("CentralityProducer",

                            produceHFhits = cms.bool(False),
                            produceHFtowers = cms.bool(True),
                            produceEcalhits = cms.bool(False),
                            produceZDChits = cms.bool(True),
                            produceETmidRapidity = cms.bool(False),
                            producePixelhits = cms.bool(False),
                            produceTracks = cms.bool(True),
                            producePixelTracks = cms.bool(False),
                            reUseCentrality = cms.bool(False),
                            
                            srcHFhits = cms.InputTag("hfreco"),
                            srcTowers = cms.InputTag("towerMaker"),
                            srcEBhits = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
                            srcEEhits = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
                            srcZDChits = cms.InputTag("zdcreco"),
                            srcPixelhits = cms.InputTag("siPixelRecHits"),
                            srcTracks = cms.InputTag("generalTracks"),
                            srcVertex= cms.InputTag("offlinePrimaryVertices"),
                            srcReUse = cms.InputTag("pACentrality"),
                            srcPixelTracks = cms.InputTag("pixelTracks"),

                            doPixelCut = cms.bool(True),
                            UseQuality = cms.bool(True),
                            TrackQuality = cms.string('highPurity'),
                            trackEtaCut = cms.double(2),
                            trackPtCut = cms.double(1),
                            hfEtaCut = cms.double(4), #hf above the absolute value of this cut is used
                            midRapidityRange = cms.double(1),
			    lowGainZDC = cms.bool(True),

                            )



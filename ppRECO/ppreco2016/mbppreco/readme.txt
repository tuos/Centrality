
PbPb golden json: /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt

DAS: block dataset=/HIMinimumBias2/HIRun2015-v1/RAW run=262893
Block: /HIMinimumBias2/HIRun2015-v1/RAW#9477a000-97c0-11e5-9687-001e67abf228
Block size: 1.7TB, Number of files: 500
Block: /HIMinimumBias2/HIRun2015-v1/RAW#a3b05994-a14e-11e5-9720-001e67abf228
Block size: 685.1GB, Number of files: 103
Block: /HIMinimumBias2/HIRun2015-v1/RAW#d1da22e4-97e1-11e5-9687-001e67abf228
Block size: 1.7TB, Number of files: 480

new Json file: {"262893": [[33, 1054]]}

current pp reconstruct:
release: CMSSW_7_5_8_patch4
cfg: https://cmsweb.cern.ch/reqmgr/view/showOriginalConfig/fabozzi_HIRun2015-HIMinimumBias5-02May2016_758p4_160502_172625_4322
need to change input files and HLT paths, then only reconstruct hf
https://github.com/cms-sw/cmssw/blob/CMSSW_7_5_X/Configuration/StandardSequences/python/Reconstruction_cff.py


find HLT path: https://cmsweb.cern.ch/confdb/

1. Configuration/StandardSequences/python/Reconstruction_cff.py was modified, tried to keep only HF information

seems not possible to just reco hf without tracking now:
CaloTowersCreator/'towerMaker' needs hbhereco, (http://cmslxr.fnal.gov/source/RecoLocalCalo/CaloTowersCreator/python/calotowermaker_cfi.py)
HBHEIsolatedNoiseReflagger/'hbhereco' needs trackExtrapolator, (http://cmslxr.fnal.gov/source/RecoLocalCalo/HcalRecProducers/python/HBHEIsolatedNoiseReflagger_cfi.py)
TrackExtrapolator/'trackExtrapolator' needs generalTracks, (http://cmslxr.fnal.gov/source/RecoJets/JetAssociationProducers/python/trackExtrapolator_cfi.py)

For now, try to use "hbheprereco" in towerMaker. 
2. RecoLocalCalo/CaloTowersCreator/python/calotowermaker_cfi.py was modified to use "hbheprereco"
seems ok???
http://cmslxr.fnal.gov/ident is very useful.

Error with 'photonIsolationHIProducerpp', can not find 'photons'
curl -s --insecure https://raw.githubusercontent.com/cms-sw/cmssw/CMSSW_7_5_X/RecoHI/Configuration/python/customise_PPwithHI.py --retry 2 --create-dirs -o RecoHI/Configuration/python/customise_PPwithHI.py
3. RecoHI/Configuration/python/customise_PPwithHI.py is modified to remove photon related collections

seems working for now, but we are using "hbheprereco" now.
Is the HF energy changed???




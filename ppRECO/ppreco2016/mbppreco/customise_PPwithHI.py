import FWCore.ParameterSet.Config as cms

# Customize process to run HI-style photon isolation in the pp RECO sequences
def addHIIsolationProducer(process):

    process.load('Configuration.EventContent.EventContent_cff')
    
    return process


    # modify cluster limits to run pp reconstruction on peripheral PbPb
def modifyClusterLimits(process):

    return process


# Add caloTowers to AOD event content
def storeCaloTowersAOD(process):

    process.load('Configuration.EventContent.EventContent_cff')
    
    # extend AOD content
    if hasattr(process,'AODoutput'):
        process.AODoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

    if hasattr(process,'AODSIMoutput'):
        process.AODSIMoutput.outputCommands.extend(['keep *_towerMaker_*_*'])

    return process

def customisePPwithHI(process):

    process=addHIIsolationProducer(process)
    process=modifyClusterLimits(process)
    process=storeCaloTowersAOD(process)

    return process


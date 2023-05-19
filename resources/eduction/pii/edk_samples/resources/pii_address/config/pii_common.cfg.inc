[Eduction]
AllowMultipleResults = False
MatchWholeWord = True
EnableComponents = True
MinScore = 0.4
PostProcessThreshold = 0.5
PostProcessingTask0 = pii_postprocessing

[pii_postprocessing]
Script  = ../../scripts/pii_postprocessing.lua
Entities = pii/*

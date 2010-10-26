--- Checkout and compile the following tags: (will be integrated in CMSSW_3_8_6)

cvs co -r V03-01-02 CondFormats/JetMETObjects                     
cvs co -r V02-01-01 JetMETCorrections/Algorithms                  
cvs co -r V03-01-01 JetMETCorrections/Configuration               
cvs co -r V05-00-01 JetMETCorrections/Modules                     

--- Disable the use of CondDB in your configuration file (during the transition period, the txt files are still in CVS)

process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.ak5PFL2Relative.useCondDB = False
process.ak5PFL3Absolute.useCondDB = False
process.ak5PFResidual.useCondDB = False

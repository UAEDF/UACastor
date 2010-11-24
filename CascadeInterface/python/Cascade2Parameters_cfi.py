import FWCore.ParameterSet.Config as cms

                         
Cascade2Parameters = cms.PSet(
    parameterSets = cms.vstring('CascadeSettings'),
    CascadeSettings = cms.vstring('KE = 2212 ! flavour code of beam1',
                                  'IRES(1) = 1 ! direct or resolved particle 1',
                                  'KP = 2212 ! flavour code of beam2',
                                  'IRES(2) = 1 ! direct or resolved particle 2',
                                  'NFRAG = 1 ! fragmentation (1=on, 0=off)',
                                  'IPST = 0 ! to keep track of intermediate state in PS ',
                                  'IPSIPOL = 0 ! polarisation for J/psi (1=on,0=off)',
                                  'I23S = 0 ! select 1S, 2S, 3S state for vector meson (0=1S,2=2S,3=3S from version 2.2.03 on)',
                                  'IFPS = 3 ! parton shower( 0 = off, 1 = initial, 2 = final, 3 = initial & final state PS)',
                                  'ITIMSHR = 1 ! swtich for time-like shower in intial state cascade (0=off,1=on)',
                                  'IRAM = 1 ! switch for running alphas (0=off,1=on)',
                                  'IQ2 = 3 ! scale for alphas',
                                  'IPRO = 11 ! process number (IPRO = 2 J/psi g, IPRO = 10 q qbar,IPRO = 11 Q Qbar)',
                                  'NFLA = 5 ! number of flavors in pdfs',
                                  'INTER = 0 ! mode of interaction for ep (photon exchange, Z-echange (not implemented))',
                                  'IHFLA = 4 ! flavor code of heavy flavor in IPRO = 11, and for vector meson producutin via IPRO = 2,3',
                                  'IRPA = 0 ! switch to select QCD process g* g* -> q qbar via IRPA = 1',
                                  'IRPB = 0 ! switch to select QCD process g* g -> g g via IRPB = 1',
                                  'IRPC = 0 ! switch to select QCD process g* q -> g q via IRPC = 1',
                                  'ICCF = 1 ! select CCFM or DGLAP mode (=1 CCFM, =0 DGLAP)',
                                  'IGLU = 1010 ! select uPDF (1010 = set A, default)',
                                  'IREM = 4 ! switch for p-remnant treatment',
                                  'PT2CUT = 0.0 ! pt2 cut in ME for massless partons',
                                  'ACC1 = 1.0 ! accurary requested for grid optimisation step (BASES)',
                                  'ACC2 = 0.5 ! accuracy requested for integration step (BASES)',
                                  'SCALFA = 1 ! scale factor for scale in alphas',
                                  'SCALFAF = 1 ! scale factor for final state parton shower scale',
                                  'UPDF = /path/updf.txt ! path where updf grid files are stored')
    )

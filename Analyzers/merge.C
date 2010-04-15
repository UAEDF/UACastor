{
TChain chain("CastorDigi");

chain.Add("TreeMaker_Jan23RawReco_AllCastorRuns900GeV.root");
//chain.Add("TreeMaker_Jan23RawReco_Run124120.root");
chain.Add("TreeMaker_MCApril8_MinBias900GeV.root");
//chain.Add("TreeMaker_MCApril8_MinBias2360GeV.root");


chain.Merge("TreeMaker_Jan23RawReco+MCApril8_900GeV.root");
}


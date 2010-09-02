{
TChain chain("demo/SimHits");

chain.Add("SLTree_Pion5-45GeV_FullSim_10000_etaphirange.root");
//chain.Add("SLTree_Pion10GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion15GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion20GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion25GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion30GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion35GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion40GeV_FullSim_10000_etaphipoint.root");
//chain.Add("SLTree_Pion45GeV_FullSim_10000_etaphipoint.root");

chain.Add("SLTree_Pion5-45GeV_SL_10000_etaphirange.root");
//chain.Add("SLTree_Pion10GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion15GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion20GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion25GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion30GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion35GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion40GeV_SL_10000_etaphipoint.root");
//chain.Add("SLTree_Pion45GeV_SL_10000_etaphipoint.root");

chain.Merge("SLTree_5-45GeVpion_FS+SL50ME_10000_etaphirange.root");
}


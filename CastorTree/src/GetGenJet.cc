#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

#include "./CastorTree.h"

bool GenJetDebug = false;

void CastorTree::GetGenJet(const edm::Event& iEvent, const edm::InputTag& genjetcoll_, vector<MyGenJet>& JetVector) {

  using namespace std;
  using namespace edm;
  using namespace reco;

  JetVector.clear();
  
  //-- FIXME: needed only for name which is for now commented: crashes the code ...
  // ESHandle <ParticleDataTable> pdt;
  // iSetup.getData( pdt );

  //-- gen jet collection
  Handle<GenJetCollection> genjets;
  iEvent.getByLabel(genjetcoll_,genjets);
  
  JetVector.assign(genjets->size(),MyGenJet());
  
  int ijet = 0;  

  for(GenJetCollection::const_iterator genjet = genjets->begin(); genjet != genjets->end(); ++genjet,++ijet){ 
  
    JetVector[ijet].SetPxPyPzE(genjet->px(),genjet->py(),genjet->pz(),genjet->energy());

    JetVector[ijet].npart = genjet->nConstituents();
     
    vector <const GenParticle*> genparts = genjet->getGenConstituents();
    JetVector[ijet].JetPart.assign(genparts.size(),MyGenPart());
    
    //-- FIXME : doesn't fill mothers & daughters
    for (unsigned i = 0; i < genparts.size (); i++)
      this->FillGenPart(*(genparts[i]),JetVector[ijet].JetPart[i]);

    if(GenJetDebug) JetVector[ijet].Print();
  }
  
}


void CastorTree::GetAllGenJet(const edm::Event& iEvent) {
  
  using namespace std;
  using namespace edm;
  using namespace reco;

  for(vector<InputTag>::iterator icoll = GenJetColl_.begin() ; icoll!= GenJetColl_.end() ; ++icoll)
    this->GetGenJet(iEvent,*icoll,AllGenJet[icoll->label()]);
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "ParticleMass.h"
#include "Event.h"
#include "MassMean.h"

using namespace std;

ParticleMass::ParticleMass() 
{
}

ParticleMass::~ParticleMass()
{
}

// inizio esecuzione
void ParticleMass::beginJob()
{
    pList.reserve(10); //riservo lo spazio di memoria nella lista
    //creo elementi nella lista uno per tipo di decadimento
    pList.push_back(new MassMean(0.490, 0.505)); //decadimento k
    pList.push_back(new MassMean(1.114, 1.118)); //decadimento Lambda
    return;
}

void ParticleMass::endJob()
{
    int n=pList.size(); //ciclo sugli elementi
    for (int i=0; i<n; i++)
    {
        MassMean* mean= pList[i]; //prendo l'elemento
        mean->compute(); //calcolo risultati
        //stampo i risultati
        cout<<mean->mMean()<<"\t"<<mean->mRMS()<<"\t"<<mean->nEvents()<<endl;   
    }
}

void ParticleMass::process(const Event& ev)
{
    int n=pList.size(); //loop e aggiunta degli elemnti per le due masse
    for (int i=0; i<n; i++) pList[i]->add(ev);
}
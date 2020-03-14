//sviluppo la funzione di scrittura
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

void dump (int n_ev, int n_p, float x, float y, float z, 
            int* charges, float* px, float* py, float* pz)
{
    cout<<n_ev<<endl;//stampo numero evento e luogo
    cout<<x<<"\t"<<y<<"\t"<<z<<endl;
    cout<<n_p<<endl;
    
    for (int i=0; i<n_p; i++) //per ogni particella stampo carica e momento
    {
        cout<<charges[i]<<"\t"<<px[i]<<"\t"<<py[i]<<"\t"<<pz[i]<<endl;
    }

    return;
}
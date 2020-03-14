//sviluppo la funzione di lettura
#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

int read (ifstream& input, float& x, float& y, float& z, 
            int* charge, float* px, float* py, float* pz)
{
    input>>x>>y>>z; //ricevo il punto di decadimento
    int n; //numero di particelle (è il return della funzione)
    input>>n;
    for (int i=0; i<n; i++) //per ogni particella ricevo carica e momento
    {
        input>>charge[i];
        input>>px[i]>>py[i]>>pz[i];
    }

    return n;
}
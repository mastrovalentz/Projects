#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//intervallo di accettabilità delle masse
const double min_mass=0.490, max_mass=0.505;

struct Particle;
struct Event;

const Event* read (ifstream&);
void dump (const Event&);
void clear (const Event*);
bool add (const Event&, float, float, double&, double&);

int main(int argc, const char* argv[])
{
    const char* file=argv[1]; //ricevo file dati
    ifstream input (file);

    const Event* ev;
    int cont=0; //variabili per contare e calcolare media e rms 
    double sum=0, sum_squares=0, mean, rms;

    while ((ev=read(input))!=0) //finchè ricevo eventi faccio girare
    {
        //eseguo la chiamata di add direttamente dentro l'if
        //in questo modo le somme si aggiornano in automatico essendo
        //passate per reference e l'unica cosa rimasta da fare è 
        //incremetare il contatore
        if (add(*ev, min_mass, max_mass, sum, sum_squares)==true) cont++; 
        dump(*ev); //stampo
        clear(ev); //pulisco la memoria
    }
    
    //calcolo media e rms
    mean=sum/cont;
    rms=sqrt(sum_squares/cont-pow(mean,2));
    
    //stampo media e rms
    cout<<mean<<endl;
    cout<<rms<<endl;

    return 0;
}
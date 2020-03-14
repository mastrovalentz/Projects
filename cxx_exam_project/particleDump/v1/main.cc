#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

const int DIM=10; //dimensione massima degli array contenenti i dati

int read (ifstream&, float&, float&, float&, 
            int*, float*, float*, float*); //lettura dati
void dump (int, int, float, float, float, 
            int*, float*, float*, float*); //scrittura dati

int main(int argc, char* argv[])
{
    const char* file=argv[1]; //ricevo nome da linea di comando

    ifstream input (file);

    int ev_number, particle_number; //variabili identificative di un evento
    float x_decay, y_decay, z_decay;
    int charges [DIM];
    float x_moment[DIM], y_moment[DIM], z_moment[DIM];

    while(input>>ev_number) //finche ricevo un codice evento leggo e stampo tutti i valori
    {
        //ricevo evento
        particle_number=read(input, x_decay, y_decay, z_decay, 
                              charges, x_moment, y_moment, z_moment);

        //stampo evento
        dump(ev_number, particle_number, x_decay, y_decay, z_decay,
                charges, x_moment, y_moment, z_moment);
    }

    return 0;

}
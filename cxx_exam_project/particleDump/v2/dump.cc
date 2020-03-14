#include <iostream>
#include <fstream>

#include "Event.h"
#include "Particle.h"

using namespace std;

void dump (const Event& ev)
{
    cout<<ev.ev_number<<endl; //stampo identificativo e luogo dell'evento
    cout<<ev.ev_x<<"\t"<<ev.ev_y<<"\t"<<ev.ev_z<<endl;

    cout<<ev.particle_number<<endl;

    //per ogni particella stampo carica e momento
    for (int i=0; i<ev.particle_number; i++) 
    {
        cout<<ev.p_decay[i]->charge<<"\t"<<ev.p_decay[i]->px<<"\t";
        cout<<ev.p_decay[i]->py<<"\t"<<ev.p_decay[i]->pz<<endl;
    }

    return;
}
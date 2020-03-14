#include <iostream>
#include <fstream>

#include "Event.h"

using namespace std;

void dump (const Event& ev)
{
    cout<<ev.eventNumber()<<endl; //stampo identificativo e luogo dell'evento
    cout<<ev.x_event()<<"\t"<<ev.y_event()<<"\t"<<ev.z_event()<<endl;

    cout<<ev.nParticles()<<endl; //stampo numero particella

    //per ogni particella stampo carica e momento
    for (int i=0; i<ev.nParticles(); i++) 
    {
        cout<<ev.particle(i)->charge<<"\t"<<ev.particle(i)->px<<"\t";
        cout<<ev.particle(i)->py<<"\t"<<ev.particle(i)->pz<<endl;
    }

    return;
}
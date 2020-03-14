#include <iostream>
#include <fstream>

#include "Event.h"
#include "Particle.h"

using namespace std;

void clear (const Event* ev)
{
     // per prima cosa elimino le strutture particella
    for (int i=0; i<ev->particle_number; i++)  delete ev->p_decay[i]; 
    delete [] ev->p_decay; //elimino l'array di puntatori delle strutture
    delete [] ev; //elimino l'evento

    return;
}
#include <iostream>
#include <fstream>

#include "Particle.h"
#include "Event.h"

using namespace std;

struct Event;
struct Particle;

const Event* read (ifstream& input)
{
    Event* ev; 
    int ev_id, n; //variabili che poi assegnerò all'evento

    if (input>>ev_id) ev=new Event;//se ce un evento ricevibile creo l'oggetto
    else return 0; //se non c'è ritorno 0 così da terminare il ciclo nel main

    ev->ev_number=ev_id; //se ho ricevuto l'identificativo lo assegno all'evento

    //ora ricevo le altre variabili dell'evento

    input>>ev->ev_x>>ev->ev_y>>ev->ev_z; //coordinate evento
    input>>n; //numero particelle

    ev->particle_number=n;

    ev->p_decay=new Particle* [n]; //creo l'array di particelle
    for (int i=0; i<n; i++)
    {
        Particle* temp= new Particle; //uso variabile temporanea per ricevere i dati
        input>>temp->charge;
        input>>temp->px>>temp->py>>temp->pz;
        ev->p_decay [i]=temp;
    }

    return ev; //ritorno l'evento
}

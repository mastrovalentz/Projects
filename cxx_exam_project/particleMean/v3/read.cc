#include <iostream>
#include <fstream>

#include "Event.h"

using namespace std;

const Event* read (ifstream& input)
{
    Event* ev; 
    int ev_id, n;
    double ev_x, ev_y, ev_z; //variabili che poi assegnerò all'evento

    if (input>>ev_id) //se ce un evento ricevibile creo l'oggetto
    {
        input>>ev_x>>ev_y>>ev_z; //coordinate evento
        ev=new Event(ev_id, ev_x, ev_y, ev_z);
    } 
    else return 0; //se non c'è ritorno 0 così da terminare il ciclo nel main
    
    input>>n; //ricevo numero particelle
    
    //variabili da mandare alla funzione add per aggiungere le particelle
    int ch;
    double px, py, pz;  for (int i=0; i<n; i++)
    {
        input>>ch>>px>>py>>pz; //ricevo le variabili
        ev->add(px, py, pz, ch); //aggiungo la particella all evento
    }

    return ev;
}

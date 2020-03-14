#include <iostream>
#include <fstream>
#include <string>

#include "EventReadFromFile.h"
#include "Event.h"

using namespace std;

// read data from file "name"
EventReadFromFile::EventReadFromFile( const string& name ) 
{
  file = new ifstream(name.c_str());
}

EventReadFromFile::~EventReadFromFile() 
{
  delete file;
}

// get an event
const Event* EventReadFromFile::get() 
{
  return readFile();
}

// read an event
const Event* EventReadFromFile::readFile() 
{
  Event* ev; 
  int ev_id, n;
  double ev_x, ev_y, ev_z; //variabili che poi assegnerò all'evento

  if (*file>>ev_id) //se ce un evento ricevibile creo l'oggetto
  {
    *file>>ev_x>>ev_y>>ev_z; //coordinate evento
    ev=new Event(ev_id, ev_x, ev_y, ev_z);
  } 
  else return 0; //se non c'è ritorno 0 così da terminare il ciclo nel main
    
  *file>>n; //ricevo numero particelle
  int ch;
  double px, py, pz; //variabili da mandare alla funzione add per aggiungere le particelle
  for (int i=0; i<n; i++)
  {
    *file>>ch>>px>>py>>pz; //ricevo le variabili
    ev->add(px, py, pz, ch); //aggiungo la particella all evento
  }

  return ev;
}


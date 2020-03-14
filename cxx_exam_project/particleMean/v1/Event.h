#ifndef Event_h
#define Event_h


//data la conoscenza della struttura particella definisco l'evento
//il quale è identificato dal numero di particelle del decadimento
//e dal luogo in cui esso avviene, oltre che dal suo numero di identificazione
struct Particle;
struct Event
{
    int ev_number, particle_number;
    float ev_x, ev_y, ev_z; //identificatore e posizioni dell'evento
    Particle** p_decay;
};

#endif
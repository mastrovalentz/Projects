#include <iostream>

using namespace std;

struct Event;

double mass (const Event& ev); //funzione per calcolare la massa

bool add (const Event& ev, float min_mass, float max_mass, 
            double& sum, double& sum_squares)
{
    double m=mass(ev); //calcolo la massa invariante dell'evento
    if(m<=max_mass && m>=min_mass) //controllo se è nell'intervallo
    {
        sum+=m; //in caso affermativo aggiorno le somme e ritorno una risposta affermativa
        sum_squares+=m*m;
        return true;
    }
    return false; 
    //non serve mettere else perchè la funzione termina prima se l'if è vero
}

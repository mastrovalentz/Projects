#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Particle;
struct Event;

const Event* read (ifstream&);
void dump (const Event&);
void clear (const Event*); //per pulire la memoria

int main(int argc, const char* argv[])
{
    const char* file=argv[1];

    ifstream input (file);

    const Event* ev;
    while ((ev=read(input))!=0) //finchè ricevo eventi 
    {
        dump(*ev); //stampo
        clear(ev); //pulisco la memoria
    }

    return 0;
}
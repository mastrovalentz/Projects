#include "EventSource.h"
#include "Event.h"
#include "util/include/Dispatcher.h"

EventSource::EventSource() {
}


EventSource::~EventSource() {
}

void EventSource::run()
{
    const Event *ev;
    while ((ev=get())) // la funzione ritorna vero finchè ci sono eventi da analizzare 
    {
        Dispatcher<Event>::notify (*ev);
        delete ev;
    }
    return;
}
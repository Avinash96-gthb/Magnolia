#ifndef EVENT_BUS_H
#define EVENT_BUS_H

#include "Subscriber.h"

typedef struct {
	int count;
	Subscriber subscriberList[];
}EventBus;

extern EventBus *globalEventBus;

#endif

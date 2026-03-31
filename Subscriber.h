#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "Typelist.h"

typedef struct {
	typelist type;
	size_t size;
	char *publisherName;
	void (*callback)(void*);
}Subscriber;

#endif

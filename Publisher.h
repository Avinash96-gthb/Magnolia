#ifndef PUBLISHER_H
#define PUBLISHER_H


#include "Typelist.h"
typedef struct {
	typelist type;
	char *publisherName;
	void* data;
}Publisher;

void publish(Publisher publisher);


#endif

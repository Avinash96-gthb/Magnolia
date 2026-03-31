#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "Publisher.h"
#include "EventBus.h"

void publish(Publisher publisher){
	int count = globalEventBus->count;
	for (int i = 0; i < count; i++){
		int res = strcmp(publisher.publisherName, globalEventBus->subscriberList[i].publisherName);
		if (res == 0){
			if (publisher.type == globalEventBus->subscriberList[i].type){

			     printf("found the subscriber subscriber to publisher and now calling the callBack\n");
			     globalEventBus->subscriberList[i].callback(publisher.data);
			} else {
				fprintf(stderr,"ERROR: the type of data %d being published for publisher name %s is different from the type of data expected by subscriber of type %d",publisher.type, publisher.publisherName,globalEventBus->subscriberList[i].type);
				assert(publisher.type == globalEventBus->subscriberList[i].type);
			}
		}
	}
}


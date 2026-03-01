#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
	size_t size;
	char *publisherName;
	void (*callback)(void*);
}Subscriber;

typedef struct {
	int count;
	Subscriber subscriberList[];
}EventBus;

typedef struct {
	char *publisherName;
	int data;
}Publisher;

static EventBus *globalEventBus;

void callbackTest(void* a){
	int* dataPtr = (int*)a;
	printf("hello from callback with data %d \n",*dataPtr);
}


void callingCallback(void (*callback)(void*)){
	printf("entering function that does calling back\n");
	int b = 30;
	callback(&b);
}


void addSubscriber(Subscriber subscriber){
	int count = globalEventBus->count;
	printf("current count is %d \n", count);
	count += 1;
	EventBus *TempBus = realloc(globalEventBus, sizeof(EventBus) + count * sizeof(Subscriber));
	if (TempBus){
		globalEventBus = TempBus;
	} else {
		printf("failure nooo \n");
	}
	globalEventBus->subscriberList[count-1] = subscriber;
	globalEventBus->count = count;
	for (int i = 0; i < count; i++){
	        printf("even more sus but the new subscriber is of size %zu and name %s \n",globalEventBus->subscriberList[i].size, globalEventBus->subscriberList[i].publisherName);
	}
	globalEventBus->subscriberList[count-1].callback(&count);
}

void publish(Publisher publisher){
	int count = globalEventBus->count;
	for (int i = 0; i < count; i++){
		int res = strcmp(publisher.publisherName, globalEventBus->subscriberList[i].publisherName);
		if (res == 0){
			printf("found the subscriber subscriber to publisher and now calling the callBack\n");
			globalEventBus->subscriberList[i].callback(&publisher.data);
		}
	}
}

int main(){
	printf("hello world, testing subscriber struct \n");
        Subscriber subscriber1;
	printf("enter the name of subscriber1 \n");
	subscriber1.publisherName = strdup("hello");
	subscriber1.size = strlen(subscriber1.publisherName);
	subscriber1.callback = callbackTest;
	printf("testing printing the subscriber size %zu and name is %s",subscriber1.size, subscriber1.publisherName);
	printf("triggering function which will do callback\n");
	callingCallback(callbackTest);
	int a = 20;
	subscriber1.callback(&a);
	int BusCount = 1;
	globalEventBus = malloc(sizeof(EventBus) + BusCount * sizeof(Subscriber));
	if (globalEventBus == NULL){
		printf("oops not supposed to happen \n");
	}
	globalEventBus->count = BusCount;
	printf("yaaah the count of GlobalEventBus is %d \n", globalEventBus->count);
	globalEventBus->subscriberList[0] = subscriber1;
	printf("this is a littble bit tricky the subscriber 1 size is %zu and name is %s \n",globalEventBus->subscriberList[0].size,globalEventBus->subscriberList[0].publisherName);
	Subscriber subscriber2;
	subscriber2.publisherName = strdup("second sub");
	subscriber2.size = strlen(subscriber2.publisherName);
	subscriber2.callback = callbackTest;
	addSubscriber(subscriber2);
	Publisher publisher1;
	publisher1.publisherName = strdup("hello");
	publisher1.data = 87932;
	publish(publisher1);
	return 0;
}


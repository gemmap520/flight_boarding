#include <stdbool.h>
#include "passenger.h"

// a queue for passengers
struct queue;

// queue_create() creates a new empty queue.
// effects: allocates heap memory [client must call queue_destroy]
// time:    O(1)
struct queue *queue_create(void);

// queue_destroy(q) releases all resources used by *q.
// effects: invalidates *q
// time:    O(n), where n is the number of queued passengers
void queue_destroy(struct queue *q);

// queue_enqueue(q, name, zone) adds a passenger with name and zone to the end
//    of the queue *q.
// effects: mutates *q
// time:    O(1) [amortized]
void queue_enqueue(struct queue *q, const char *name, const int zone);

// queue_dequeue(q) removes and returns the first passenger from the queue *q.
// requires: queue must not be empty
// effects:  mutates *q
//           allocates heap memory [client must call passenger_destroy]
// time:     O(m), where m is the number of queued passengers
struct passenger *queue_dequeue(struct queue *q);

// queue_front(q) returns a copy of the first passenger from the queue *q.
// requires: queue must not be empty
// effects:  allocates heap memory [client must call passenger_destroy]
// time:     O(n), where n is the length of the passenger's name
struct passenger *queue_front(const struct queue *q);

// queue_empty(q) returns true if the queue *q is empty, and false otherwise.
// time: O(1)
bool queue_is_empty(const struct queue *q);

// queue_print(q) prints out the queue *q.
// effects: produces output
// time:    O(m * n) where m is the number of queued passengers and n is the
//          longest passenger name
void queue_print(const struct queue *q);

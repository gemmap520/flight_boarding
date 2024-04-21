#include <stdbool.h>
#include "passenger.h"

// pqueue represents a priority queue for passengers
struct pqueue;

// pqueue_create() returns a new (empty) priority queue.
// requires: num_zones must be positive
// effects:  allocates heap memory [client must call pqueue_destroy]
// time:     O(k) where k is the number of zones
struct pqueue *pqueue_create(int num_zones);

// pqueue_destroy(pq) frees all resources used by the priority queue *pq.
// effects: *pq becomes invalid
// time:    O(k + n) where k is the number of zones and n is the number
//          of queued passengers
void pqueue_destroy(struct pqueue *pq);

// pqueue_enqueue(pq, name, zone) adds a new passenger with name and zone
//   into the priority queue *pq.
// requires: 1 <= zone <= num_zones
//           name is unique [not asserted]
// effects:  mutates *pq, allocates memory
// time:     ???
void pqueue_enqueue(struct pqueue *pq, const char *name, int zone);

// pqueue_dequeue(pq) removes and returns the first passenger in the the
//   priority queue *pq.
// requires: *pq must not be empty
// effects:  mutates *pq
//           client must call passenger_destroy on returned passenger
// time:     O(k + n) where k is the number of zones and n is the number
//           of queued passengers
struct passenger *pqueue_dequeue(struct pqueue *pq);

// pqueue_front(pq) returns the first passenger in the priority queue *pq.
// requires: *pq must not be empty
//           client must call passenger_destroy on returned passenger
// time:     O(k + m) where k is the number of zones and m is the length
//           of the passenger's name
struct passenger *pqueue_front(const struct pqueue *pq);

// pqueue_is_empty(pq) returns true if the priority queue *pq is empty, and
//   false otherwise.
// time: O(k) where k is the number of zones
bool pqueue_is_empty(const struct pqueue *pq);

// pqueue_print(pq) prints out the priority queue *pq.
// effects: produces output
// time:    O(k + m * n) where k is the number of zones, n is the number of
//          queued passengers, and m is the longest passenger name
void pqueue_print(const struct pqueue *pq);

// pqueue_upgrade(pq, name, new_zone) upgrades passenger named name to
//   new_zone. Returns true if upgrade was successfull and false otherwise
//   (e.g., there is no passenger of this name or the passenger is already
//   in new_zone or lower).
// requires: 1 <= new_zone < num_zones
// effects:  mutates *pq
// time:     ???
bool pqueue_upgrade(struct pqueue *pq, const char *name, const int new_zone);

#include <stdlib.h>
#include "passenger.h"
#include "queue.h"
#include "pqueue.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

// pqueue represents a priority queue for passengers
struct pqueue {
  struct queue **zones;
  int max_zone;
};

// pqueue_create() returns a new (empty) priority queue.
// requires: num_zones must be positive
// effects:  allocates heap memory [client must call pqueue_destroy]
// time:     O(k) where k is the number of zones
struct pqueue *pqueue_create(const int num_zones) {
  assert(num_zones >= 1);
  struct pqueue *pq = malloc(sizeof(struct pqueue));
  assert(pq != NULL);
  pq->max_zone = num_zones;
  pq->zones = malloc(sizeof(struct queue*) * num_zones);
  for (int i = 0; i < num_zones; i++) {
    pq->zones[i] = queue_create();
  }
  return pq;
}

// pqueue_destroy(pq) frees all resources used by the priority queue *pq.
// effects: *pq becomes invalid
// time:    O(k + n) where k is the number of zones and n is the number
//          of queued passengers
void pqueue_destroy(struct pqueue *pq) {
  assert(pq != NULL);
  for (int i = 0; i < pq->max_zone; ++i) {
    queue_destroy(pq->zones[i]);
  }
  free(pq->zones);
  free(pq);
}

// pqueue_enqueue(pq, name, zone) adds a new passenger with name and zone
//   into the priority queue *pq.
// requires: 1 <= zone <= num_zones
//           name is unique [not asserted]
// effects:  mutates *pq, allocates memory
// time:    O(1) [amortized]
void pqueue_enqueue(struct pqueue *pq, const char *name, int zone) {
  assert(pq != NULL);
  assert(name != NULL);
  assert(1 <= zone);
  assert(zone <= pq->max_zone);
  queue_enqueue(pq->zones[zone - 1], name, zone);
}

// pqueue_dequeue(pq) removes and returns the first passenger in the the
//   priority queue *pq.
// requires: *pq must not be empty
// effects:  mutates *pq
//           client must call passenger_destroy on returned passenger
// time:     O(k + n) where k is the number of zones and n is the number
//           of queued passengers
struct passenger *pqueue_dequeue(struct pqueue *pq) {
  assert(pq != NULL);
  for (int i = 0; i < pq->max_zone; ++i) {
    if (!queue_is_empty(pq->zones[i])) {
      return queue_dequeue(pq->zones[i]);
    }
  }
  return NULL;
}

// pqueue_front(pq) returns the first passenger in the priority queue *pq.
// requires: *pq must not be empty
//           client must call passenger_destroy on returned passenger
// time:     O(k + m) where k is the number of zones and m is the length
//           of the passenger's name
struct passenger *pqueue_front(const struct pqueue *pq) {
  assert(pq != NULL);
  for (int i = 0; i < pq->max_zone; ++i) {
    if (!queue_is_empty(pq->zones[i])) {
      return queue_front(pq->zones[i]);
    }
  }
  return NULL;
}

// pqueue_is_empty(pq) returns true if the priority queue *pq is empty, and
//   false otherwise.
// time: O(k) where k is the number of zones
bool pqueue_is_empty(const struct pqueue *pq) {
  assert(pq != NULL);
  for (int i = 0; i < pq->max_zone; ++i) {
    if (!queue_is_empty(pq->zones[i])) {
      return false;
    }
  }
  return true;
}

// pqueue_print(pq) prints out the priority queue *pq.
// effects: produces output
// time:    O(k + m * n) where k is the number of zones, n is the number of
//          queued passengers, and m is the longest passenger name
void pqueue_print(const struct pqueue *pq) {
  assert(pq != NULL);
  for (int i = 0; i < pq->max_zone; ++i) {
    printf("Zone %d: ", i + 1);
    if (!queue_is_empty(pq->zones[i])) {
      queue_print(pq->zones[i]);
    } else {
      printf("Queue\n");
    }
  }
}

// pqueue_upgrade(pq, name, new_zone) upgrades passenger named name to
//   new_zone. Returns true if upgrade was successfull and false otherwise
//   (e.g., there is no passenger of this name or the passenger is already
//   in new_zone or lower).
// requires: 1 <= new_zone < num_zones
// effects:  mutates *pq
// time:     O(k * n) where k is number of zones, and n is number of passengers
bool pqueue_upgrade(struct pqueue *pq, const char *name, const int new_zone) {
  assert(pq != NULL);
  assert(name != NULL);
  assert(new_zone >= 1);
  assert(new_zone < pq->max_zone);
  
  bool upgraded = false;
  struct passenger *upgraded_passenger = NULL;
  for (int i = pq->max_zone - 1; i >= new_zone; --i) {
    struct queue *current_queue = pq->zones[i];
    struct queue *temp_queue = queue_create();
    bool found = false;
    
    while (!queue_is_empty(current_queue)) {
      struct passenger *p = queue_dequeue(current_queue);
      if (strcmp(passenger_name(p), name) == 0) {
        upgraded_passenger = p;
        found = true;
        upgraded = true;
        break;
      } else {
        queue_enqueue(temp_queue, passenger_name(p), passenger_zone(p));
        passenger_destroy(p);
      }
    }
    
    while (!queue_is_empty(temp_queue)) {
      struct passenger *p = queue_dequeue(temp_queue);
      queue_enqueue(current_queue, passenger_name(p), passenger_zone(p));
      passenger_destroy(p);
    }
    
    queue_destroy(temp_queue);
    if (found) {
      break;
    }
  }
  
  if (upgraded_passenger != NULL) {
    queue_enqueue(pq->zones[new_zone - 1], passenger_name(upgraded_passenger), new_zone);
    passenger_destroy(upgraded_passenger);
  }
  return upgraded;
}

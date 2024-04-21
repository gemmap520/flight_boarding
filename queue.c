#include "queue.h"
#include "passenger.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


// a queue for passengers
struct queue {
  struct passenger **data;
  int front;
  int back;
  int capacity;
};

// queue_create() creates a new empty queue.
// effects: allocates heap memory [client must call queue_destroy]
// time:    O(1)
struct queue *queue_create(void) {
  // Your implementation goes here
  struct queue *q = malloc(sizeof(struct queue));
  assert(q != NULL);
  q->capacity = 1;
  q->data = malloc(sizeof(struct passenger *));
  q->front = 0;
  q->back = 0;
  return q;
}

// queue_destroy(q) releases all resources used by *q.
// effects: invalidates *q
// time:    O(n), where n is the number of queued passengers
void queue_destroy(struct queue *q) {
  // Your implementation goes here
  assert(q != NULL);
  for (int i = q->front; i < q->back; ++i) {
    passenger_destroy(q->data[i]);
  }
  free(q->data);
  free(q);
}

// queue_enqueue(q, name, zone) adds a passenger with name and zone to the end
//    of the queue *q.
// effects: mutates *q
// time:    O(1) [amortized]
void queue_enqueue(struct queue *q, const char *name, const int zone) {
  // Your implementation goes here
  assert(q);
  assert(name);
  assert(zone >= 1);

  if (q->back >= q->capacity) {
    q->capacity *= 2;
    q->data = realloc(q->data, q->capacity * sizeof(struct passenger *));
  }
  struct passenger *new = passenger_create(name, zone);
  q->data[q->back++] = new;
}

// queue_dequeue(q) removes and returns the first passenger from the queue *q.
// requires: queue must not be empty
// effects:  mutates *q
// time:     O(m), where m is the number of queued passengers
struct passenger *queue_dequeue(struct queue *q) {
  // Your implementation goes here
  assert(q != NULL);
  if (q->front == q->back) {
    return NULL;
  }
  return q->data[q->front++];
}

// See queue.h for documentation.
struct passenger *queue_front(const struct queue *q) {
  // Your implementation goes here
  if (q->back == q->front) {
    return NULL;
  }
  return passenger_clone(q->data[q->front]);
}

// See queue.h for documentation.
bool queue_is_empty(const struct queue *q) {
  // Your implementation goes here
  assert(q != NULL);
  return q->back == q->front;
}

// queue_print(q) prints out the queue *q.
// effects: produces output
// time:    O(m * n) where m is the number of queued passengers and n is the
//          longest passenger name
void queue_print(const struct queue *q) {
  assert(q != NULL);
  printf("Queue");
  for (int i = q->front; i < q->back; i++) {
    printf(" -> ");
    passenger_print(q->data[i]);
  }
  printf("\n");
}

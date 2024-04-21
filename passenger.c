#include "passenger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A record for a passenger
struct passenger {
  char *name;
  int zone;
};

// passenger_create(name, zone) returns a new passenger with name and zone.
// requires: zone must be at least 1
// effects:  allocates heap memory [client must call passenger_destroy]
// time:     O(n), where n is the length of the passenger name
struct passenger *passenger_create(const char *name, const int zone) {
  // Your implementation goes here
  assert(name);
  assert(zone >= 1);
  struct passenger* new = malloc(sizeof(struct passenger));
  new->name = malloc(sizeof(char) * strlen(name) + 1);
  strcpy(new->name, name);
  new->zone = zone;
  return new;
}

// passenger_clone(p) returns a clone of *p.
// effects:  allocates heap memory [client must call passenger_destroy]
// time:     O(n), where n is the length of the passenger name
struct passenger *passenger_clone(const struct passenger *p) {
  // Your implementation goes here
  assert(p);
  struct passenger *cp = passenger_create(p->name, p->zone);
  return cp;
}

// passenger_zone(p) returns the zone of passenger *p.
// time:     O(1)
int passenger_zone(const struct passenger *p) {
  // Your implementation goes here
  assert(p);
  return p->zone;
}

// passenger_name(p) returns the name of passenger *p.
// time:     O(1)
const char *passenger_name(const struct passenger *p) {
  // Your implementation goes here
  assert(p);
  return p->name;
}

// passenger_destroy(p) releases all resources used by *p.
// effects:  *p becomes invalid
// time:     O(1)
void passenger_destroy(struct passenger *p) {
  // Your implementation goes here
  assert(p);
  free(p->name);
  free(p);
}

// passenger_print(p) prints the passenger *p to output.
// effects:  produces output
// time:     O(n), where n is the length of the passenger name
void passenger_print(const struct passenger *p) {
  assert(p);
  printf("%s (#%d)\n", p->name, p->zone);
}


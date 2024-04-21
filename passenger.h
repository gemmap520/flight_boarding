// A record for a passenger
struct passenger;

// passenger_create(name, zone) returns a new passenger with name and zone.
// requires: zone must be at least 1
// effects:  allocates heap memory [client must call passenger_destroy]
// time:     O(n), where n is the length of the passenger name
struct passenger *passenger_create(const char *name, const int zone);

// passenger_clone(p) returns a clone of *p.
// effects:  allocates heap memory [client must call passenger_destroy]
// time:     O(n), where n is the length of the passenger name
struct passenger *passenger_clone(const struct passenger *p);

// passenger_zone(p) returns the zone of passenger *p.
// time:     O(1)
int passenger_zone(const struct passenger *p);

// passenger_name(p) returns the name of passenger *p.
// time:     O(1)
const char *passenger_name(const struct passenger *p);

// passenger_destroy(p) releases all resources used by *p.
// effects:  *p becomes invalid
// time:     O(1)
void passenger_destroy(struct passenger *p);

// passenger_print(p) prints the passenger *p to output.
// effects:  produces output
// time:     O(n), where n is the length of the passenger name
void passenger_print(const struct passenger *p);

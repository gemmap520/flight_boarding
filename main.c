#include <assert.h>
#include <stdio.h>
#include "passenger.h"
#include "pqueue.h"

// The following commands are available:
// ENQUEUE <name:string> <zone:int>
//         Enqueues a new passenger with name (no more than 40 characters) and
//         zone.
// DEQUEUE
//         Dequeues and prints out the passenger with the highest priority.
// FRONT
//         Retrieces and prints out the passenger with the highest priority.
// UPGRADE <name:string> <zone:int>
//         Upgrades the existing passenger with name (no more than 40
//         characters) to zone.
// PRINT   Prints out the priority queue.
int main(void) {
    const int CMD_ENQ = lookup_symbol("ENQUEUE");
    const int CMD_DEQ = lookup_symbol("DEQUEUE");
    const int CMD_FRONT = lookup_symbol("FRONT");
    const int CMD_UPGRADE = lookup_symbol("UPGRADE");
    const int CMD_PRINT = lookup_symbol("PRINT");

    struct pqueue *pq = pqueue_create(5);
    int cmd;

    while ((cmd = read_symbol()) == 1) {
        if (cmd == CMD_ENQ) {
            char name[40 + 1] = {'\0'};
            int zone = -1;
            assert(scanf("%40s%d", name, &zone) == 2);
            pqueue_enqueue(pq, name, zone);
        } else if (cmd == CMD_DEQ) {
            struct passenger *p = pqueue_dequeue(pq);
            printf("Serving passenger: ");
            passenger_print(p);
            passenger_destroy(p);
        } else if (cmd == CMD_FRONT) {
            struct passenger *p = pqueue_front(pq);
            printf("Next passenger is: ");
            passenger_print(p);
            passenger_destroy(p);
        } else if (cmd == CMD_UPGRADE) {
            char name[40 + 1] = {'\0'};
            int new_zone = 0;
            assert(scanf("%40s%d", name, &new_zone) == 2);
            if (pqueue_upgrade(pq, name, new_zone) == true) {
                printf("Upgrade sucessful.\n");
            } else {
                printf("Upgrade failed.\n");
            }
        } else if (cmd == CMD_PRINT) {
            pqueue_print(pq);
        } else {
            printf("ERROR: unknown command!\n");
            break;
        }
    }
    pqueue_destroy(pq);
}

/* pqueue.h
 * Interface for a priority queue.
 * Homework assigned 2/8/17
 */
#include <stdbool.h>
#include "graph.h"

// ------- ELEMENTS OF PQUEUE ------

typedef struct data {
	Vertex *v;
	int weight;
} Data;

// Returns the actual data struct, not a pointer to it.
Data makeData(Vertex *v, int weight);

// --------- PQUEUE METHODS ---------
// You may assume that the priority queue will never have to hold
// more than 100 elements.

// Represents a priority queue.
typedef struct pqueue *PQueue;

// Returns a newly allocated empty priority queue.
PQueue makeEmptyPQueue();

// Determines whether the priority queue is empty.
bool isEmpty(PQueue q);

// Adds an element to the priority queue.
void addToPQueue(PQueue q, Data d);

// Decreases priority of Data d;
void decreasePriority(PQueue q, Data d);

// Returns min-weight element.
Data peekMin(PQueue q);

// Removes and returns min-weight element.
Data removeMin(PQueue q);

// Returns the number of elements in the priority queue.
int pqLength(PQueue q);

// Frees the priority queue
void freePQueue(PQueue q);

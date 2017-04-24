/* pqueue.c
 * Implementation of a priority queue.
 * Homework assigned 2/8/17
 */

#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define INITIALCAPACITY 100
#define min(a, b) ((a < b) ? a : b)

Data makeData(Vertex *v, int weight) {
	Data data = {v, weight};
	return data;
}

// Your code here:

void swap(Data *a, Data *b) {
	Data x = *a;
	*a = *b;
	*b = x;
}

typedef struct pqueue {
	Data *data;
	int length;
	int capacity;
} pqueue;

int getDepth(PQueue q, int index) {
	return log2(index) + 1;
}

int getLeftChild(Data *d, int length, int index) {
	int value = index * 2 + 1;
	if (value >= length) {
		return -1;
	} else {
		return value;
	}
}

int getRightChild(Data *d, int length, int index) {
	int value = index * 2 + 2;
	if (value >= length) {
		return -1;
	} else {
		return value;
	}
}

int getParent(PQueue q, int index) {
	if (index == 0) {
		return -1;
	} else {
		return (index - 1) / 2;
	}
}

// Returns a newly allocated empty priority queue.
PQueue makeEmptyPQueue() {
	PQueue newPQueue= (PQueue) malloc(sizeof(pqueue));
	newPQueue->data = (Data*) malloc(sizeof(Data) * INITIALCAPACITY);
	newPQueue->length = 0;
	newPQueue->capacity = INITIALCAPACITY;
	return newPQueue;
}

// Determines whether the priority queue is empty.
bool isEmpty(PQueue q) {
	return q->length == 0;
}

void siftUp(PQueue q, int index) {
	int parentIndex = getParent(q, index);
	if (parentIndex != -1) {
		if (q->data[parentIndex].weight > q->data[index].weight) {
			swap(&q->data[parentIndex], &q->data[index]);
		}
	} else {
		return;
	}
	siftUp(q, parentIndex);
}

// Adds an element to the priority queue.
void addToPQueue(PQueue q, Data d) {
	if (q->length == q->capacity) {
		// to be implemented: expanding arrays.
		fprintf(stderr, "Attempted to add elements beyond capacity\n");
		exit(1);
	}
	q->data[q->length] = d;
	siftUp(q, q->length);
	q->length += 1;
}

// Decreases the priority of a Data element of the priority queue.
void decreasePriority(PQueue q, Data d) {
	for (int i = 0; i < q->length; i++) {
		if (q->data[i].v == d.v) {
			q->data[i] = d;
			siftUp(q, i);
		}
	}
}

void siftDown(Data* data, int length, int index) {
	int leftChildIndex = getLeftChild(data, length, index);
	int rightChildIndex = getRightChild(data, length, index);
	if (leftChildIndex == -1 && rightChildIndex == -1) {
		return;
	} else if (rightChildIndex == -1) {
		if (data[0].weight > data[leftChildIndex].weight) {
			swap(&data[0], &data[leftChildIndex]);
			siftDown(data, length, leftChildIndex);
		}
	} else {
		int minValueIndex = min(leftChildIndex, rightChildIndex);
		if (data[0].weight > data[minValueIndex].weight) {
			swap(&data[0], &data[minValueIndex]);
			siftDown(data, length, minValueIndex);
		}
	}
}


// Returns min-weight element.
Data peekMin(PQueue q) {
	return q->data[0];
}

// Removes and returns min-weight element.
Data removeMin(PQueue q) {
	Data firstElem = q->data[0];
	Data lastElem = q->data[q->length - 1];
	q->data[0] = lastElem;
	q->data[q->length - 1] = firstElem;
	q->length -= 1;
	siftDown(q->data, q->length, 0);
	return firstElem;
}

// Returns the number of elements in the priority queue.
int pqLength(PQueue q) {
	return q->length;
}

void freePQueue(PQueue q) {
	free(q->data);
	free(q);
}

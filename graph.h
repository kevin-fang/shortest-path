#include <stdio.h>

#ifndef graph_h
#define graph_h

typedef struct vertex Vertex;

// Each vertex keeps a linked list of adjacent vertices.
// Each node in the linked list contains:
//   (a) a pointer to the vertex at the edge's endpoint
//   (b) the weight of the edge connecting you to this neighbor
//   (c) a pointer to the next node in the list.
typedef struct node {
    Vertex *v;
    int edgeWeight;
    struct node *next;
} *List;

// A vertex contains an "info" field -- its "name" -- as well as
// a linked list of adjacent vertices.
struct vertex {
    int info;
    List adjacentVertices;
};

// A graph contains a number of vertices, n, and an array of vertex structs.
typedef struct graph {
  int numVertices; // number of vertices
  Vertex *vertices;
} Graph;

#endif

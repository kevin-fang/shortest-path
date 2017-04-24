#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pqueue.h"
#include "graph.h"

Graph *makeGraph(int numVertices, int *vertexInfo) {
  Vertex *vertices = malloc(sizeof(*vertices) * numVertices);
  for (int i = 0; i < numVertices; i++) {
    vertices[i].info = vertexInfo[i];
    vertices[i].adjacentVertices = NULL;
  }

  Graph *g = malloc(sizeof(*g));
  g->numVertices = numVertices;
  g->vertices = vertices;
  return g;
}

void addDirectedEdge(Vertex *v, Vertex *u, int edgeWeight) {
  List newNode = malloc(sizeof(*newNode));
  newNode->v = u;
  newNode->edgeWeight = edgeWeight;
  newNode->next = v->adjacentVertices;
  v->adjacentVertices = newNode;
}

void addUndirectedEdge(Vertex *v, Vertex *u, int edgeWeight) {
  addDirectedEdge(v, u, edgeWeight);
  addDirectedEdge(u, v, edgeWeight);
}

void addUndirectedEdgeWithIndices(Graph *g, int i, int j, int edgeWeight) {
  addUndirectedEdge(&g->vertices[i], &g->vertices[j], edgeWeight);
}

void addDirectedEdgeWithIndices(Graph *g, int i, int j, int edgeWeight) {
  addDirectedEdge(&g->vertices[i], &g->vertices[j], edgeWeight);
}

void printGraph(Graph *g) {
  for (int i = 0; i < g->numVertices; i++) {
    Vertex v = g->vertices[i];
    printf("Vertex %d: (%d).\n", i, v.info);
    printf("\tAdjacent to: ");
    List next = v.adjacentVertices;
    while (next) {
      printf("%d (weight %d), ", next->v->info, next->edgeWeight);
      next = next->next;
    }
    puts("");
  }
}

void shortestPath(Graph *g, Vertex *s) {
  PQueue pq = makeEmptyPQueue();
  addToPQueue(pq, makeData(s, 0));
  for (int i = 0; i < g->numVertices; i++) {
    Vertex *v = &g->vertices[i];
    if (v != s) {
      addToPQueue(pq, makeData(v, INT_MAX));
    }
  }
  while (!isEmpty(pq)) {
    Data d = removeMin(pq);
    printf("Info: %d; Distance from s: %d\n", d.v->info, d.weight);
    List toIncrement = d.v->adjacentVertices;
    while (toIncrement) {
      decreasePriority(pq, makeData(toIncrement->v, d.weight + toIncrement->edgeWeight));
      toIncrement = toIncrement->next;
    }
  }
}


int main(int argc, char *argv[]) {
  int nodeInfo[] = {0, 1, 2, 3, 4, 5};
  Graph *g = makeGraph(6, nodeInfo);
  addUndirectedEdgeWithIndices(g, 1, 5, 2);
  addUndirectedEdgeWithIndices(g, 1, 3, 5);
  addUndirectedEdgeWithIndices(g, 3, 2, 2);
  addUndirectedEdgeWithIndices(g, 0, 1, 4);
  addUndirectedEdgeWithIndices(g, 0, 4, 1);
  shortestPath(g, &g->vertices[0]);
  //printGraph(g);
}

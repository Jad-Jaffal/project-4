#include "main.h"

void readFile(Graph *graph) {
  FILE *file;
  char line[300];

  file = fopen("input_buildings.txt", "r");
  // check if fill is NULL
  if (file == NULL) {
    printf("error opening the file\n");
    return;
  }
  printf("file uploaded\n");
  // read each line and use strtok to devide the info
  while (fgets(line, sizeof(line), file)) {
    char *src = strtok(line, "#");
    char *dest = strtok(NULL, "#");
    int weight = atoi(strtok(NULL, "#"));
    addEdge(graph, src, dest, weight);
  }
  fclose(file);
}

Vertex *getOrInsertVertex(Graph *graph, char *name) {
  // if head is Null allocate new node
  if (!graph->vertices) {
    graph->vertices = newVertex(name);
    graph->V++;
    return graph->vertices;
  }
  Vertex *curr = graph->vertices;
  Vertex *parent = NULL;
  while (curr != NULL) {
    if (strcmp(curr->name, name) == 0) {
      return curr;
    }
    parent = curr;
    curr = curr->next;
  }
  curr = newVertex(name);
  if (parent)
    parent->next = curr;

  graph->V++;
  return curr;
}

Graph *createGraph() {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->vertices = NULL;
  graph->V = 0;
  return graph;
}

Vertex *newVertex(char *name) {
  Vertex *newNode = (Vertex *)malloc(sizeof(Vertex));
  strcpy(newNode->name, name);
  newNode->visited = 0;
  newNode->distance = INF;
  newNode->edges = NULL;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

Edge *newEdge(char *dest, int weight) {
  Edge *newNode = (Edge *)malloc(sizeof(Edge));
  strcpy(newNode->dest, dest);
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

void addEdge(Graph *graph, char *src, char *dest, int weight) {
  Vertex *srcVertex = getOrInsertVertex(graph, src);
  Edge *current = srcVertex->edges;
  Edge *parent = srcVertex->edges;
  while (current) {
    if (strcmp(current->dest, dest) == 0)
      return;
    parent = current;
    current = current->next;
  }
  current = newEdge(dest, weight);
  if (parent)
    parent->next = current;
  if (!srcVertex->edges)
    srcVertex->edges = current;
}

void printGraph(Graph *graph) {
  Vertex *temp = graph->vertices;
  while (temp != NULL) {
    printf("From: %s\n", temp->name);
    Edge *tempDis = temp->edges;
    while (tempDis != NULL) {
      printf("to: %s, distance: %d\n", tempDis->dest, tempDis->weight);
      tempDis = tempDis->next;
    }
    temp = temp->next;
  }
}
Vertex *minDistanceVertex(Graph *graph) {
  Vertex *minVertex = NULL;
  int minDist = INF;
  Vertex *temp = graph->vertices;
  while (temp != NULL) {
    if (!temp->visited && temp->distance <= minDist) {
      minDist = temp->distance;
      minVertex = temp;
    }
    temp = temp->next;
  }
  return minVertex;
}

void printPath(Vertex *dest) {
  if (dest->prev != NULL) { // Recursively print the path
    printPath(dest->prev);
    printf(" -> ");
  }
  printf("%s", dest->name);
}

void dijkstra(Graph *graph, char *src, char *dist) {
  Vertex *srcVertex = getOrInsertVertex(graph, src);
  Vertex *distVertex = getOrInsertVertex(graph, dist);
  Vertex *temp = graph->vertices;

  if (srcVertex == NULL || distVertex == NULL) {
    printf("Source or destination vertex not found.\n");
    return;
  }

  srcVertex->distance = 0;
  for (int i = 0; i < graph->V; i++) {
    Vertex *min = minDistanceVertex(graph);
    if (min == NULL)
      break;
    min->visited = 1;
    Edge *neighbors = min->edges;
    while (neighbors) {
      Vertex *v = getOrInsertVertex(graph, neighbors->dest);
      if (v && !v->visited && min->distance != INF &&
          min->distance + neighbors->weight < v->distance) {
        v->distance = min->distance + neighbors->weight;
        v->prev = min;
      }
      neighbors = neighbors->next;
    }
  }
  if (distVertex->distance == INF) {
    printf("No path from %s to %s\n", src,
           dist); // Check if distVertex is reachable
  } else {
    printf("Shortest path from %s to %s is %d\n", src, dist,
           distVertex->distance);
    printf("Path: ");
    printPath(distVertex); // Print the path
    printf("\n");
  }
}

int main(void) {
  Graph *graph = createGraph();
  readFile(graph);
  // printGraph(graph);
  dijkstra(graph, "Masri", "Alsadik");
  return 0;
}

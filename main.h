#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000

typedef struct Edge {
  char dest[100];
  int weight;
  struct Edge *next;
} Edge;

typedef struct Vertex {
  char name[100];
  int visited;
  int distance;
  Edge *edges;
  struct Vertex *next;
  struct Vertex *prev;
} Vertex;

typedef struct Graph {
  Vertex *vertices;
  int V;
} Graph;

typedef struct Node {
  char name[100];
  struct Node *next;
} Node;

// definition of queue
typedef struct {
  Node *front;
  Node *rear;
} Queue;

void readFile(Graph *);
Vertex *getOrInsertVertix(Graph *, char *);
Graph *createGraph();
Vertex *newVertex(char *);
Edge *newEdge(char *, int);
void addEdge(Graph *, char *, char *, int);
void printGraph(Graph *);
void dijkstra(Graph *, char *, char *);
Vertex *minDistanceVertex(Graph *);
void printPath(Vertex *);

// void enqueue(Queue *queue, char *word) {
//   // creat a new node
//   Node *newNode = createNode(word);
//   // add node to queue
//   if (queue->front == NULL) {
//     queue->front = newNode;
//     queue->rear = newNode;
//   } else {
//     queue->rear->next = newNode;
//     queue->rear = newNode;
//   }
// }

// // function to dequeue a node and send it to stack
// char *dequeue(Queue *queue) {
//   // check if queue is empty
//   if (queue->front == NULL) {
//     return NULL;
//   }
//   // return the nods value value
//   Node *temp = queue->front;
//   char *word = temp->name;
//   queue->front = temp->next;
//   free(temp);
//   return word;
// }

// // function to creat a new node
// Node *createNode(char *word) {
//   Node *newNode = (Node *)malloc(sizeof(Node));
//   // check if node was made
//   if (newNode == NULL) {
//     printf("no space available");
//     return NULL;
//   }
//   strcpy(newNode->name, word);
//   // defualt values
//   newNode->next = NULL;
//   return newNode;
// }

// int isQueueEmpty(Queue *queue) { return queue->front == NULL; }
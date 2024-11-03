#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int    data;
  struct node *next;
} node_t;

node_t* append(node_t *startNode){
  node_t *newNode = malloc(sizeof(node_t));
  scanf("%d", &newNode -> data);
  newNode -> next = NULL;
  if (startNode == NULL){
    return newNode;
  }

  node_t *tmp = startNode;
  while (tmp -> next != NULL){
    tmp = tmp -> next;
  }
  tmp -> next = newNode;
  return startNode;
}

void get(node_t *startNode){
  node_t *tmp = startNode;
  int i, index;

  scanf("%d", &index);
  for (i = 1; i <= index; i++){
    tmp = tmp -> next;
  }
  printf("%d\n", tmp -> data);
}

void show(node_t *startNode){
  node_t *tmp = startNode;
  while (tmp != NULL){
    printf("%d", tmp -> data);
    tmp = tmp -> next;
  }
}

node_t* reverse(node_t *startNode){
  node_t *tmp = startNode;
  node_t *prev = NULL;
  node_t *next = NULL;

  if (startNode == NULL){
    return startNode;
  }

  while (tmp != NULL){
    next = tmp -> next;
    tmp -> next = prev;
    prev = tmp;
    tmp = next;
  }
  return prev;
}

node_t* cut(node_t *startNode){
  int start, stop, i;
  node_t *tmp = startNode;
  node_t *first = startNode;
  node_t *last = startNode;

  scanf("%d %d", &start, &stop);

  for (i = 1; i <= stop; i++){
    last = last -> next;
  }
  last -> next = NULL;

  for (i = 0; i < start; i++){
    if (i == start - 1){
      tmp = first -> next;
      first -> next = NULL;
      break;
    }
    first = first -> next;
  }
  startNode = tmp;
  return startNode;
}

int main(void) {
  node_t *startNode;
  int    n,i;
  char   command;
  startNode = NULL;
  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf(" %c", &command);
    switch (command) {
      case 'A':
        startNode = append(startNode);
        break;
      case 'G':
        get(startNode);
        break;
      case 'S':
        show(startNode);
        break;
      case 'R':
        startNode = reverse(startNode);
        break;
      case 'C':
        startNode = cut(startNode);
        break;
      default:
        break;
} }
return 0; }

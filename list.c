#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* list = (List*) malloc (sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  list->current = list->head;
  if(list->current)
    return list->current->data;
  return NULL;
}

void * nextList(List * list) {
  if(list->current != NULL)
    list->current = list->current->next;
  if(list->current != NULL)
    return list->current->data;
  return NULL;
}

void * lastList(List * list) {
  while(list->current->next != NULL){
    list->current = list->current->next;
  }
  return list->current->data;
}

void * prevList(List * list) {
  if(list->current != NULL)
    list->current = list->current->prev;
  if(list->current != NULL)
    return list->current->data;
  return NULL;
}

void pushFront(List * list, void * data) {
  Node* nuevoN = createNode(data);
  nuevoN->prev = NULL;
  nuevoN->next = list->head;
  if(list->head) list->head->prev = nuevoN;
  list->head = nuevoN;
  list->tail = nuevoN;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node* nuevoN = createNode(data);
  list->current->next = nuevoN;
  nuevoN->prev = list->current;
  list->tail = nuevoN;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL) {
      return NULL;
  }
  Node *aux = list->current;
  if (list->current->prev == NULL) {
      list->head = list->current->next;
  } else {
    list->current->prev->next = list->current->next;
  }
  if (list->current->next == NULL) {
      list->tail = list->current->prev;
  } else {
    list->current->next->prev = list->current->prev;
  }
  return aux->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
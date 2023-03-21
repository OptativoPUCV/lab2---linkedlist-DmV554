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
     List* lista = malloc(sizeof(List)); 
      lista->head = NULL; 
      lista->tail = NULL; 
      lista->current = NULL; 
  return lista;
  
}

void * firstList(List * list) {
  if(list == NULL || list->head == NULL ) {
    return NULL;
  }

    list->current = list->head;
  
    return list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL; 
    }

    list->current = list->current->next;

    return list->current->data;
}

void * lastList(List * list) {
  if (list == NULL || list->current == NULL || list->tail == NULL) {
        return NULL; 
    }
  
   list->current = list->tail;
  
    return list->current->data;
}

void * prevList(List * list) {
  if (list == NULL || list->current == NULL || list->current->prev == NULL) {
        return NULL; 
    }

  list->current = list->current->prev;
  
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * nodoAInsertar = createNode(data);

  nodoAInsertar->prev = NULL;
  nodoAInsertar->next = list->head;
  
  if (list->head != NULL) {
        list->head->prev = nodoAInsertar;
    } else {
      list->tail = nodoAInsertar;
    }

   list->head = nodoAInsertar;
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * nodoAInsertar = createNode(data);
  
   nodoAInsertar->prev = NULL;
   nodoAInsertar->next = NULL;
  
  if(list->current != NULL) {
    nodoAInsertar->next = list->current->next;
    nodoAInsertar->prev = list->current;
    
    if(list->current->next != NULL) {
      list->current->next->prev = nodoAInsertar;
    } else {
      list->tail = nodoAInsertar;
    }
    
    list->current->next = nodoAInsertar;
    
  } else {
    list->tail = nodoAInsertar;
    list->head = nodoAInsertar;
    list->current = nodoAInsertar;
  }
  
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

  if(list == NULL || list->current == NULL) {
    return NULL;
  }

  if(list->current == list->head) {
    list->head = list->current->next;
  }

  if(list->current == list->tail) {
    list->tail = list->current->prev;
  }

  if(list->current->prev != NULL) {
    list->current->prev = list->current->next;
  }

  if(list->current->next != NULL) {
    list->current->next->prev = list->current->prev;
  }


  if(list->current->next != NULL) {
    list->current = list->current->next;
  }

  free(list->current);
  
  return list->current->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
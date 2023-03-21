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

   if (list == NULL || list->current == NULL) {
        return NULL; // Si la lista o el current son nulos, no se puede hacer nada
    }
   
    void * dato = list->current->data;
    if (list->current == list->head && list->current == list->tail) {
        // Si solo hay un nodo en la lista, hay que inicializar la lista vacía
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    } else if (list->current == list->head) {
        // Si el current es el primer nodo de la lista
        list->head = list->current->next;
        list->head->prev = NULL;
        list->current = list->head;
    } else if (list->current == list->tail) {
        // Si el current es el último nodo de la lista
        list->tail = list->current->prev;
        list->tail->next = NULL;
        list->current = list->tail;
    } else {
        // Si el current está en algún lugar intermedio de la lista
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current = list->current->next;
    }
    free(list->current); // Liberar la memoria del nodo eliminado
    return dato;


}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
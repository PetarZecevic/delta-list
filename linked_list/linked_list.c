/*
 * linked_list.c
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */
#include "linked_list.h"
#include <stdlib.h>

void SingleLinkedList_Initialize(SingleLinkedList_t* list, void (*destroy)(void* data))
{
  list->head = NULL;
  list->destroy = destroy;
}

void SingleLinkedList_Insert(SingleLinkedList_t* list, ListElement_t* element, void* data)
{
  ListElement_t* tmpElement = (ListElement_t*)malloc(sizeof(ListElement_t));
  tmpElement->data = data;
  if(element == NULL)
  {
      // Ubacuje na pocetak liste, pa je potrebno azurirati glavu.
      tmpElement->next = list->head;
      list->head = tmpElement;
  }
  else{
      // Ubacuje posle prvog elementa.
      tmpElement->next = element->next;
      element->next = tmpElement;
  }
}

void SingleLinkedList_Destroy(SingleLinkedList_t* list)
{
  ListElement_t* iterator = list->head;
  ListElement_t* elementToDelete = NULL;
  while(iterator != NULL)
  {
      elementToDelete = iterator;
      iterator = iterator->next;
      list->destroy(elementToDelete->data);
      free(elementToDelete);
  }
  list->head = NULL;
}

void SingleLinkedList_Delete(SingleLinkedList_t* list, ListElement_t* element)
{
  if(element == NULL)
  {
      // Brisanje prvog elementa.
      element = list->head;
      list->head = list->head->next;
      free(element);
  }
  else if(element->next != NULL)
  {
      // Brisanje ostalih elemenata.
      element->next = element->next->next;
      free(element);
  }
}

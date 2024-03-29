/*
 * linked_list.c
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */
#include <stdlib.h>
#include <assert.h>

#include "linked_list.h"

void SingleLinkedList_Initialize(SingleLinkedList_t* list, void (*destroy)(void* data))
{
  assert(list != NULL);
  list->head = NULL;
  list->destroy = destroy;
}

void SingleLinkedList_Insert(ListElement_t** currentElement, void* newData)
{
  assert(currentElement != NULL);
  ListElement_t* newElement = (ListElement_t*)malloc(sizeof(ListElement_t));
  assert(newElement != NULL);
  if(newElement != NULL)
  {
      newElement->data = newData;
      newElement->next = *currentElement;
      *currentElement = newElement;
  }
}

void SingleLinkedList_Destroy(SingleLinkedList_t* list)
{
  assert(list != NULL);
  ListElement_t* iterator = list->head;
  ListElement_t* elementToDelete = (ListElement_t*)NULL;
  while(iterator != NULL)
  {
      elementToDelete = iterator;
      iterator = iterator->next;
      if(list->destroy != NULL)
      {
          list->destroy(elementToDelete->data);
      }
      free(elementToDelete);
  }
  list->head = (ListElement_t*)NULL;
}

void SingleLinkedList_Delete(const SingleLinkedList_t* list, ListElement_t** element)
{
  assert(list != NULL);
  assert(element != NULL);
  assert(*element != NULL);
  ListElement_t* tmpElement = *element;
  *element = (*element)->next;
  if(list->destroy != NULL)
  {
      list->destroy(tmpElement->data);
  }
  free(tmpElement);
}

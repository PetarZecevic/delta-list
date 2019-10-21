/*
 * delta_list.c
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */
#include <stdlib.h>
#include "delta_list.h"
#include "assert.h"

static void destroyDeltaElement(void* element)
{
  DeltaElement_t* deltaElement = (DeltaElement_t*)element;
  free(deltaElement->object);
  free(deltaElement);
}

void DeltaList_Initialize(DeltaList_t* deltaList)
{
  assert(deltaList != NULL);
  SingleLinkedList_Initialize(&(deltaList->rawList), &destroyDeltaElement);
}

void DeltaList_Add(DeltaList_t* deltaList, DeltaElement_t* newDeltaElement)
{
  assert(deltaList != NULL);
  assert(newDeltaElement != NULL);
  ListElement_t** currentRawElement = &(deltaList->rawList.head);
  DeltaElement_t* currentDeltaElement = NULL;
  while(*currentRawElement != NULL)
  {
      currentDeltaElement = (DeltaElement_t*)((*currentRawElement)->data);
      if(newDeltaElement->delay > currentDeltaElement->delay)
      {
          newDeltaElement->delay = UINT16_C(newDeltaElement->delay - currentDeltaElement->delay);
          currentRawElement = &((*currentRawElement)->next);
      }
      else
      {
          currentDeltaElement->delay = UINT16_C(currentDeltaElement->delay - newDeltaElement->delay);
          break;
      }
  }
  SingleLinkedList_Insert(currentRawElement, newDeltaElement);
}

void DeltaList_Destroy(DeltaList_t* deltaList)
{
  assert(deltaList != NULL);
  SingleLinkedList_Destroy(&(deltaList->rawList));
}

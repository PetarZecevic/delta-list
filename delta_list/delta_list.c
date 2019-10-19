/*
 * delta_list.c
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */
#include <stdlib.h>
#include "delta_list.h"

static void destroyDeltaElement(void* element)
{
  DeltaElement_t* deltaElement = (DeltaElement_t*)element;
  free(deltaElement->object);
  free(deltaElement);
}

void DeltaList_Initialize(DeltaList_t* deltaList)
{
  SingleLinkedList_Initialize(&(deltaList->rawList), &destroyDeltaElement);
}

void DeltaList_Add(DeltaList_t* deltaList, DeltaElement_t* newDeltaElement)
{
  ListElement_t** currentRawElement = &(deltaList->rawList.head);
  /*TODO: Process delta list to find correct position for new element.*/
  SingleLinkedList_Insert(currentRawElement, newDeltaElement);
}

void DeltaList_Destroy(DeltaList_t* deltaList)
{
  SingleLinkedList_Destroy(&(deltaList->rawList));
}

/*
 * main.c
 *
 *  Created on: Oct 17, 2019
 *      Author: osboxes
 */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include "linked_list.h"

void testSingleLinkedList(void);
void testSingleInitializaton(void);
void testSingleInsertionAndDestroy(void);
void testSingleDeletion(void);

void main(void)
{
	printf("*** Running Tests ***\n");
	testSingleLinkedList();
}

void testSingleLinkedList(void)
{
	printf("\n - Testing Single Linked List\n");
	testSingleInitializaton();
	testSingleInsertionAndDestroy();
	testSingleDeletion();
}

void destroyFunc1(void* object)
{
	return;
}

void testSingleInitializaton(void)
{
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, (void(*)(void*))NULL);
	assert(list.head == (ListElement_t*)NULL);
	assert(list.destroy == NULL);

	SingleLinkedList_Initialize(&list, destroyFunc1);
	assert(list.destroy == destroyFunc1);
	list.destroy(NULL);
}

void destroyFunc2(void* object)
{
	free(object);
}

void testSingleInsertionAndDestroy(void)
{
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, destroyFunc2);

	// Kreiranje testnih objekata.
	uint_least8_t index;
	uint_least8_t* objects[3] = {(uint_least8_t*)NULL, (uint_least8_t*)NULL,
			(uint_least8_t*)NULL};
	for(index = 0; index < 3; index++)
	{
		objects[index] = (uint_least8_t*)malloc(sizeof(uint_least8_t));
		*(objects[index]) = index+1;
	}

	// Testiranje umetanja elementa na prvo mesto u listi.
	for(index = 0; index < 3; index++)
	{
		SingleLinkedList_Insert(&(list.head), objects[index]);
		assert(*((uint_least8_t*)list.head->data) == *(objects[index]));
	}
	ListElement_t* current = list.head;
	printf("\t");
	while(current != (ListElement_t*)NULL)
	{
		printf("%"PRIuLEAST16" ", *((uint_least8_t*)current->data));
		current = current->next;
	}
	printf("\n");

	// Testiranje oslobadjanja liste.
	SingleLinkedList_Destroy(&list);
	assert(list.head == (ListElement_t*)NULL);

	// Testiranje ubacivanja elemenata testnog vektora na mesta u listi na kojima se oni nalaze u vektoru.
	uint_least8_t testVector[] = {1, 2, 3};
	SingleLinkedList_Initialize(&list, NULL);

	SingleLinkedList_Insert(&(list.head), &testVector[0]);
	current = list.head;
	for(index = 1; index < 3; index++)
	{
		SingleLinkedList_Insert(&(current->next), &testVector[index]);
		current = current->next;
		assert(*((uint_least8_t*)current->data) == testVector[index]);
	}

	printf("\t");
	current = list.head;
	while(current != (ListElement_t*)NULL)
	{
		printf("%"PRIuLEAST16" ", *((uint_least8_t*)current->data));
		current = current->next;
	}
	printf("\n");

	SingleLinkedList_Destroy(&list);
	assert(list.head == (ListElement_t*)NULL);
}

void testSingleDeletion(void)
{
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, NULL);

	uint_least8_t testVector[] = {1, 2, 3};
	uint_least8_t index;
	for(index = 0; index < 3; index++)
	{
		SingleLinkedList_Insert(&(list.head), &testVector[index]);
	}

	// Brisanje glave liste tokom svake iteracije.
	for(index = 0; index < 3; index++)
	{
		assert(*((uint_least8_t*)list.head->data) == testVector[3-index-1]);
		SingleLinkedList_Delete(&list, &(list.head));
	}
	assert(list.head == (ListElement_t*)NULL);

	// Brisanje treceg i prvog elementa iz liste.
	for(index = 0; index < 3; index++)
	{
		SingleLinkedList_Insert(&(list.head), &testVector[index]);
	}
	ListElement_t* current = list.head;
	printf("\t");
	while(current != (ListElement_t*)NULL)
	{
		printf("%"PRIuLEAST16" ", *((uint_least8_t*)current->data));
		current = current->next;
	}
	printf("\n");

	SingleLinkedList_Delete(&list, &(list.head->next->next));
	SingleLinkedList_Delete(&list, &(list.head));
	assert(*((uint_least8_t*)list.head->data) == testVector[1]);
	assert(list.head->next == (ListElement_t*)NULL);
}




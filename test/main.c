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
#include <string.h>
#include "linked_list.h"
#include "delta_list.h"

static void testSingleLinkedList(void);
static void testSingleInitialize(void);
static void testSingleInsertAndDestroy(void);
static void testSingleDelete(void);
static void printSingleList(SingleLinkedList_t* list);
static void destroyFunc1(void* object);
static void destroyFunc2(void* object);

static void testDeltaList(void);
static void testDeltaInitialize(void);
static void testDeltaAddAndDestroy(void);
static void printDeltaList(DeltaList_t* deltaList);

void main(void)
{
	printf("*** Running Tests ***\n");
	testSingleLinkedList();
	testDeltaList();
}

static void testSingleLinkedList(void)
{
	printf("\n- Testing Single Linked List\n");
	testSingleInitialize();
	testSingleInsertAndDestroy();
	testSingleDelete();
}

static void testSingleInitialize(void)
{
	printf("\t Test initialize method\n");
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, NULL);
	assert(list.head == NULL);
	assert(list.destroy == NULL);
	printSingleList(&list);

	SingleLinkedList_Initialize(&list, &destroyFunc1);
	assert(list.destroy == &destroyFunc1);
	list.destroy(NULL);
	printSingleList(&list);
}

static void testSingleInsertAndDestroy(void)
{
	printf("\tTest insert and destroy methods\n");
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, &destroyFunc2);

	/*Kreiranje testnih objekata.*/
	uint_least8_t index;
	uint_least8_t* objects[3] = {(uint_least8_t*)NULL, (uint_least8_t*)NULL,
			(uint_least8_t*)NULL};
	for(index = UINT8_C(0); index < UINT8_C(3); index++)
	{
		objects[index] = (uint_least8_t*)malloc(sizeof(uint_least8_t));
		*(objects[index]) = index + UINT8_C(1);
	}

	/*Testiranje umetanja elementa na prvo mesto u listi.*/
	for(index = UINT8_C(0); index < UINT8_C(3); index++)
	{
		SingleLinkedList_Insert(&(list.head), objects[index]);
		assert(*((uint_least8_t*)list.head->data) == *(objects[index]));
	}
	printSingleList(&list);

	/*Testiranje oslobadjanja liste.*/
	SingleLinkedList_Destroy(&list);
	assert(list.head == NULL);
	printSingleList(&list);

	/*Testiranje ubacivanja elemenata testnog vektora na mesta u listi na kojima se oni nalaze u vektoru.*/
	uint_least8_t testVector[] = {UINT8_C(1), UINT8_C(2), UINT8_C(3)};
	SingleLinkedList_Initialize(&list, NULL);

	SingleLinkedList_Insert(&(list.head), &testVector[0]);
	ListElement_t* current = list.head;
	for(index = UINT8_C(1); index < UINT8_C(3); index++)
	{
		SingleLinkedList_Insert(&(current->next), &testVector[index]);
		current = current->next;
		assert(*((uint_least8_t*)current->data) == testVector[index]);
	}
	printSingleList(&list);

	SingleLinkedList_Destroy(&list);
	assert(list.head == NULL);
	printSingleList(&list);
}

static void testSingleDelete(void)
{
	printf("\t Test delete method\n");
	SingleLinkedList_t list;
	SingleLinkedList_Initialize(&list, NULL);

	uint_least8_t testVector[] = {UINT8_C(1), UINT8_C(2), UINT8_C(3)};
	uint_least8_t index;
	for(index = UINT8_C(0); index < UINT8_C(3); index++)
	{
		SingleLinkedList_Insert(&(list.head), &testVector[index]);
	}
	printSingleList(&list);

	/*Brisanje glave liste tokom svake iteracije.*/
	for(index = UINT8_C(0); index < UINT8_C(3); index++)
	{
		assert(*((uint_least8_t*)list.head->data) == testVector[UINT8_C(3)-index-UINT8_C(1)]);
		SingleLinkedList_Delete(&list, &(list.head));
	}
	assert(list.head == NULL);
	printSingleList(&list);

	/*Brisanje treceg i prvog elementa iz liste.*/
	for(index = UINT8_C(0); index < UINT8_C(3); index++)
	{
		SingleLinkedList_Insert(&(list.head), &testVector[index]);
	}
	printSingleList(&list);

	SingleLinkedList_Delete(&list, &(list.head->next->next));
	SingleLinkedList_Delete(&list, &(list.head));
	assert(*((uint_least8_t*)list.head->data) == testVector[1]);
	assert(list.head->next == NULL);
	printSingleList(&list);
}

static void destroyFunc1(void* object)
{
	return;
}

static void destroyFunc2(void* object)
{
	free(object);
}

static void printSingleList(SingleLinkedList_t* list)
{
	ListElement_t* current = list->head;
	printf("\t  ");
	if(current == NULL)
	{
		printf("Empty list");
	}
	else
	{
		while(current != NULL)
		{
			printf("%"PRIuLEAST16"->", *((uint_least8_t*)current->data));
			current = current->next;
		}
		printf("NULL");
	}
	printf("\n");
}

static void testDeltaList(void)
{
	printf("\n- Testing Delta List\n");

	testDeltaInitialize();
	testDeltaAddAndDestroy();
}

static void testDeltaInitialize(void)
{
	printf("\tTest initialize method\n");

	DeltaList_t deltaList;
	DeltaList_Initialize(&deltaList);
	assert(deltaList.rawList.head == NULL);
	assert(deltaList.rawList.destroy != NULL);

	printDeltaList(&deltaList);
}

static void testDeltaAddAndDestroy(void)
{
	printf("\tTest add and destroy methods\n");

	DeltaList_t deltaList;
	DeltaList_Initialize(&deltaList);
	/*Testni vektori za popunjavanje delta liste.*/
	DeltaElement_t* deltaTestVector[3] = {NULL, NULL, NULL};
	uint_least16_t delayVector[3] = {UINT16_C(100), UINT16_C(200), UINT16_C(300)};
	const char* idVector[3] = {"A", "B", "C"};
	uint_least8_t index = UINT8_C(0);
	for(; index < UINT8_C(3); index++)
	{
		deltaTestVector[index] = (DeltaElement_t*)malloc(sizeof(DeltaElement_t));
		deltaTestVector[index]->object = NULL;
		deltaTestVector[index]->delay = delayVector[index];
		strncpy(deltaTestVector[index]->id, idVector[index], (size_t)DELTA_MAX_ID_LENGTH);
		DeltaList_Add(&deltaList, deltaTestVector[index]);
	}
	assert(deltaList.rawList.head != NULL);
	printDeltaList(&deltaList);

	/*Brisanje delta liste.*/
	DeltaList_Destroy(&deltaList);
	assert(deltaList.rawList.head == NULL);
	printDeltaList(&deltaList);
}

static void printDeltaList(DeltaList_t* deltaList)
{
	printf("\t  ");
	if(deltaList->rawList.head != NULL)
	{
		ListElement_t* current = deltaList->rawList.head;
		while(current != NULL)
		{
			printf("[%s:%"PRIuLEAST16"]->",
							((DeltaElement_t*)current->data)->id,
							((DeltaElement_t*)current->data)->delay);
			current = current->next;
		}
		printf("NULL");
	}
	else
	{
		printf("Empty delta list");
	}
	printf("\n");
}


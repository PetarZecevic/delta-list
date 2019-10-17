/*
 * linked_list.h
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct ListElement
{
  void* data;
  struct ListElement* next;
}ListElement_t;

typedef struct SingleLinkedList
{
  /*
   * Funkcija koja ce biti pozvana pri brisanju podataka svakog elementa liste.
  */
  void (*destroy)(void* data);
  ListElement_t* head;
}SingleLinkedList_t;

/*
 * Inicijalizacija liste.
 * Mora biti pozvana pre prve upotrebe liste.
 * Drugi parametar je funkcija koja ce biti pozvana pri oslobadjanju
 * svakog elementa liste kako bi se oslobodili i njegovi podaci.
 * Ako je 'destroy' funkcija jednaka NULL nece se pozivati prilikom oslobadjanja
 * elemenata liste.
 * Pretpostavke:
 * - 'list' != NULL
*/
void SingleLinkedList_Initialize(SingleLinkedList_t* list, void (*destroy)(void* data));

/*
 * Ubacuje novi element nakon trenutnog elementa koji je prosledjen po referenci.
 * Pretpostavke:
 * - 'currentElement' != NULL
 * - '*currentElement' != NULL
 * - 'newElement' != NULL
 * - memorija za 'newElement' je zauzeta dinamicki.
*/
void SingleLinkedList_Insert(ListElement_t** currentElement, ListElement_t* newElement);

/*
 * Oslobadja memoriju zauzetu od strane svakog elementa prosledjene liste.
 * Pretpostavke:
 * - 'list' != NULL.
*/
void SingleLinkedList_Destroy(SingleLinkedList_t* list);

/*
 * Oslobadja memoriju zauzetu od strane elementa koji je nalazi u prosledjenoj listi
 * nakon prosledjenog elementa po referenci.
 * Pri oslobadjanju elementa se oslobadjaju i njegovi podaci uspomoc funkcije 'destroy'.
 * Pretpostavke:
 * - 'list' != NULL
 * - 'element != NULL'
 * - '*element' != NULL
*/
void SingleLinkedList_Delete(const SingleLinkedList_t* list, ListElement_t** element);

#endif /* LINKED_LIST_H_ */

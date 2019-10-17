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
   * Funkcija koja ce biti pozvana pri brisanju podatka svakog elementa liste.
  */
  void (*destroy)(void* data);
  ListElement_t* head;
}SingleLinkedList_t;

/*
 * Inicijalizacija liste.
 * Mora biti pozvana pre prve upotrebe liste.
*/
void SingleLinkedList_Initialize(SingleLinkedList_t* list, void (*destroy)(void* data));

/*
 * Ubacuje podatak u prosledjenu listu nakon prosledjenog elementa.
 * Ako je vrednost prosledjenog elementa NULL ubacuje element na pocetak liste.
 * Ukoliko je prosledjeni element razlicit od NULL, pretpostavka je da se nalazi
 * u prosledjenoj listi, tj. ne radi se provera da li se dati element nalazi u listi.
*/
void SingleLinkedList_Insert(SingleLinkedList_t* list, ListElement_t* element, void* data);

/*
 * Oslobadja memoriju zauzetu od svakog elementa prosledjene liste.
*/
void SingleLinkedList_Destroy(SingleLinkedList_t* list);

/*
 * Brise element nakon prosledjenog elementa iz prosledjene liste.
 * Ako je vrednost elementa NULL onda brise prvi element iz liste.
*/
void SingleLinkedList_Delete(SingleLinkedList_t* list, ListElement_t* element);

#endif /* LINKED_LIST_H_ */

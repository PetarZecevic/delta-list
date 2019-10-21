/*
 * delta_list.h
 *
 *  Created on: Oct 16, 2019
 *      Author: root
 */

#ifndef DELTA_LIST_H_
#define DELTA_LIST_H_

#include <stdint.h>
#include "linked_list.h"

#define DELTA_MAX_ID_LENGTH 9

typedef struct
{
  char id[DELTA_MAX_ID_LENGTH];
  void* object;
  uint_least16_t delay;
}DeltaElement_t;

typedef struct
{
  SingleLinkedList_t rawList;
}DeltaList_t;

/* Inicijalizuje delta listu tako sto inicijalizuje jednostruko spregnutu listu
 * sa parametrima specificnim za delta listu.
 * Pretpostavke:
 * - 'deltaList' != NULL
 */
void DeltaList_Initialize(DeltaList_t* deltaList);

/* Dodaje novi element u delta listu.
 * Mesto elementa u listi zavisi od njegovog perioda kasnjenja.
 * Element sa najmanjim periodom se nalazi na pocetku liste, a
 * element sa najvecim periodom na kraju liste.
 * Za detaljnije objasnjenje pogledati:
 *      https://everything2.com/title/delta+list
 * Pretpostavke:
 * - 'deltaList' != NULL
 * - 'newElement' != NULL
 * - memorija na koju ukazuje prosledjeni pokazivac delta elementa je dinamicki zauzeta.
 * - memorija na koju ukazuje DeltaElement_t.object polje strukture je dinamicki zauzeta ili je NULL.
 */
void DeltaList_Add(DeltaList_t* deltaList, DeltaElement_t* newDeltaElement);

/* Oslobadja memoriju zauzetu od strane svakog elementa liste.
 * Pretpostavke:
 * - 'deltaList' != NULL
 */
void DeltaList_Destroy(DeltaList_t* deltaList);

#endif /* DELTA_LIST_H_ */

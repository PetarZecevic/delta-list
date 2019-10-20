/*
 * Opis zadatka: 63. zadatak
 * Kratak opis resenja:
 * U sklopu resenja su napravljena 4 eclipse projekta.
 *      1) Projekat 'linked_list' sadrzi izvorni kod i binarni fajl dinamicke biblioteke
 *         koja sluzi za rukovanje jednostruko spregnutom listom.
 *      2) Projekat 'delta_list' sadrzi izvorni kod i binarni fajl dinamicke biblioteke
 *         koja sluzi za rukovanje delta listom. Ovaj projekat zavisi od dinamicke biblioteke
 *         projekta 1).
 *      3) Projekat 'test' koji sadrzi izvorni kod zaduzen za testiranje funkcionalnosti
 *         delta liste i jednostruko spregnute liste. Funkcije su implementirane po uzoru
 *         na model jedinicnog testiranja. Zavisi od dinamickih biblioteka projekata 1) i 2)
 *      4) Projekat 'main' sadrzi main.c datoteku koja sluzi za interakciju sa korisnikom.
 *         Zavisi od dinamickih biblioteka projekata 1) i 2)
 *		5) Projekat 'delta_proj' predstavlja korenski projekat koji objedinjuje izvorni kod svih prethodno
 *		   navedenih projekata u jednu celinu. Sadrzi fajl xml projectSet.psf koji opisuje strukturu projekata.
 *      Upustvo:
 *      - Projekti su povezani u jednu celinu uspomoc 'Team Project Set' funckionalnosti eclipse-a.
 *      Kako bi svi projekti bili ucitani u eclipse okruzenje potrebno je importovati fajl koji predstavlja
 *      opis strukture projekata na sledeci nacin:
 *              File -> Import -> Team -> Team Project Set -> URL -> http_link_projekta/projectSet.psf -> Finish
 *              http_link_projekta => https://svn.riouxsvn.com/delta_proj
 * Za proveru MISRA pravila je koriscen Texas Instruments kompajler sa vezbi, na nacin kako je to radjeno u
 * poslednjoj vezbi.
 * Ime: Petar
 * Prezime: Zecevic
 * Indeks: RA 43/2016
 * Napomene:
 *      MISRA 2004->2012 pravila:
 *      Pravilo 20.4 - Nije ispostovano jer su za implementaciju jednostruko spregnute liste i delta liste
 *      koriscene malloc i free funckije zbog fleksibilnosti, tj. broj elemenata nije ogranicen, ogranicen je
 *      kolicinom memorije koju sistem poseduje. Takodje su ove dve funkcije koriscene tokom testiranja.
 *      Pravilo 17.6 - Nije ispostovano u funkciji za ubacivanje novog elementa u jednostruko spregnutu listu,
 *      zato sto je bilo potrebno azurirati ono na sta prosledjeni pokazivaci,koji su parametri funkcije, ukazuju ali se
 *      adrese na kojima se oni nalaze u memoriji nisu koristile u svrhe dodele i povratnih vrednosti posto su to lokalne
 *      promenljive, tako da je pravilo tehnicki ispostovano.
 *      Pravilo 8.1 - Nije ispostovano kada su u pitanju 'main' funkcija.
 *      Pravilo 9.1 - Nije ispostovano kod projekata 'test' i 'main' jer se za inicijalizaciju lokalne promenljive
 *      liste koristila posebna funkcija.
 *      Pravilo 20.9 - Nije ispostovano u 'main' projektu jer se trazilo da korisnik unese elemente, pa je to realizovano
 *      pa se interakcija sa korisnikom oslanjala na standardni ulaz i izlaz.
 *      Nije ispostovano u projektu 'test' jer se standardni izlaz koristio za vizuelnu verifikaciju sadrzaja liste.
 *      Pravilo 10.1 - Nije ispostovano tamo gde se koristila 'assert' funkcija jer se radi o konverziji
 *      unutar 'assert' funkcije. Izuzetak ovog pravila je prosledjivanje 'NULL' pokazivaca ili dodela tamo gde se
 *      ocekuje pokazivac nekog tipa.
 **/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include "delta_list.h"

/* Prikazuje opcije programa na standardni izlaz.
 */
static void printOptions(void);

/* Ucitava ogranicen znakovni niz sa standardnog ulaza.
 */
static bool scanner(char* buffer, uint_least8_t bufferLength);

/* Prikazuje sadrzaj delta liste na standardni izlaz u formatu:
 * [id elementa, kasnjenje] -> (sledeci element)
 */
static void printDeltaList(DeltaList_t* deltaList);
void main(void)
{
	DeltaList_t deltaList;
	DeltaList_Initialize(&deltaList);
	static char optionBuffer[2];
	static char idBuffer[DELTA_MAX_ID_LENGTH];
	static char delayBuffer[6];
	bool programEnd = false;
	printf("\n--- Program za rukovanje delta listom --- \n");
	while(!programEnd)
	{
		printOptions();
		if(scanner(optionBuffer, UINT8_C(sizeof(optionBuffer))))
		{
			switch(optionBuffer[0])
			{
			case '1':
				printf("Identifikator elementa(1-%lu karaktera):", sizeof(idBuffer)-1);
				if(!scanner(idBuffer, UINT8_C(sizeof(idBuffer))))
				{
					printf("Greska: Nevalidan unos identifikatora\n");
					continue;
				}
				printf("Kasnjenje(0-%"PRIuLEAST16" milisekundi):", UINT_LEAST16_MAX);
				if(!scanner(delayBuffer, UINT8_C(sizeof(delayBuffer))))
				{
					printf("Greska: Nevalidan unos kasnjenja\n");
					continue;
				}
				/*Konverzija iz niza karaktera u neoznacen ceo broj.*/
				errno = 0;
				char* endptr = NULL;
				int_least32_t delayNum = INT32_C(strtol(delayBuffer, &endptr, 10));
				if(errno != 0 || (endptr != delayBuffer && *endptr == '\0'))
				{
					if(delayNum > UINT_LEAST16_MAX || delayNum < INT32_C(0))
					{
						printf("Greska: Broj van opsega\n");
						continue;
					}
					/*Kreiranje i dodavanje elementa u listu.*/
					DeltaElement_t* deltaElement = (DeltaElement_t*)malloc(sizeof(DeltaElement_t));
					strncpy(deltaElement->id, idBuffer, DELTA_MAX_ID_LENGTH);
					deltaElement->delay = UINT16_C(delayNum);
					deltaElement->object = NULL;
					DeltaList_Add(&deltaList, deltaElement);
					printf("Dodat element [%s,%s]\n", idBuffer, delayBuffer);
					printDeltaList(&deltaList);
				}
				else if(errno == ERANGE)
				{
					printf("Greska: Broj van opsega\n");
				}
				else
				{
					printf("Greska: Nevalidan broj\n");
				}
				break;
			case '2':
				DeltaList_Destroy(&deltaList);
				printf("Elementi liste su oslobodjeni\n");
				printDeltaList(&deltaList);
				break;
			case '3':
				printDeltaList(&deltaList);
				break;
			case '4':
				DeltaList_Destroy(&deltaList);
				return;
			default:
				printf("Greska: Nepostojeca opcija\n");
			}
		}
		else
		{
			printf("Greska: Neispravan unos\n");
		}
		printf("\n**********\n\n");
	}

}

static void printOptions(void)
{
	printf("Opcije:\n");
	printf("1) Dodavanje novog elementa\n");
	printf("2) Brisanje liste\n");
	printf("3) Prikaz liste\n");
	printf("4) Izlazak iz programa\n");
	printf("Unos:");
}

static bool scanner(char* buffer, uint_least8_t bufferLength)
{
	if(bufferLength == 0)
		return false;

	const uint_least8_t MAX_FORMAT_LENGTH = UINT8_C(32);
	char format[MAX_FORMAT_LENGTH];
	memset(format, '\0', (size_t)MAX_FORMAT_LENGTH);
	snprintf(format, MAX_FORMAT_LENGTH, "%%%"PRIuLEAST8"s", UINT8_C(bufferLength-1));
	int_least8_t result = INT8_C(scanf(format, buffer));

	/*Provera da li je ostalo jos znakova sa standardnog ulaza.*/
	bool restClear = true;
	char ch = (char)getchar();
	if(ch != '\n' && ch != EOF)
	{
		restClear = false;
		// .
		while((ch = (char)getchar()) != '\n' && ch != EOF)
		{
			;
		}
	}

	return (restClear && result > INT8_C(0)) ? true : false;
}

static void printDeltaList(DeltaList_t* deltaList)
{
	printf("Sadrzaj liste:\t");
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
		printf("Prazna lista");
	}
	printf("\n");
}

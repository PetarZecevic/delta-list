/*
 * Opis zadatka: 63. zadataka
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
 *      4) Projekat 'delta_proj' korenski projekat koji objedinjuje izvorni kod prethodnih projekata
 *         u jednu celinu. Sadrzi main.c datoteku koja sluzi za interakciju sa korisnikom.
 *         Zavisi od dinamickih biblioteka projekata 1) i 2)
 *
 *      Upustvo:
 *      Projekti su povezani u jednu celinu uspomoc 'Team Project Set' funckionalnosti eclipse-a.
 *      Kako bi svi projekti bili ucitani u eclipse okruzenje potrebno je importovati fajl koji predstavlja
 *      opis strukture projekata na sledeci nacin:
 *              File -> Import -> Team -> Team Project Set -> URL -> http_link_projekta/projectSet.psf -> Finish
 *              http_link_projekta => https://svn.riouxsvn.com/delta_proj
 * Ime: Petar
 * Prezime: Zecevic
 * Indeks: RA 43/2016
 * Napomene:
 *      MISRA 2004->2012 pravila:
 *      Pravilo 20.4 - Nije ispostovano jer su za implementaciju jednostruko spregnute liste i delta liste
 *      koriscene malloc i free funckije zbog fleksibilnosti, tj. broj elemenata nije ogranicen, ogranicen je
 *      kolicinom memorije koju sistem poseduje.
 *      Pravilo 17.6 - Nije ispostovano u funkciji za ubacivanje novog elementa u jednostruko spregnutu listu,
 *      zato sto je bilo potrebno azurirati ono na sta prosledjeni pokazivaci,koji su parametri funkcije, ukazuju ali se
 *      adrese na kojima se oni nalaze u memoriji nisu koristile u svrhe dodele i povratnih vrednosti posto su to lokalne
 *      promenljive, tako da je pravilo tehnicki ispostovano.
 *
 **/
#include <stdint.h>

int8_t main()
{
	return INT8_C(0);
}

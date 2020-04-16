/*
 riprendiamo l'esercizio esercizio-C2020-04-03
https://github.com/marcotessarotto/esercizio-C-2020-04-03

***
è dato il tipo dati contact_type, dovrebbe servire ad implementare una rubrica telefonica molto semplice:

#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

sono già date le seguenti funzioni (riutilizzare quelle già sviluppate):

// crea un oggetto di tipo contact_type e lo inizializza con name e phone
contact_type * create_contact(char * name, char * phone);

// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person);

******
*/
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>


#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256


typedef struct {
   int id;
   char name[NAME_LEN + 1];
   char phone[PHONE_LEN + 1];
} contact_type;

static int ident = 0;
contact_type * address_book[ADDRESS_BOOK_SIZE];

contact_type * create_contact(char * name, char * phone){

	contact_type * new_contact;
	new_contact = malloc(sizeof(contact_type));

		new_contact->id=ident;
		strcpy(new_contact->name, name);
		strcpy(new_contact->phone, phone);
		ident++;
		return new_contact;

}

void print_contact(contact_type * person){

	printf("PERSON:\t");
	printf("Id: %d, ", person->id);
	printf("Name: %s, ", person->name);
	printf("Phone: %s\n", person->phone);


}

/*scrivere le seguenti nuove funzioni e variabili:

#define ADDRESS_BOOK_SIZE 256

// la rubrica telefonica contiene al massimo 256 nominativi
contact_type * address_book[ADDRESS_BOOK_SIZE]; // global variable
// è un array di puntatori a contact_type
// se address_book[i] == NULL, vuole dire che la cella è utilizzabile per conservare l'indirizzo di un contatto
*/

// confronta due contatti:
// due contatti sono uguali se e solo se c1->name è uguale a c2->name e c1->phone è uguale a c2->phone
// return value:
// 0: contatti uguali
// < 0: se *c1 è ordinato prima di *c2
// > 0: se *c1 è ordinato dopo di *c2
// ovvero FATE COME FA STRCMP (vedete man strcmp)
// NOTA BENE: se c1 == NULL or c2 == NULL, restituisce -1
int compare_contacts(contact_type * c1, contact_type * c2){

	if(c2 == NULL){
		return -1;
	}

	if(c1 == NULL && c2 != NULL){
		return 1;
	}

	if ((strcmp(c1->name, c2->name)==0) && (strcmp(c1->phone,c2->phone)==0)){
		return 0;
	}

	if(strcmp(c1->name, c2->name)==0){
		return strcmp(c1->phone,c2->phone);
	}

	return strcmp(c1->name, c2->name);
}


// aggiunge il contatto c all'array address_book array
// la funzione NON controlla se il contatto è già presente; ma cerca la prima cella libero nell'array
// return value:
// >=0: posizione nell'array address_book dove è stato inserito c
// -1: errore (i.e. non c'è più spazio in address_book o c == NULL)
int add_to_address_book(contact_type * c){
	for(int i =0; i < ADDRESS_BOOK_SIZE; i++){
		if (address_book[i]==NULL){
			address_book[i] = c;
			return i;
		}
	}
	return -1;
}


// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
// return value:
// >= 0: posizione dove si trovava c
// -1: non ho trovato c, quindi non ho cancellato nessun contatto
int remove_from_address_book(contact_type * c){
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if (compare_contacts(c, address_book[i]) == 0){
			address_book[i] = NULL;
			return i;
		}
	}
	return -1;
}


// cerca il contatto c nell'array address_book
// cercare un contatto: confronta c con ogni contatto memorizzato in address_book
// DOVETE USARE compare_contacts()
// return value:
// >= 0: posizione dove si trova il primo contatto uguale a c
// -1: contatto c non trovato
int search_in_address_book(contact_type * c){
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if (compare_contacts(c, address_book[i])==0){
			return i;
		}
	}
	return -1;
}


// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()

void swap_contacts(contact_type * x, contact_type * y) {
		contact_type t;
		strcpy(t.name, x->name);
		strcpy(t.phone, x->phone);
		t.id = x->id;
		strcpy(x->name, y->name);
		strcpy(x->phone, y->phone);
		x->id = y->id;
		strcpy(y->name, t.name);
		strcpy(y->phone, t.phone);
		y->id = t.id;
	}

void sort_by_name(){

	int n, newn;

		n = ADDRESS_BOOK_SIZE;

		while (n > 1) {

			newn = 0;

			for (int i = 1; i < n; i++) {
				if (compare_contacts(address_book[i-1], address_book[i]) > 0){
					swap_contacts(address_book[i-1], address_book[i]);
					newn = i;
				}
			}

			n = newn;
		}
}

/*
scrivete un main() faccia le cose seguenti:

1 - creare gli oggetti di tipo contact_type a partire dai seguenti nominativi e numeri di telefono
ed inserirli in address_book utilizzando la funzione add_to_address_book

creare ed inserire in rubrica i contatti in questo ordine:

"dino","+391237"
"filippo", "+391239"
"barbara","+391235"
"antonio","+391234"
"enrico","+391238"
"chiara","+391236"

2 - cercare il contatto "antonio","+391234"
e se trovato, rimuoverlo

3 - creare ed aggiungere il contatto "pino","+399999"
e scrivere a video tutta la rubrica telefonica (non le celle vuote)

4 - aggiungere di nuovo dil contatto "antonio","+391234"

5 - fare il sort di tutta la rubrica

6 - scrivere a video tutta la rubrica telefonica (non le celle vuote)
il risultato deve essere ordinato

FINE
 */



int main(int argc, char *argv[]) {

	contact_type * dino = create_contact("dino", "+391237");

	if(add_to_address_book(dino) == -1){
		printf("errore add dino\n");
		exit(EXIT_FAILURE);
	}

	contact_type * filippo = create_contact("filippo", "+391239");

	if(add_to_address_book(filippo) == -1){
			printf("errore add filippo\n");
			exit(EXIT_FAILURE);
		}

	contact_type * barbara = create_contact("barbara", "+391235");

	if(add_to_address_book(barbara) == -1){
			printf("errore add barbara\n");
			exit(EXIT_FAILURE);
		}

	contact_type * antonio = create_contact("antonio", "+391234");

	if(add_to_address_book(antonio) == -1){
			printf("errore add antonio\n");
			exit(EXIT_FAILURE);
		}

	contact_type * enrico = create_contact("enrico", "+391238");

	if(add_to_address_book(enrico) == -1){
			printf("errore add enrico\n");
			exit(EXIT_FAILURE);
		}

	contact_type * chiara = create_contact("chiara", "+391236");

	if(add_to_address_book(chiara) == -1){
			printf("errore add chiara\n");
			exit(EXIT_FAILURE);
		}


	if(search_in_address_book(antonio) != -1){
		int i = remove_from_address_book(antonio);
		if (i == -1){
			printf("errore in remove antonio!\n");
			exit(EXIT_FAILURE);
		}
	}

	else{
		printf("errore in search antonio!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * pino = create_contact("pino", "+39999");

	if(add_to_address_book(pino) == -1){
			printf("errore add pino\n");
			exit(EXIT_FAILURE);
		}

	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if ( address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}

	if(add_to_address_book(antonio) == -1){
			printf("errore add antonio2\n");
			exit(EXIT_FAILURE);
		}

   sort_by_name();
   printf("\n\n");

	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++){
			if ( address_book[i] != NULL){
				print_contact(address_book[i]);
			}
		}

	free(dino);
	free(chiara);
	free(antonio);
	free(pino);
	free(enrico);
	free(barbara);
	free(filippo);

	return 0;

}

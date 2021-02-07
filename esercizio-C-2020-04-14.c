/***********TESTO ESERCIZIO*****************
 * riprendiamo l'esercizio esercizio-C2020-04-03
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

scrivere le seguenti nuove funzioni e variabili:

#define ADDRESS_BOOK_SIZE 256

// la rubrica telefonica contiene al massimo 256 nominativi
contact_type * address_book[ADDRESS_BOOK_SIZE]; // global variable
// è un array di puntatori a contact_type
// se address_book[i] == NULL, vuole dire che la cella è utilizzabile per conservare l'indirizzo di un contatto


// confronta due contatti:
// due contatti sono uguali se e solo se c1->name è uguale a c2->name e c1->phone è uguale a c2->phone
// return value:
// 0: contatti uguali
// < 0: se *c1 è ordinato prima di *c2
// > 0: se *c1 è ordinato dopo di *c2
// ovvero FATE COME FA STRCMP (vedete man strcmp)
// NOTA BENE: se c1 == NULL or c2 == NULL, restituisce -1
int compare_contacts(contact_type * c1, contact_type * c2);


// aggiunge il contatto c all'array address_book array
// la funzione NON controlla se il contatto è già presente; ma cerca la prima cella libero nell'array
// return value:
// >=0: posizione nell'array address_book dove è stato inserito c
// -1: errore (i.e. non c'è più spazio in address_book o c == NULL)
int add_to_address_book(contact_type * c);

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
// return value:
// >= 0: posizione dove si trovava c
// -1: non ho trovato c, quindi non ho cancellato nessun contatto
int remove_from_address_book(contact_type * c);


// cerca il contatto c nell'array address_book
// cercare un contatto: confronta c con ogni contatto memorizzato in address_book
// DOVETE USARE compare_contacts()
// return value:
// >= 0: posizione dove si trova il primo contatto uguale a c
// -1: contatto c non trovato
int search_in_address_book(contact_type * c);


// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()
void sort_by_name();


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
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;


int count = 0;	//id incrementale per i contatti
contact_type * address_book[ADDRESS_BOOK_SIZE];

// crea un oggetto di tipo contact_type e lo inizializza con name e phone
contact_type * create_contact(char * name, char * phone);

// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person);

// confronta due contatti:
int compare_contacts(contact_type * c1, contact_type * c2);

// aggiunge il contatto c all'array address_book array
int add_to_address_book(contact_type * c);

// cerca il contatto c nell'array address_book
int search_in_address_book(contact_type * c);

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
int remove_from_address_book(contact_type * c);

// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()
void sort_by_name();
void swap_contacts(contact_type *x, contact_type *y);

int main(int argc, char *argv[]) {

	//-----------------PUNTO 1-----------------
	contact_type * dino = create_contact("dino", "+391237");

	if (dino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * filippo = create_contact("filippo", "+391239");

	if (filippo == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * barbara = create_contact("barbara", "+391235");

	if (barbara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * antonio = create_contact("antonio", "+391234");

	if (antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * enrico = create_contact("enrico", "+391238");

	if (enrico == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	contact_type * chiara = create_contact("chiara", "+391236");

	if (chiara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int res;

	res = add_to_address_book(dino);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(filippo);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(barbara);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(antonio);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(enrico);
	if(res == -1)
		printf("Errore nell'inserimento del contatto nella rubrica!\n");

	res = add_to_address_book(chiara);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	//-----------------PUNTO 2-----------------
	contact_type * temp = create_contact("antonio", "+391234");

	if (antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	res = search_in_address_book(temp);

	if(res != -1){
		res = remove_from_address_book(temp);
		printf("Cancellazione riuscita!\n");
	}
	else{
		printf("Contatto non trovato nella rubrica!\n");
	}

	//-----------------PUNTO 3-----------------

	contact_type * pino = create_contact("pino", "+399999");

	if (pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(pino);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	printf("\n3) Rubrica: \n");

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL)
			print_contact(address_book[i]);
	}

	//-----------------PUNTO 4-----------------

	antonio = create_contact("antonio", "+391234");

	if (antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	res = add_to_address_book(antonio);
	if(res == -1){
		printf("Errore nell'inserimento del contatto nella rubrica!\n");
		exit(EXIT_FAILURE);
	}

	//-----------------PUNTO 5-----------------
	sort_by_name();

	//-----------------PUNTO 6-----------------
	printf("\n6) Rubrica ordinata: \n");
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL)
			print_contact(address_book[i]);
	}

	//-----------------------------------------
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++)
		if(address_book[i] != NULL){
			free(address_book[i]);
		}

	return 0;
}

contact_type * create_contact(char * name, char * phone){
	contact_type * new_contact = (contact_type *) malloc(sizeof(contact_type));

	new_contact->id = count;
	strcpy(new_contact->name, name);
	strcpy(new_contact->phone, phone);

	count++;

	return new_contact;
}

void print_contact(contact_type * person){
	printf("\nperson:");

	printf("\tid = %d, ", person->id);
	printf("name = %s, ", person->name);
	printf("phone = %s\n", person->phone);
}


int compare_contacts(contact_type * c1, contact_type * c2){
	if(c1 == NULL || c2 == NULL)
		return -1;

	int res = strcmp(c1->name, c2->name);

	if(res != 0){	//controllo se i nomi sono diversi
		if(res < 0)	//controllo se il nome di c1 è ordinato prima di quello di c2
			return -2;	//ritorno un valore negativo (che sia diverso da -1)
		else
			return 2;
	}

	res = strcmp(c1->phone, c2->phone);

	if(res != 0){	//controllo se i numeri di telefono sono diversi
		if(res < 0)
			return -2;
		else
			return 2;
	}

	//a questo punto i due contatti non possono che essere uguali
	return 0;
}

int add_to_address_book(contact_type * c){
	if(c == NULL)
		return -1;

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){	//scorro address_book
		if(address_book[i] == NULL){	//controllo se la posizione i-esima di address_book è libera
			address_book[i] = (contact_type *) malloc(sizeof(contact_type));

			if(address_book[i] == NULL)
				return -1;	//errore nel malloc

			address_book[i] = c;
			return i;	//ritorno la posizione in cui è stato inserito c in address_book
		}
	}

	return -1;	//se si arriva qui, allora address_book non ha più spazio libero
}

// cerca il contatto c nell'array address_book
int search_in_address_book(contact_type * c){
	if (c == NULL)
		return -1;

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(compare_contacts(c, address_book[i]) == 0)
			return i;
	}

	return -1;
}

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
int remove_from_address_book(contact_type * c){
	if(c == NULL)
		return -1;

	int pos = search_in_address_book(c);

	if(pos == -1)
		return -1;

	address_book[pos] = NULL;

	return pos;
}

void sort_by_name(){
	int n = ADDRESS_BOOK_SIZE;
	do{
		int newn = 0;
		for(int i = 1; i < n; i++){
			if(compare_contacts(address_book[i - 1], address_book[i]) > 0){
				swap_contacts(address_book[i-1], address_book[i]);
				newn = i;
			}
		}
		n = newn;
	}while(n > 1);
}

void swap_contacts(contact_type *x, contact_type *y) {
	contact_type t = *x;
	*x = *y;
	*y = t;
}

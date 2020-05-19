#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

int id_counter=0;

void print_contact(contact_type * person) {
	printf("person: id=%d, name='%s', phone='%s'\n", person->id, person->name, person->phone);
}

#define ADDRESS_BOOK_SIZE 256

contact_type * address_book[ADDRESS_BOOK_SIZE];

// crea un oggetto di tipo contact_type e lo inizializza con name e phone

contact_type * create_contact(char * name, char * phone) {
	contact_type * result;

	result = calloc(1, sizeof(contact_type));

	result->id = id_counter;
	id_counter++;

	if (name != NULL)
		strncpy(result->name, name, NAME_LEN);

	if (phone != NULL)
		strncpy(result->phone, phone, PHONE_LEN);

	return result;
}

// confronta due contatti:
// due contatti sono uguali se e solo se c1->name è uguale a c2->name
// e c1->phone è uguale a c2->phone
// return value:
// 0: contatti uguali
// < 0: se *c1 è ordinato prima di *c2
// > 0: se *c1 è ordinato dopo di *c2
// ovvero FATE COME FA STRCMP (vedete man strcmp)
// NOTA BENE: se c1 == NULL or c2 == NULL, restituisce -1
int compare_contacts(contact_type * c1, contact_type * c2){
	int ritorno = -1;

	if(c1->name == c2->name && c1->phone == c2->phone)
		ritorno = 0;
	else if(c1 != NULL && c2 != NULL)
		ritorno = strcmp(c1->name, c2->name);

	return ritorno;
}


// aggiunge il contatto c all'array address_book array
// la funzione NON controlla se il contatto è già presente;
// ma cerca la prima cella libera nell'array
// return value:
// >=0: posizione nell'array address_book dove è stato inserito c
// -1: errore (i.e. non c'è più spazio in address_book o c == NULL)

// se address_book[i] == NULL, vuole dire che la cella è utilizzabile
// per conservare l'indirizzo di un contatto
int add_to_address_book(contact_type * c){
	int posizione = -1;
	int i=0;

	while(address_book[i] != NULL){
		i++;
	}

	if(i < ADDRESS_BOOK_SIZE && c!= NULL){
		address_book[c->id] = c;
		posizione = c->id;
	}

	return posizione;
}

// cerca il contatto c nell'array address_book
// cercare un contatto: confronta c con ogni contatto memorizzato in address_book
// DOVETE USARE compare_contacts()
// return value:
// >= 0: posizione dove si trova il primo contatto uguale a c
// -1: contatto c non trovato
int search_in_address_book(contact_type * c){

	int res = -1;
	int i = 0;

	while(compare_contacts(c, address_book[i]) != 0){
		i++;

		if(i == ADDRESS_BOOK_SIZE)
			break;
	}

	if(i != ADDRESS_BOOK_SIZE)
		res = i;

	return res;
}

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
// return value:
// >= 0: posizione dove si trovava c
// -1: non ho trovato c, quindi non ho cancellato nessun contatto
int remove_from_address_book(contact_type * c){

	int posiz = -1;

	if((posiz = search_in_address_book(c)) != -1){
		address_book[posiz] = NULL;
	}

	return posiz;
}

// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()
void sort_by_name(){

	int compare;
	int contascambi=0;

	int i=0;

	while(i<id_counter-1){

		int b = i+1;

		compare = compare_contacts(address_book[i], address_book[b]);


		while(compare == -1 && b<=id_counter-1){//uno dei contatti è NULL

			if(address_book[i] == NULL)
				compare = 0;

			else if(address_book[b] == NULL){
				b++;
				compare = compare_contacts(address_book[i], address_book[b]);

			}
			else
				break;
		}


		if(compare > 0){

			contact_type *t = address_book[i+1];

			address_book[i+1] = address_book[i];
			address_book[i] = t;

			contascambi++;
		}

		//printf("%d\n", contascambi);

		if(i == id_counter-2 && contascambi>0){
			i=-1;
			contascambi=0;
		}
		i++;
	}
}


//scrivete un main() faccia le cose seguenti:
//

int main(){
//1 - creare gli oggetti di tipo contact_type a partire dai seguenti nominativi e numeri di telefono
//ed inserirli in address_book utilizzando la funzione add_to_address_book

	contact_type * anto;

	add_to_address_book(create_contact("dino", "+391237"));
	add_to_address_book(create_contact("filippo", "+391239"));
	add_to_address_book(create_contact("barbara","+391235"));
	add_to_address_book(anto = create_contact("antonio","+391234"));
	add_to_address_book(create_contact("enrico","+391238"));
	add_to_address_book(create_contact("chiara","+391236"));

	//2 - cercare il contatto "antonio","+391234"
	//e se trovato, rimuoverlo
	remove_from_address_book(anto); //il search è già compreso nella funzione

	add_to_address_book(create_contact("pino","+399999"));

	//3 - creare ed aggiungere il contatto "pino","+399999"
	//e scrivere a video tutta la rubrica telefonica (non le celle vuote)
	for(int i=0; i<id_counter; i++){
		if(address_book[i] != NULL)
			print_contact(address_book[i]);
	}

	//4 - aggiungere di nuovo dil contatto "antonio","+391234"
	add_to_address_book(create_contact("antonio","+391234"));

	//5 - fare il sort di tutta la rubrica
	sort_by_name();

	//6 - scrivere a video tutta la rubrica telefonica (non le celle vuote)
	//il risultato deve essere ordinato

	for(int i=0; i<id_counter; i++){
		if(address_book[i] != NULL)
			print_contact(address_book[i]);
	}

	return 0;

}











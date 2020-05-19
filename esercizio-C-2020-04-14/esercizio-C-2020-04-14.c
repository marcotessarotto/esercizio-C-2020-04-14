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

int pos=0;

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

// se address_book[i] == NULL, vuole dire che la cella è utilizzabile
// per conservare l'indirizzo di un contatto


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
	int ritorno;

	if(*c1->name == *c2->name && *c1->phone == *c2->phone)
		ritorno = 0;
	else if(c1 != NULL && c2 != NULL)
		ritorno = strcmp(c1->name, c2->name);

	return ritorno;
}


// aggiunge il contatto c all'array address_book array
// la funzione NON controlla se il contatto è già presente;
// ma cerca la prima cella libero nell'array
// return value:
// >=0: posizione nell'array address_book dove è stato inserito c
// -1: errore (i.e. non c'è più spazio in address_book o c == NULL)
int add_to_address_book(contact_type * c){
	int posizione = -1;

	if(pos < ADDRESS_BOOK_SIZE && c!= NULL && address_book[pos] != NULL){
		address_book[pos] = c;
		posizione = pos;
		pos++;
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

	int res;

	for(int i=0; i<pos; i++){

		if(compare_contacts(c, address_book[i]) == 0){
			res = i;
			i=pos;
		}
		else
			res=-1;
	}
	return res;
}

// rimuovi il contatto c da address_book (setta a NULL la posizione dove si trova c)
// return value:
// >= 0: posizione dove si trovava c
// -1: non ho trovato c, quindi non ho cancellato nessun contatto
int remove_from_address_book(contact_type * c){

	int posiz;

	if((posiz = search_in_address_book(c)) != -1){
		address_book[posiz] = NULL;
	}
	else{
		posiz = -1;
	}
	return posiz;
}
//prende l'indirizzo della prima variabile e scambia le posizioni delle variabili
void swap_address(contact_type * c1, contact_type * c2){

	contact_type t;

	//t = calloc(1, sizeof(contact_type));

	t = *c1;
	*c1 = *c2;
	*c2 = t;

}

// funzione che fa il sort dei contatti in address_book, utilizzando compare_contacts()
void sort_by_name(){

	int compare;
	int contascambi=0;

	for(int i=0; i<pos-1; i++){

		compare = compare_contacts(address_book[i], address_book[i+1]);

		if(compare > 0){
			swap_address(address_book[i], address_book[i+1]);
			contascambi++;
		}
		if(i == pos-2)
			if(contascambi>0)
				i=0;
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
	if(search_in_address_book(anto) != -1)
		remove_from_address_book(anto);

	add_to_address_book(create_contact("pino","+399999"));

	//3 - creare ed aggiungere il contatto "pino","+399999"
	//e scrivere a video tutta la rubrica telefonica (non le celle vuote)
	for(int i=0; i<pos; i++){
		if(address_book[i] != NULL)
			print_contact(address_book[i]);
	}

	//4 - aggiungere di nuovo dil contatto "antonio","+391234"
	add_to_address_book(create_contact("antonio","+391234"));

	//5 - fare il sort di tutta la rubrica
	sort_by_name();

	//6 - scrivere a video tutta la rubrica telefonica (non le celle vuote)
	//il risultato deve essere ordinato

	for(int i=0; i<pos; i++){
			if(address_book[i] != NULL)
				print_contact(address_book[i]);
	}

	return 0;

}











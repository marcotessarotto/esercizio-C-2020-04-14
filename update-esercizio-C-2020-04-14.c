
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256



int univoco = 0;

typedef
	struct {
		int id; // id numerico del contatto (valore univoco)
		char name[NAME_LEN + 1]; // nome della persona
		char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

contact_type  *create_contact(char * name, char * phone){
	contact_type  *contact;
	contact = malloc(sizeof(contact_type));

	contact->id = univoco ;


	memcpy(contact->name, name, 64 * sizeof(char));

	memcpy(contact->phone, phone, 20 * sizeof(char));

	univoco++;

	return contact;
}

void print_contact(contact_type *person){
	printf("person:		 id=%d  name='%s' phone='%s'\n", (*person).id, (*person).name, (*person).phone);
	printf("____________________\n\n");
}

//per alleggerire la lettura uso questa funzione per assicurarmi che la creazione del contatto avvenga in maniera corretta
void verifica(contact_type *contact){
if (contact->name == NULL || contact->phone == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
}

int cmp_contact(contact_type *c1, contact_type *c2){
	
	int result = 0;
	result = strcmp(c1->name, c2->name);
	if(result != 0){
		return result;
	}else{
		result = strcmp(c1->phone, c2->phone);
	}

	return result;

}

contact_type * address_book[ADDRESS_BOOK_SIZE];

//creo un acopia della rubrica vuota che mi servirà per ordinare quella principale
contact_type * address_book_order[ADDRESS_BOOK_SIZE];

int add_contact(contact_type *contact){
	int i=0;
	//printf("______add_contact_______\n");
	if (contact == NULL){
		printf("Il contatto non è stato inserito, contatto non valido!");
		return-1;
	}
	while(i<ADDRESS_BOOK_SIZE){
		if(address_book[i]==NULL){
			address_book[i] = contact;
		//	printf("contatto inserito nella posizione: %d\n", i);
		//	printf("____________________\n");
			return i;
		}
		i++;
	}
	if (i >= ADDRESS_BOOK_SIZE){
		printf("Il contatto non è stato inserito, la rubrica è piena!");
		printf("____________________\n");
		return-1;
	}

	return 0;
}

int add_contact_order(contact_type *contact){
	int i=0;
	if (contact == NULL){
		printf("null");
		return-1;
	}
	while(i<ADDRESS_BOOK_SIZE){
		if(address_book_order[i]==NULL){
			address_book_order[i] = contact;
			return i;
		}
		i++;
	}
	if (i >= ADDRESS_BOOK_SIZE){
		printf("pieno");
		return-1;
	}
	return 0;
}

int remove_contact(contact_type *contact){

	int i=0;
	if (contact == NULL){
			printf("Il contatto non è stato rimosso, contatto non valido!\n");
			printf("____________________\n");
			return-1;
		}
		while(i<ADDRESS_BOOK_SIZE){
			if(address_book[i]==contact){
				address_book[i] = NULL;
			//	printf("Contatto rimosso! Si trovava alla posizione: %d\n", i);
			//	printf("____________________\n\n");
				return i;
			}
			i++;
		}
		if (i >= ADDRESS_BOOK_SIZE){
			printf("Non è stato trovato il contatto richiesto!\n");
			printf("____________________\n");
			return-1;
		}

		return 0;
}

int search_contact(contact_type *contact){
	int i = 0;
	while(i<ADDRESS_BOOK_SIZE){
		int compare = cmp_contact(contact, address_book[i]);
		if(compare == 0){
			printf("Trovato!\n Il primo contatto uguale si trova alla posizione %d\n", i);
		}
		i++;
	}
	if (i >= ADDRESS_BOOK_SIZE){
				printf("Non è stato trovato il contatto richiesto!");
				return-1;
			}
	return 0;
}

void print_address_book(){

	int i =0;
	printf("____print_address_book____\n");
	while(i<ADDRESS_BOOK_SIZE){
		if (address_book[i] != NULL){
			print_contact(address_book[i]);

		}
		i++;
	}
	printf("__________________________\n");
}

void sort_by_name(){

	//selective sort che prende il primo conatatto in ordine alfabetico, lo trascrive nella rubrica ordinata
	//lo cancella da quella reale e successivamente ricopio la rubrica ordinata in quella reale

	int j = 0;
    int pos = 0;


	while (j<ADDRESS_BOOK_SIZE){


	for (int i = 0; i<10; i++){

		if (address_book[i] != NULL){			
			int res = cmp_contact(address_book[pos], address_book[i]);
			if(res > 0){
			pos = i;	
			}
		}
	}

	if (address_book[pos] != NULL){
	add_contact_order(address_book[pos]);
	remove_contact(address_book[pos]);
	}

	for(int y = 0; y<ADDRESS_BOOK_SIZE; y++){
		if (address_book[y] != NULL){
			pos = y;
		}
	}

	j++;
	}

	//ora ho l'array ordinato e lo ricopio sulla rubrica
	for (int x=0; x<ADDRESS_BOOK_SIZE; x++){
		if(address_book_order[x] != NULL){
			add_contact(address_book_order[x]);
		}
	}

}


int main(int argc, char *argv[]) {

	contact_type *dino = create_contact("dino", "+391239");
	verifica(dino);
	//print_contact(dino);
	add_contact(dino);

	contact_type *filippino = create_contact("filippino", "+391239");
	verifica(filippino);
	//print_contact(filippino);
	add_contact(filippino);

	contact_type *barbara = create_contact("barbara", "+391235");
	verifica(barbara);
	//print_contact(barbara);
	add_contact(barbara);

	contact_type *antonio = create_contact("antonio", "+391234");
	verifica(antonio);
	//print_contact(antonio);
	add_contact(antonio);

	contact_type *enrico = create_contact("enrico", "+391238");
	verifica(enrico);
	//print_contact(enrico);
	add_contact(enrico);

	contact_type *chiara = create_contact("chiara", "+391236");
	verifica(chiara);
	//print_contact(chiara);
	add_contact(chiara);

	//rimoviamo il contatto antonio
	remove_contact(antonio);

	//print_address_book(); // verifica per controllare rimozione di antonio

	//creaiamo e aggiungiamo il contatto pino
	contact_type *pino = create_contact("pino", "+399999");
	verifica(pino);
	//print_contact(pino);
	add_contact(pino);

	//stampo la rubrica aggiornata
	print_address_book();

	//aggiungo di nuovo antonio
	add_contact(antonio);

	//stampo la rubrica aggironata
	print_address_book();

	//ordino per nome
	sort_by_name();

	//stampo la rubrica ordinata
	print_address_book();

	return 0;
}

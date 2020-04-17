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

int max_id = 0;
int address_book_size = 0;

contact_type * address_book[ADDRESS_BOOK_SIZE];


contact_type * create_contact(char * name, char * phone);
void print_contact(contact_type * person);

int compare_contacts(contact_type * c1, contact_type * c2);
int add_to_address_book(contact_type * c);
int remove_from_address_book(contact_type * c);
int search_in_address_book(contact_type *c);
void swap_contacts(contact_type *c1, contact_type *c2);
void sort_by_name();


int main(int argc, char *argv[]) {

//-------punto 1---------

	int n_contatti = 6;
	char * nomi[] = {"dino", "filippo", "barbara", "antonio", "enrico", "chiara"};
	char * numeri[] = {"+391237", "+391239", "+391235", "+391234", "+391238", "+391236",};

	for(int i=0; i < n_contatti; i++){
		contact_type * contact = create_contact(nomi[i], numeri[i]);
		int add = add_to_address_book(contact);
		if(add < 0){
			printf("Errore in add_to_address_contact");
			exit(EXIT_FAILURE);
		}
		else{
			printf("Aggiunto in posizione %d: ", add);
			print_contact(contact);
		}
	}

//-----------------------
//-------punto 2---------
	int cerca_antonio;
	contact_type * antonio = create_contact("antonio", "+391234");
	cerca_antonio = search_in_address_book(antonio);

	if(cerca_antonio < 0){
		printf("Antonio non trovato!\n");
	}
	else{
		int rim_antonio = remove_from_address_book(antonio);
		if(rim_antonio < 0){
			printf("Errore: impossibile rimuovere antonio");
		}
		else{
			printf("\nRimosso dalla posizione %d.", rim_antonio);
			print_contact(antonio);
		}
	}

//-----------------------
//-------punto 3---------
	contact_type * pino = create_contact("pino", "+399999");
	add_to_address_book(pino);

	printf("\nINTERA RUBRICA:\n");
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
//-----------------------
//-------punto 4---------
	int add = add_to_address_book(antonio);
	if(add < 0){
		printf("errore");
	}
	else{
		printf("\n\nAggiunto in posizione %d: ", add);
		print_contact(antonio);
		printf("\n\n");
	}
//-----------------------
//-------punto 5---------
	sort_by_name();
//-----------------------
//-------punto 6---------
	printf("\nINTERA RUBRICA:\n");
	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
//-----------------------

	return 0;
}

contact_type * create_contact(char * name, char * phone){
	if(name == NULL){
		return NULL;
	}
	contact_type * contact;
	contact = calloc(1, sizeof(contact_type));
	contact->id = max_id;
	strncpy(contact->name, name, NAME_LEN);
	strncpy(contact->phone, phone, PHONE_LEN);
	max_id++;
	return contact;
}

void print_contact(contact_type * person){
	printf("person: id=%d, name='%s', phone='%s'\n", person->id, person->name, person->phone);
	return;
}

int compare_contacts(contact_type * c1, contact_type * c2){
	if(c1 == NULL || c2 == NULL){
		return -1;
	}

	int cmp_name = strcmp(c1->name,c2->name);

	if(cmp_name == 0){
		int cmp_phone = strcmp(c1->phone,c2->phone);
		return cmp_phone;
	}
	else{
		return cmp_name;
	}
}

int add_to_address_book(contact_type * c){
	if(c == NULL){
		return -1;
	}

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(address_book[i] == NULL){
			address_book[i] = c;
			address_book_size++;
			return i;
		}
	}

	return -1;
}

int remove_from_address_book(contact_type * c){

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(compare_contacts(c, address_book[i]) == 0){
			for(int n = i+1; n < address_book_size; n++){
				swap_contacts(address_book[n], address_book[n-1]);
			}
			//free(address_book[i]);
			address_book_size--;
			address_book[address_book_size] = NULL;
			return i;
		}
	}

	return -1;
}

int search_in_address_book(contact_type *c){

	for(int i = 0; i < ADDRESS_BOOK_SIZE; i++){
		if(compare_contacts(c, address_book[i]) == 0){
			return i;
		}
	}

	return -1;
}

void swap_contacts(contact_type * c1, contact_type * c2){

	contact_type temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void sort_by_name(){
	int n = address_book_size;
	do{
		int newn = 0;
		for(int i = 1; i < n; i++){
		if(compare_contacts(address_book[i], address_book[i-1]) < 0){
				swap_contacts(address_book[i-1], address_book[i]);
				newn = i;
			}
		}
		n = newn;
	}while(n>=1);

	return;
}

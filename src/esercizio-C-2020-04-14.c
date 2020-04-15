#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256


typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;


//global variable
int id_counter; // già inizializzato a 0
contact_type * address_book[ADDRESS_BOOK_SIZE];


// signature function
contact_type * create_contact(char * name, char * phone);
void print_contact(contact_type * person);
int compare_contacts(contact_type * c1, contact_type * c2);
int add_to_address_book(contact_type * c);
int remove_from_address_book(contact_type * c);
int search_in_address_book(contact_type * c);
void swap_contacts(contact_type *x, contact_type *y);
void sort_by_name();


int main(int argc, char *argv[]) {

	// main requst (1)
	char *contacts[] = {	"dino",		"+391239",
							"filippo",	"+391239",
							"barbara",	"+391239",
							"antonio",	"+391234",
							"enrico",	"+391238",
							"chiara",	"+391236"
						};
	int numbers_of_contacts = 6;

	contact_type * contact;

	for(int i=0 ; i<numbers_of_contacts*2 ; i+=2){
		contact = create_contact(contacts[i], contacts[i+1]);
		if (contact == NULL) {
			printf("errore in create_contact!\n");
			exit(EXIT_FAILURE);
		}
		add_to_address_book(contact);
	}

	// main requst (2)
	contact_type * antonio = create_contact("antonio", "+391234");
	int index_of_antonio_in_address_book = search_in_address_book(antonio);
	if(index_of_antonio_in_address_book >= 0){
		int check = remove_from_address_book(address_book[index_of_antonio_in_address_book]);
		if(check < 0){
			printf("error in remove_from_address_book\n");
		}
	}

	// main requst (3)
	contact_type * pino = create_contact("pino", "+399999");
	if (pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(pino);

	for(int i=0 ; i<ADDRESS_BOOK_SIZE ; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}
	putchar('\n');

	// main requst (4)
	antonio = create_contact("antonio", "+391234");
	if (antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	add_to_address_book(antonio);

	// main requst (5)
	sort_by_name();

	// main requst (6)
	for(int i=0 ; i<ADDRESS_BOOK_SIZE ; i++){
		if(address_book[i] != NULL){
			print_contact(address_book[i]);
		}
	}

	return 0;
}


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


// scrive su stdout i contenuti dell'oggetto
void print_contact(contact_type * person) {
	printf("person: id=%d\tname='%s'\t phone='%s'\n", person->id, person->name, person->phone);
}


// aggiunge un contatto all address_book
int add_to_address_book(contact_type * c){
	int result = -1;
	if(c == NULL){
		return result;
	}

	for(int i=0 ; i<ADDRESS_BOOK_SIZE ; i++){
		if(address_book[i] == NULL){
			address_book[i] = c;
			result = i;
			break;
		}
	}

	return result;
}


// confronta due contatti se sono uguali torna 0
int compare_contacts(contact_type * c1, contact_type * c2){

	if(c1 == NULL || c2 == NULL){
		return -1;
	}

	int compare_name = strcmp(c1->name, c2->name);
	int compare_phone = strcmp(c1->phone, c2->phone);

	// return the strcmp
	if(compare_name == 0 && compare_phone == 0){
		return 0;
	}else{
		if(compare_name != 0){
			return compare_name;
		}else{
			return compare_phone;
		}
	}

}


// rimuove un contatto dall'address_book
int remove_from_address_book(contact_type * c){
	int result = -1;

	for(int i=0 ; i<ADDRESS_BOOK_SIZE ; i++){
		if(address_book[i] == c){
			address_book[i] = NULL;
			result = i;
			break;
		}
	}

	return result;
}


// trova l'indice di un contatto nell address_book
int search_in_address_book(contact_type * c){
	int result = -1;

	for(int i=0 ; i<ADDRESS_BOOK_SIZE ; i++){
		if(compare_contacts(c, address_book[i]) == 0){
			result = i;
			break;
		}
	}

	return result;
}


// swap due contatti
void swap_contacts(contact_type *x, contact_type *y){
	contact_type t = *x;
	*x = *y;
	*y = t;
}


// bubble sorto applicato ad una array di contatti
void bubble_sort(contact_type ** array, int array_dimension) {
	// example: array = [c1, c2 , NULL, c3, c4, NULL, NULL]
	int upperLimit = array_dimension; // in the example upperLimit = 7
	//optimization, exclude from the bubble sorts all the final part of NULL cells from address_book
	for(int i=array_dimension-1 ; i>=0 ; i--){
		if(array[i] != NULL){
			upperLimit = i+1;
			break;
		}
	}
	// in the example upperLimit = 5

	// swap all the null contact and put on the bottom of the address_book
	for(int i=0 ; i<upperLimit ; i++){
		if(array[i] == NULL){
			array[i] = array[upperLimit-1];
			array[upperLimit-1] = NULL;
			upperLimit--;
		}
	}
	// in the example upperLimit = 4 and array = [c1, c2, c4, c3, NULL, NULL, NULL]

	//start bubble sort
	while(upperLimit > 1){
		for(int i=1 ; i<upperLimit ; i++){
		   if(compare_contacts( array[i-1], array[i]) > 0){
			   swap_contacts(array[i-1], array[i]);
		   }
		}
		upperLimit--;
	}
}


//ordina i contatti per nome
void sort_by_name(){
	bubble_sort(address_book, ADDRESS_BOOK_SIZE);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256
#define TRUE 1
#define FALSE 0

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;





//VARIABILI GLOBALI
int id=0;
contact_type * address_book[ADDRESS_BOOK_SIZE];






contact_type * create_contact(char * name, char * phone){

	contact_type * person=malloc(sizeof(contact_type));

	(*person).id=id;

	strcpy((*person).name,name);
	strcpy((*person).phone,phone);

	++id;

	return person;

}

void print_contact (contact_type * person){

	printf("person: id=%d, name='%s', phone='%s\n\n",(*person).id,(*person).name,(*person).phone);

}


int compare_contacts(contact_type * c1, contact_type * c2){
	int i=0;

	char *p1=&(*c1).name;
	char *p2=&(*c2).name;

	if(c1==NULL || c2==NULL)
		return -1;

	else //confronto i nomi
		while (*p1!='\0' && *p2!='\0'){

			if (*p1==*p2)
				;
			else
				return *p1-*p2;

			++p1;
			++p2;
		}
	//se i nomi sono uguali confronto i numeri di telefono
	if(*p1=='\0' && *p2=='\0'){

		p1=&(*c1).phone;
		p2=&(*c2).phone;

		while (*p1!='\0' && *p2!='\0'){

			if (*p1==*p2)
				;
			else
				return *p1-*p2;

			++p1;
			++p2;
		}
	}

	return *p1-*p2;
}



int add_to_address_book(contact_type * c){

	if(c==NULL)
		return -2;
	else{ //inserisco nel primo posto libero

		int i=0;
		int inserito=FALSE;

		while(i<ADDRESS_BOOK_SIZE && inserito==FALSE)

			if(address_book[i]==NULL){
				address_book[i]=c;
				inserito=TRUE;
			}else
				++i;

		if(inserito)
			return i;
		else
			return -1;
	}
}

int remove_from_address_book(contact_type * c){

	if(c==NULL)
		return -2;

	else{
		//se non si volesse restituire la posizione in cui ho rimosso il contatto
		//si potrebbe sfruttare un for per rimuovere tutti i contatti uguali

		int i=0;
		int rimosso=FALSE;

		while(i<ADDRESS_BOOK_SIZE && rimosso==FALSE)

			if(compare_contacts(address_book[i],c)==0){
				address_book[i]=NULL;
				rimosso=TRUE;
			}else
				++i;

		if(rimosso)
			return i;
		else
			return -1;
	}
}

int search_in_address_book(contact_type * c){

	if(c==NULL)
		return -2;

	else{
		int i=0;
		int trovato=FALSE;

		while(!trovato && i<ADDRESS_BOOK_SIZE){

			if(compare_contacts(address_book[i],c)==0)
				trovato=TRUE;
			++i;
		}

		if (trovato)
			return i;
		else
			return -1;

	}
}


void swap(contact_type *a, contact_type *b) {
	contact_type t = *a;
	*a = *b;
	*b = t;
}


void sort_by_name(){
	int n=ADDRESS_BOOK_SIZE,newn;
	while (n > 1) {

		newn = 0;

		for (int i = 1; i < n; i++) {

			if (compare_contacts(address_book[i-1],address_book[i])>0) {
				swap(address_book[i-1],address_book[i]);

				newn = i;
			}
		}

		n = newn;
	}//end while
}


void print_address_book(){

	for(int i=0;i<ADDRESS_BOOK_SIZE;++i)
		if(address_book[i]!=NULL)
			print_contact(address_book[i]);
	printf("\n\n");


}


int main(int argc, char *argv[]) {

	//creo e inserisco i contatti

	contact_type * c = create_contact("dino", "+391237");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	c = create_contact("filippo","+391239");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	c = create_contact("barbara","+391235");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	c = create_contact("antonio","+391234");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	c = create_contact("enrico","+391238");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	c = create_contact("chiara","+391236");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));



	//	2 - cercare il contatto "antonio","+391234"
	//	e se trovato, rimuoverlo

	c = create_contact("antonio","+391234");

	if(search_in_address_book(c)>=0)
		printf("Rimuovo antonio dalla posizione %d\n\n",remove_from_address_book(c));



	//	3 - creare ed aggiungere il contatto "pino","+399999"
	//	e scrivere a video tutta la rubrica telefonica (non le celle vuote)

	c = create_contact("pino","+399999");
	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));

	printf("\n\n Stampo tutta la rubruca:\n\n");
	print_address_book();

	//	4 - aggiungere di nuovo il contatto "antonio","+391234"

	c = create_contact("antonio","+391234");

	if (c == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	printf("Inserisco contatto \"%s\" nella posizione %d\n\n",(*c).name,add_to_address_book(c));


	//	5 - fare il sort di tutta la rubrica

	sort_by_name();


	//	6 - scrivere a video tutta la rubrica telefonica (non le celle vuote)
	//	il risultato deve essere ordinato

	printf("\n\n Stampo tutta la rubruca:\n\n");
	print_address_book();


	return 0;
}


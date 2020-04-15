#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 64
#define PHONE_LEN 20
#define ADDRESS_BOOK_SIZE 256

int c=0;

typedef struct {
   int id; // id numerico del contatto (valore univoco)
   char name[NAME_LEN + 1]; // nome della persona
   char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;

contact_type * address_book[ADDRESS_BOOK_SIZE];

void print_contact(contact_type * person)
{

	printf("person: id=%d, name='%s', phone='%s'\n", (*person).id, (*person).name, (*person).phone);

}

contact_type * create_contact(char * name, char * phone)
{
	contact_type * person = malloc(sizeof(contact_type));
	(*person).id = c;
	memcpy((*person).name, name , NAME_LEN+1);
	memcpy((*person).phone, phone, PHONE_LEN+1);
	c++;

	return person;
}

int compare_contacts(contact_type * c1, contact_type * c2)
{
	if(c1->name == c2->name && c1->phone == c2->phone && c1!=NULL && c2!=NULL )
	{
		return 0;
	}
	else
	{
		if(strcmp(c1->name, c2->name)<0 && c1!=NULL && c2!=NULL)

			return 1;
		else
		{
			if(c1==NULL || c2==NULL)
				return -1;
			return -2;
		}
	}

}

int add_to_address_book(contact_type * c)
{
	int i=0;
	if(c==NULL)
		return -1;

	while(address_book[i]!=NULL)
	{
		i++;
		if(i==256)
			return -1;
	}

	address_book[i]=c;
	return i;

}

int remove_from_address_book(contact_type * c)
{
	int i=0;
	while(i<256)
	{
		if(address_book[i]==c)
		{
			address_book[i]=NULL;
			return i;
		}
		i++;
	}

	return -1;
}

int search_in_address_book(contact_type * c)
{
	int i=0;
	while(i<ADDRESS_BOOK_SIZE)
	{
		if(compare_contacts(address_book[i], c)==0)
		return i;

		i++;
	}

	return -1;

}

void swap_contacts(int x, int y)
{
	contact_type *t = address_book[x];
	address_book[x] = address_book[y];
	address_book[y] = t;

}

void sort_by_name()
{
	  for (int i=0; i<ADDRESS_BOOK_SIZE-1; i++)
	  {
		  for (int j=0; j<ADDRESS_BOOK_SIZE-i-1; j++)
		  {
			  if (address_book[j] == NULL && address_book[j+1] != NULL)
				  swap_contacts(j,j+1);
			  else if (address_book[j] != NULL && address_book[j + 1] != NULL)
				  if (compare_contacts(address_book[j],address_book[j + 1])==-2)
					  swap_contacts(j,j+1);
	      }

	  }
}

int main(int argc, char *argv[]) {

	contact_type * dino = create_contact("dino", "+391237");
	if (dino == NULL) {
			printf("errore in create_contact!\n");
			exit(EXIT_FAILURE);
		}

	int a=add_to_address_book(dino);
	if(a>=0)
	{
		printf("Contatto Dino inserito nella posizione %d\n", a );

	}
	else
		printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");



	contact_type * filippo = create_contact("filippo", "+391239");

	if (filippo == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int b=add_to_address_book(filippo);
		if(b>=0)
		{
			printf("Contatto Filippo inserito nella posizione %d\n", b );
		}
		else
			printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");



	contact_type * barbara = create_contact("barbara", "+391235");

	if (barbara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int c=add_to_address_book(barbara);
			if(c>=0)
			{
				printf("Contatto Barbara inserito nella posizione %d\n", c );
			}
			else
				printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");



	contact_type * antonio = create_contact("antonio", "+391234");

	if (antonio == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int d=add_to_address_book(antonio);
	if(d>=0)
	{
		printf("Contatto Antonio inserito nella posizione %d\n", d );
	}
	else
		printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");



	contact_type * enrico = create_contact("enrico", "+391238");

	if (enrico == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int e=add_to_address_book(enrico);
	if(e>=0)
	{
		printf("Contatto Enrico inserito nella posizione %d\n", e );
	}
	else
	printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");


	contact_type * chiara = create_contact("chiara", "+391236");

	if (chiara == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}

	int f=add_to_address_book(chiara);
	if(f>=0)
	{
		printf("Contatto Chiara inserito nella posizione %d\n", f );
	}
	else
		printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");


	if(search_in_address_book(antonio)>=0)
	{
		remove_from_address_book(antonio);
		printf("\n\nContatto Antonio trovato e rimosso\n");

	}
	else
		printf("Contatto non trovato");


	contact_type * pino = create_contact("pino", "+399999");
	if (pino == NULL) {
		printf("errore in create_contact!\n");
		exit(EXIT_FAILURE);
	}
	int g=add_to_address_book(pino);
		if(g>=0)
		{
			printf("Contatto Pino inserito nella posizione %d\n", g);
		}
		else
			printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");



		printf("\n\nStampa rubrica\n");

	for(int i=0; i<ADDRESS_BOOK_SIZE; i++)
	{
		if(address_book[i]!=NULL)
			print_contact(address_book[i]);
	}

	int h=add_to_address_book(antonio);
	if(h>=0)
	{
		printf("\n\nContatto Antonio inserito nella posizione %d\n", h);

	}
	else
		printf("errore (i.e. non c'è più spazio in address_book o c == NULL)");

	sort_by_name();

	printf("\n\nStampa rubrica dopo reinserimento di Antonio e sorting\n");
	for(int i=0; i<ADDRESS_BOOK_SIZE; i++)
		{
			if(address_book[i]!=NULL)
				print_contact(address_book[i]);
		}

	free(dino);
	free(filippo);
	free(barbara);
	free(pino);
	free(antonio);
	free(enrico);
	free(chiara);

	return 0;
}



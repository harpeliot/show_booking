void displaySpectacle(Spectacle tab[], int t_len)
{
	printf("ID | TITLE					|PLACES|NUMBER|\n---+-------------------------------------------+------+------+\n");
	for(int i=0; i< t_len; i++)
	{
		printf("%d	%s					%d	%d \n", tab[i].id, tab[i].title, tab[i].left_places, tab[i].representation);
	}
	printf("\n The booking of the left places is not guaranted.\n");
}


int starting()
{
	int connection;

	printf("Welcome on the tickets shop !\n Do you want to connect ? \n 1: Yes \n 2: No \n");


	scanf("%d", &connection);
	switch(connection){
		case 1 :
			printf("You are connected\n");
			sleep(1);
			return 1;
		case 2 :
			printf("See you soon !\n");
			sleep(2);
			return -1;
	}
	return 0;
	
}

int reservationId()
{
	int choice;
	printf("\n Give the id of the show : \n");
	scanf(" %d", &choice);
	return choice;
}

int reservationProcess()
{
	int choice;

	printf("\n Do you want to book a show? \n 1: Yes \n 2: No \n");
	scanf("%d", &choice);
	switch(choice){
		case 1 :
			printf("You can decide which one\n");
			sleep(1);
			return 1;
		case 2 :
			printf("See you soon !\n");
			sleep(2);
			return -1;
	}
	
	return -1;
}
int reservationNbPlace()
{
	int number;
	printf("\n How many places do you want to book ? \n");
	scanf(" %d", &number);
	return number;
}


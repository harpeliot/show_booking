
int idspectacle = 0;
Spectacle tabS[11];
int tabS_length = 11;
int	msqid;
int	semid;

msgbuf msgtxt;
char *msg = "\n";
typedef struct sembuf sembuf;
sembuf tache;

void initVerrous() {

semid = semget (12, 0, IPC_CREAT|IPC_EXCL|0600);

semctl (semid, 0, SETVAL, 1);

}

void lock()
{
	tache.sem_num = 0;
	tache.sem_op = -1;
	tache.sem_flg = 0;
	semop(semid,&tache,1);
}

void unlock()
{
	tache.sem_num = 0;
	tache.sem_op = 1;
	tache.sem_flg = 0;
	semop(semid,&tache,1);
}


int getRepresentationNumber(char title[])
{
	int nbRepresentation = 0;
	for(int i = 0; i < tabS_length; i++)
	{
		if(!strcmp(tabS[i].title,title))
		{
			nbRepresentation++;
		}
	}
	return nbRepresentation;
}

int makeReservation(short id, short nbPlaces)
{
	if(tabS[id].left_places >= nbPlaces)
	{
		tabS[id].left_places -= nbPlaces;
		if(tabS[id].left_places == 0)
		{
			printf("Ce sont les dernières places !\n");
		}
		return 1;
	}
	else
	{
		return -1;
	}
	return 0;
}

Spectacle* getLeftPlacesForTitle(char title[], Spectacle tabR[])
{
	int	i	= 0;
	for(int j = 0; j < tabS_length; j++)
	{
		if(!strcmp(tabS[j].title ,title))
		{
			tabR[i] = tabS[j];
			i++;
		}
	}
	return tabR; 
}

Spectacle* getLeftPlacesForId(int id, Spectacle tabR[])
{
	for(int j = 0; j < tabS_length; j++)
	{
		if(tabS[j].id == id)
		{
			tabR[0] = tabS[j];
		}
	}
	return tabR; 
}

void addSpectacle(unsigned short int place, char title[], int representation)
{
	Spectacle s;
	strcpy(s.title, title);
	s.left_places = place;
	s.id = idspectacle;
	s.representation = representation;
	tabS[s.id] = s;
}

void newSpectacle(char title[], unsigned short int place)
{	//TO DO have to create two spectacle with 1 representation
	//while (place == 0)
	//{
	//	printf("Error : invalid number of place");
	//	place = (unsigned short int) scanf("%d");
	//} 
	//while (title[0] == null)
	//{
	//	printf("Error : empty title");
	//	title = scanf("%s");
	//} Ckeck if tabS not full
	addSpectacle(place,title,1);
	idspectacle++;
	addSpectacle(place,title,2);
	idspectacle++;

}
void createShow()
{
	newSpectacle("L'Avare",45);
	newSpectacle("Dune",150);
	newSpectacle("Eiffel",400);
	newSpectacle("Feek",15);
	newSpectacle("Elton",90);
}



void consultation()
{
	while(1)
	{
		if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)12,0)!=-1)
		{
			printf("%s\n",msgtxt.mtext);
			msgtxt.mtype=13;
			for(int i=0;i<11;i++)
			{
				msgtxt.tab[i]=tabS[i];
			}
			printf( "consultation\n");
			//strcpy(msgtxt.mtext,msg);
			//if si pas error
			msgsnd(msqid, &msgtxt,  sizeof(msgbuf)-sizeof(long), 0);
		}else
		{
			perror("msgrcv");
		 	exit(1);
		}
	}
}


void reservation()
{
	
	if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)16,0)!=-1)
	{
		printf("reservation\n");
		//Poser verrou
		lock();
		if(1 == makeReservation(msgtxt.idReservation,msgtxt.nbReservation))
		{
			msg = "Booking confirmed\n";
		}else
		{
			msg = "The booking is sold out";
		}
		strcpy(msgtxt.mtext,msg);
		msgtxt.mtype=17;
		//Enlever verrou
		unlock();
		msgsnd(msqid, &msgtxt,  sizeof(msgbuf)-sizeof(long), 0);
		pthread_exit(NULL);
	}
}


//Non utilisé
//void * displayAllShow()
//{
//	displaySpectacle(tabS, tabS_length);
//	return 0;
//}


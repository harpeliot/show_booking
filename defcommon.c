#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#define KEY 42

typedef struct Spectacle Spectacle;

struct	Spectacle
{
	int			id;
	char			title[200];
	unsigned short int	representation;
	unsigned short int	left_places;
};


typedef struct msgbuf msgbuf;

struct msgbuf
{
	long mtype; /* type du message */
	char mtext [256]; /* contenu du message */
	Spectacle tab[11];
	short idReservation;
	short nbReservation;
};

int msqid;
void sortieImminente()
{
	printf("Au revoir\n");
	//pthread_exit();
	msgctl(msqid, IPC_RMID, NULL);
	exit(0);
}

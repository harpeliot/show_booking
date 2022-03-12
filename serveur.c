#include "defcommon.c"
#include "defserveur.c"



int	main(void)
{
//PREPARATION DE L ENVIRONNEMENT
//Creation MSQ	
	
	if((msqid=msgget((key_t)KEY,0750|IPC_CREAT|IPC_EXCL))==-1)
	{
         	perror("msgget");
         	exit(1);
    	}
    	semid = semget (12, 1, IPC_CREAT|IPC_EXCL|0666);
    	semctl(semid, 0, SETVAL, 1);
// Récupération connexion client
//	int msqid2;
//	msqid2 = msgrcv(msqid,&msgtxt,255,(long)12,0);
//	msgtxt.mtext[x] = 0;
//	printf("attente...s\n %s \n", msgtxt.mtext);
//Création des spectacles
	createShow();
	pthread_t	leger_consult;
	pthread_create(&leger_consult,NULL,(void*(*)())consultation,NULL);
	signal(SIGINT, (__sighandler_t) sortieImminente);
	initVerrous();
	printf("A l'ecoute..\n");
	
	//INTERFACES DEMARRAGE
	//displayAllShow();
		
	while(1){
	//connexion entrante
//	if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)10,0)!=-1)
//	{
//		printf("%s\n",msgtxt.mtext);
//	}
//	else
//	{
//		printf("Erreur\n");
//	}
	//consultation
	
	//GESTION RECEPTION REQUETE
	if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)14,0)!=-1)
		{
			printf("%s\n",msgtxt.mtext);
			
			while(tache.sem_op == -1)
			{
			//verrou if not verrouille suite sinon reservation deja en cours et faire file d attente.		
			printf("verouille\n");
			//wait pid
			}
				pthread_create(&leger_consult,NULL,(void*(*)())reservation,NULL);
		}else{
			perror("msgrcv error");	
		}
	//RESERVATION FORK
		
			//Verrou
			//New thread qui traite la reservation et renvoie

			
	}

}

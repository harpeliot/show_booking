#include "defcommon.c"
#include "defclient.c"
msgbuf msgtxt;
int msqid;
int	main(void)
{
char *msg = "init";
	if(1 == starting())
	{
		//Récupération propre de la MSQ
		if(-1 == (msqid = msgget((key_t)KEY,0)))
			{
				perror("msgget");
				exit(0);
			}
		//Envoi de la nouvelle connexion du client au serveur	
//		char *msg = "connexion client";	
//		msgtxt.mtype = 10;
//		strcpy(msgtxt.mtext,msg);
//		msgsnd(msqid, &msgtxt,  sizeof(msgbuf)-sizeof(long), 0);
		//Menu d'action du client sur le serveur
		int choose;
		int quit=false;
		while(!quit)
		{
			choose = chooseAction();
			
			//CONSULTATION
			if(1==choose)
			{
			//Ajouter une msq pour connexion client avant et ici pour demander comme reponse la reponse suite a la demande la 12 actuellement
					msg = "demande consultation";
					strcpy(msgtxt.mtext,msg);	
					msgtxt.mtype = 12;
					msgsnd(msqid, &msgtxt, sizeof(msgbuf)-sizeof(long), 0);
				if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)13,0)!=-1)
				{
					displaySpectacle(msgtxt.tab, 11);
					
				}
			}
			//RESERVATION
			if(2==choose)
			{
				if(1 == reservationProcess())
				{
					//envoi infos pour verrou
					msg = "Reservation en cours";
					strcpy(msgtxt.mtext,msg);
					msgtxt.mtype = 14;
					msgsnd(msqid, &msgtxt, sizeof(msgbuf)-sizeof(long), 0);
					//preparation envoi id et nb place
					msgtxt.idReservation = (short)reservationId();
					msgtxt.nbReservation = (short)reservationNbPlace();
					//validation a ajouter
					msgtxt.mtype = 16;
					//msg = "Demande de reservation envoyee";
					//strcpy(msgtxt.mtext,msg);
					msgsnd(msqid, &msgtxt, sizeof(msgbuf)-sizeof(long), 0);
					if(msgrcv(msqid,&msgtxt,sizeof(msgbuf)-sizeof(long),(long)17,0)!=-1)
					{
						printf("%s\n",msgtxt.mtext);
					}
					
					
				} 	
			}
			//SORTIE
			if(3==choose)
			{
				quit=true;
				sortieImminente();
				return -1;
			}
			
		}
		
		
	
	}
	//FIN DE LA VIE DU CLIENT	
	return 0;
}

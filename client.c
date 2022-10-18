/** Codi solucio de la practica: CLIENT **/
 
/* Inclusio de fitxers .h habituals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* Inclusio de fitxers .h per als sockets */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
#define MIDA_BUFFER 1024
 
int main(int argc, char **argv){
 
    if (argc != 2) {
        //Fem un sistema de control d'errors que atura l'execució si no s'ha indicat cap IP de destí
        printf("Error, escriu: %s IP\n", argv[0]); 
        exit(0);
    }
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in adr;
    char buffer[MIDA_BUFFER];
    char buffer2[MIDA_BUFFER];
    socklen_t mida;
    int i, num1,num2;
    bool comunication = true; //per defecte tenim comunicació
 
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);
 
    adr.sin_family = AF_INET;
    adr.sin_port = htons(44444); //posem el port 44444
 
    /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
    adr.sin_addr.s_addr = inet_addr(argv[1]);
 
    while(comunication){
       
        printf("escriu un missatge: \n"); //demanem un número a l'usuari
            scanf("%s", buffer);
        
        
            //Enviem el paquet
            sendto(s, buffer, strlen(buffer), 0, (struct sockaddr*)&adr, sizeof(adr));
        
            
            //Esperem la resporta del servidor
            recvfrom(s, buffer2, strlen(buffer2), 0,(struct sockaddr*)&adr, &mida);
             comunication = !(strcmp(buffer2, "chao chao\n")==0);
            if(!comunication){
                printf("Procedim a tancar la comunicació, que tinguis un bon dia :)\n \n");
            }else{
                printf("tú: %s\nx: %s\n",buffer,buffer2); //mostrem el chat per pantalla
            }
            

    }
   
 
    /* Tanquem el socket */
    close(s);
    return 0;
}

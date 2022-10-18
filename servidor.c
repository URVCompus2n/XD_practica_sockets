/* Codi solucio de la practica: SERVIDOR */
 
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
#include <stdbool.h>
#define MIDA_BUFFER 1024

int main( ){
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in serv_adr, client_adr;
    char buffer[MIDA_BUFFER];
    char buffer2[MIDA_BUFFER];
    socklen_t mida;
    int n, i;
    bool comunication = true; //per defecte tenim comunicació
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);
 
    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr("10.112.201.2");
    serv_adr.sin_port =  htons(44444);
 
    /* Enllacem el socket */
    n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
 
    if (n < 0)
    {
        printf("No s'ha pogut enllacar el socket\n");
    }
    else
    {
 
        /* Servidor operatiu! */
        while(comunication){
                //fem un bucle mentre hi hagi comunicació
            printf("Per sortir de la conversa escriu \"chao chao\"\n");
 
 
            recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
            printf("x: %s.\n",buffer); //mostrem el buffer per pantalla

            comunication = !(strcmp(buffer, "chao chao\n")==0);
            if(!comunication){
                printf("Procedim a tancar la comunicació, que tinguis un bon dia :)\nEscriu-lo \"chao chao\" \n");
            }
            fgets(buffer2, MIDA_BUFFER, stdin); // demanem el missatge a l'usuari
        
 
            
            sendto(s, buffer2, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
 
            
        }
    }
 
    /* Tanquem el socket */
    close(s);
    return 0;
    
  

}


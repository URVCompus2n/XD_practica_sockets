/* Codi solucio de la practica: SERVIDOR */
/**
 * Copyright (c) 2022 Marina Dalumau Retuerto, Karim Badias Morales, David Domènech Pereira Da Silva
*/
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
    int n;
    bool comunication = true; //per defecte tenim comunicació
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);
 
    /* Posem les dades del socket */
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr("10.112.201.2");
    serv_adr.sin_port =  htons(44444);
     //mida = 0; //guardem la mida
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
           
            
 
            recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida);
            printf("Per sortir de la conversa escriu \"chao chao\"\n");
            printf("x: %s.\n",buffer); //mostrem el buffer per pantalla

            comunication = !(strcmp(buffer, "chao chao\n")==0);
            if(!comunication){
                printf("Procedim a tancar la comunicació, que tinguis un bon dia :)\nEscriu \"chao chao\" per despedir-te \n");
            }
            fgets(buffer2, MIDA_BUFFER, stdin); // demanem el missatge a l'usuari
        
 
            //Important remarcar que a la comunicació hem posat la longitud
            sendto(s, buffer2, strlen(buffer2)+1, 0, (struct sockaddr*)&client_adr, sizeof(client_adr));
 
            
        }
    }
 
    /* Tanquem el socket */
    close(s);
    return 0;
    
  

}


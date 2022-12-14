/** Codi solucio de la practica: CLIENT **/
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

int main(int argc, char **argv){
 
    if (argc != 2) {
        //Fem un sistema de control d'errors que atura l'execució si no s'ha indicat cap IP de destí
        printf("Error, escriu: %s IP\n", argv[0]); 
        exit(0);
    }
 
    int s;    /* Per treballar amb el socket */
    struct sockaddr_in adr;
    char text[MIDA_BUFFER-11];
    char buffer[MIDA_BUFFER];
    char buffer2[MIDA_BUFFER];
    char usuari[10];
    socklen_t mida;
    
    bool comunication = true; //per defecte tenim comunicació
 
    /* Volem socket d'internet i no orientat a la connexio */
    s = socket(AF_INET, SOCK_DGRAM, 0);
 
    adr.sin_family = AF_INET;
    adr.sin_port = htons(44444); //posem el port 44444
 
    /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */
    adr.sin_addr.s_addr = inet_addr(argv[1]);
    mida = sizeof(adr); //guardem la mida
    printf("Bon dia, indica'm quin és el teu nom d'usuari\n");
    fgets(usuari, MIDA_BUFFER, stdin); // demanem el nom d'usuari
    usuari[strlen(usuari)-1]='\0';
    printf("Hola %s. Benvingut\nSi vols marxar escriu \"chao chao\"", usuari);
    
        while(comunication){
        
            printf("escriu un missatge: \n"); //demanem un número a l'usuari
            fgets(text, MIDA_BUFFER, stdin); // demanem el missatge a l'usuari
             comunication = !(strcmp(text, "chao chao\n")==0);
            if(!comunication){
                printf("Has tancat la conexió, que tinguis un bon dia :)\n");
            }else{
               
            
            sprintf(buffer,"%s: %s",usuari,text);
            //Enviem el paquet
            buffer[strlen(buffer)-1]='\0';
            sendto(s, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&adr, sizeof(adr));
           
            
            //Esperem la resporta del servidor
            recvfrom(s, buffer2,MIDA_BUFFER, 0,(struct sockaddr*)&adr, &mida);
             printf("%s\n%s\n",buffer,buffer2); //mostrem el chat per pantalla
            }

    }
   
 
    /* Tanquem el socket */
    close(s);
    return 0;
}

//cliente que estabelece uma conexao TCP com um servidor usando sockets. 

/*Essas sao as bibliotecas necessarias para utilizar as funcoes relacionadas a sockets como criar, conectar e enviar dados atraves de sockets.*/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

//Definimos uma constante para o numero da porta na qual o servidor ouvira as conexoes. Neste caso, a porta e 8080.
#define PORT 8080

int main(int argc, char const *argv[]) // main recebe os argumentos
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr; //usado para armazenar o endereco do servidor
    char *hello = "Ola do Cliente"; //mensagem de saudacao "hello"
    char buffer[1024] = {0}; //buffer para receber dados do servidor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) //criacao do socket TCP
    {
        printf("\n ERRO NA CRIACAO DO SOCKET \n");
        return -1; //retorna -1 em caso de erro na criacao
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr)); //preenche a estrutura com zeros
    
    serv_addr.sin_family = AF_INET;  //definicao do tipo de endereco 
    serv_addr.sin_port = htons(PORT);  //difinicao porta do servidor.
    
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) //Conversao do endereco IP do servidor para um texto
    {
        printf("\nENDERECO INVALIDO/ ENDERECO NAO SUPORTADO \n");
        return -1;  // retorna -1 se der erro
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) //conectar o socket ao endereco
    {
        printf("\nFALHA NA CONEXAO \n"); 
        return -1;  // tratador em caso de erro
    }
    send(sock , hello , strlen(hello) , 0 ); //Envia a mensagem "hello" para o servidor
    printf("Mensagem de Ola enviada\n");
    valread = read( sock , buffer, 1024); //leitura dados recebidos do socket. de ate 1024bytes
    printf("%s\n",buffer );
    return 0;
}

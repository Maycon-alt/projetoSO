#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080 //porta e 8080.
int main(int argc, char const *argv[])
{
    int server_fd, new_socket; //arquivo do novo socket criado quando tem uma conexao aceita
    long valread;
    struct sockaddr_in address; //armazenar informacoes do endereco do servidor
    int addrlen = sizeof(address);

    char hello[] =
        "HTTP/1.1 200 Ok\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><title>Sistemas Operacionais</title>\r\n"
        "<style>body{background-color: jade; text-align:center; background-color: jade;font-family: 'Courier New';line-height: 30px;}</style>"
        "<body><h1>Escalacao Vasco da Gama</h1><h2>Sistemas Operacionais 2023.1</h2><ul><li>Maycon Thiago - Camisa 10</li><li>Francisco de Assis - Goleiro 1</li><li>Breno Fernandes - Camisa 9</li><li>Nelson Vasconcelos - Tecnico</li></ul></body>"
        "</html>";


    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //retorna um descritor de arquivo que representa o socket
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; // Define o tipo de endereco como AF_INET para endereco IPv4
    address.sin_addr.s_addr = INADDR_ANY;  //Definido para o servidor possa aceitar conexoes em todos os IPs disponiveis
    address.sin_port = htons(PORT); //definida a porta

    memset(address.sin_zero, '\0', sizeof address.sin_zero); //entopir a estrutura de zeros

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) //Associa o socket a um endereco IP e porta especificos
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) //Coloca o socket em modo de escuta para aguardar por conexoes de clientes
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while (1)  //O servidor entra em um loop infinito que aguarda por conexoes de clientes 
    {
        printf("\n------- ESPERANDO POR UMA NOVA CONEXAO -------\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) //Quando uma conexao e aceita, um novo socket e criado
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000); //O servidor le os dados recebidos do cliente usando a funcao e armazena no buffer
        printf("%s\n", buffer);
        write(new_socket, hello, strlen(hello)); //envia a resposta HTTP para o cliente
        printf("------------------Mensagem de Ola enviada!-------------------");
        close(new_socket); // O socket new_socket e fechado
    }
    return 0;
}
/* 
*Mustafa Kemal GOKCE
*Socket Programlama 
*21.06.2021

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(int argc, char **argv){

    if (argc == 1){
        printf("Lutfen Port numarasini giriniz! \n");
        return 0;
    }
    int portNumber = atoi(argv[1]);
    char serverMessage[256] = "Servera baglandiniz. \n";
    // Socket Olusturma
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1 ) perror("server_sock");
    // Server adres tanimlama 
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(portNumber);
    server_adress.sin_addr.s_addr = INADDR_ANY;

    // Binding
    bind(server_sock,(struct sockaddr*) &server_adress, sizeof(server_adress));

    listen(server_sock, 5);

    int client_sock = accept(server_sock, NULL, NULL );

    send(client_sock, serverMessage, sizeof(serverMessage), 0);

    close(server_sock);

    return 0;

}

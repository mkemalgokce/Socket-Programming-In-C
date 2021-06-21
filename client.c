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

#include <arpa/inet.h>
#include <netinet/in.h>

int main (int argc, char **argv){
    if(argc == 1){
        printf("Lutfen port giriniz ! \n");
        return 0;
    }
    int portNumber = atoi(argv[1]);
    // Socket Olusturma
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) perror("sock");
    // Socket icin degerlerin atanmasi
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portNumber);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    int con = connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
    
    if (con == -1){
        perror("con");
        return 0;
    }
    char server_response[256];

    recv(sock, &server_response, sizeof(server_response), 0);

    printf("Server sent this data : %s \n", server_response);

    close(sock);

    return 0;
}



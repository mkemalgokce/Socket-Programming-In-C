/* 
*Mustafa Kemal GOKCE
*Socket Programlama 
*21.06.2021

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

void send_file(int sock, int buffer_size){
    // Dosya yollamaya yarayan fonksiyon.
    send(sock,"dosya",128,0);
    FILE *fp;
    fp = fopen("a.jpg","rb");
    char buffer[buffer_size];
    while(fgets(buffer,buffer_size,fp) != NULL){
        
        if(send(sock, buffer, sizeof(buffer), 0 ) == -1){
            perror("[-] Dosya yollanirken hata olustu !");
            exit(EXIT_FAILURE);
        }
        memset(buffer, 0, buffer_size);
        
    }
    if(send(sock, "bitti", sizeof("bitti"), 0 ) == -1){
            perror("[-] Dosya yollanirken hata olustu !");
            exit(EXIT_FAILURE);
        }
    fclose(fp);
    return;
}
int main(int argc, char **argv){
    
    if (argc != 3){
        printf("[!] Lutfen Port ve IP numarasini giriniz! \n");
        exit(EXIT_FAILURE);
    }
    int port_number = atoi(argv[2]);
    char *ip = argv[1];
    char serverMessage[256] = "Servera baglandiniz. \n";
    int status = 0;
    // Socket Olusturma
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("[-] Socket olusturulurken hata olustu !");
        exit(EXIT_FAILURE);
    }
    printf("[+] Socket olusturuldu. \n");
    // Socket icin degerlerin atanmasi
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(ip);
    
    int con = connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));

    if (con == -1){
        perror("[-] Baglanti saglanamadi !");
        exit(EXIT_FAILURE);
    }
    printf("[+] Baglanti olusturuldu. \n");
    char server_response[256];

    send_file(sock, 2048);
    printf("[+] Dosya yollandi. \n");
    recv(sock, &server_response, sizeof(server_response), 0);
    printf("Serverden gelen data : %s ", server_response);


    return 0;
}



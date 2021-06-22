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
#include <string.h>

#include <arpa/inet.h>

void read_file(int sock, int buffer_size){
    // Dosya okumaya yarayan fonksiyon.
    FILE *fp = fopen("new_a.txt","wb");
    printf("[..] Dosya okunuyor.");
    char buffer[buffer_size];
    while(1){
        
        recv(sock,buffer,buffer_size,0);
        if(strcmp("bitti",buffer) == 0){
            break;
        }
        fprintf(fp,"%s",buffer);
        memset(buffer, 0, buffer_size);
        
    }
    
    fclose(fp);
    return;
}
int main(int argc, char **argv){

    int port_number = atoi(argv[2]);
    char *ip = argv[1];
    char serverMessage[256] = "[!] Server kapaniyor... \n";
    int status = 0;
    char buffer[1024];
    if (argc != 3){
        printf("[!] Lutfen Port ve IP numarasini giriniz! \n");
        exit(EXIT_FAILURE);
    }
    // Socket Olusturma
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1 ) {
        perror("[-] Socket olustururken hata olustu !");
        exit(EXIT_FAILURE);
    }
    printf("[+] Server socketi olusturuldu. \n");
    // Server adres tanimlama 
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(port_number);
    server_adress.sin_addr.s_addr = inet_addr(ip);

    // Binding
    status = bind(server_sock,(struct sockaddr*) &server_adress, sizeof(server_adress));
    if(status < 0){
        perror("[-] Bind'larken hata olustu !");
        exit(EXIT_FAILURE);
    }
    printf("[+] Bind islemi basarili. \n");

    status = listen(server_sock, 5);
    if(status < 0){
        perror("[-] Listen islemi basarisiz !");
        exit(EXIT_FAILURE);
    }
    printf("[+] Dinleniyor ... \n");

    int client_sock = accept(server_sock, NULL, NULL );
    
    while (1){
        
        recv(client_sock,buffer,128,0);
        if(strcmp(buffer, "dosya") == 0){
            
            read_file(client_sock, 2048);
            printf("[+] Okuma tamamlandi. \n");
        }
        else if(strcmp(buffer, "bitir") == 0 ){
            break;
        }
        
    }
    
    send(client_sock, serverMessage, sizeof(serverMessage), 0);
    
    close(server_sock);
    
    return 0;

}

// Cliente UDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXBUFSIZE 1000 // O tamanho max. do pacote UDP Packet é 64 Kbytes (65535 bytes, que é o valor máximo representado pelos dois bytes destinados ao tamanho do datagrama UDP).
//Descontados os cabeçalhos do UDP e do IP temos 65507 bytes.

int main() {
    int sock, status, socklen;
    int temperatura;
    unsigned char buffer[MAXBUFSIZE];
    struct sockaddr_in saddr;

    memset(&saddr, 0, sizeof(struct sockaddr_in));

    // Abre um socket UDP
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(0);
    }

    // Usa a interface DEFAULT
    //saddr.sin_port = htons(60000); // Associa porta 60000 (cliente).

    status = bind(sock, (struct sockaddr *) &saddr,
                  sizeof(struct sockaddr_in)); // Se nenhuma porta para o cliente foi especificada
    // Associa o socket com uma porta livre do cliente para enviar dados - portas altas

    // Define IP e porta de destino
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(38000); // Porta 38000. (big endian x little endian)

    int random;

    while(1) {

        srand(time(0));
        random = 1 + rand() % 9;

        if (status < 0) {
            perror("Error binding socket to interface");
            exit(0);
        }

        system("clear");
        printf("\t##### UDP client #####\n");

        printf("\tSending hello to UDP server 127.0.0.1\n");

        //preenche buffer com zeros
        memset(&buffer, 0, sizeof(buffer));

        // Escreve dados no buffer
//   strcpy(buffer, "Hello!");
//    strcpy(buffer, "1");

        if(random < 5) {
            strcpy(buffer, "1 Me manda isso aí");
        }
        else {
            strcpy(buffer, "223 Duvido me mandar isso aí");
        }

        socklen = sizeof(struct sockaddr_in);

        // Envia
        printf("\tTo port %d...\n", htons(saddr.sin_port));

        status = sendto(sock, buffer, strlen(buffer), 0,
                        (struct sockaddr *) &saddr, socklen);

        // Preenche o buffer com zeros
        memset(&buffer, 0, sizeof(buffer));

        printf("\tWaiting for response...\n");

        // Recebe resposta
        status = recvfrom(sock, buffer, MAXBUFSIZE, 0,
                          (struct sockaddr *) &saddr, &socklen);


        printf("\tReceived data:\n\t%s\n\n\tFrom %s, port %d\n\n", buffer, inet_ntoa(saddr.sin_addr),
               htons(saddr.sin_port));

        if(status<0) {
            printf("\tDeu ruim, status: %i\n", status);
        }

        sleep(5);
    }


    shutdown(sock, 2);
    close(sock);

    return 0;
}

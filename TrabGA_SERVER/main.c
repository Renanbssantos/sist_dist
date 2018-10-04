// Servidor UDP

//IMPORTANTE!!!
//Fazer modelagem do servidor:
//a) Com máquina de estados.
//b) Com fluxograma.


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
#include <stdbool.h>
#include <float.h>

#define MAXBUFSIZE 1000 // O tamanho max. do pacote UDP Packet é 64 Kbytes (65535 bytes, que é o valor máximo representado pelos dois bytes destinados ao tamanho do datagrama UDP).

/*
** reverse string in place
*/
void reverse(char *s) {
    char *j;
    int c;

    j = s + strlen(s) - 1;
    while (s < j) {
        c = *s;
        *s++ = *j;
        *j-- = c;
    }
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

//Descontados os cabeçalhos do UDP e do IP temos 65507 bytes.
int main() {
    int sock, status, socklen;
    unsigned char buffer[MAXBUFSIZE];
    unsigned char rng[MAXBUFSIZE];
    struct sockaddr_in saddr;

    memset(&saddr, 0, sizeof(struct sockaddr_in));

    // Abre um socket UDP
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        perror("Error creating socket");
        exit(0);
    }

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(38000); // Escuta na porta 38000. (big endian x little endian)

    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    status = bind(sock, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in));

    if (status < 0) {
        perror("Error binding socket to interface");
        exit(0);
    }

    socklen = sizeof(struct sockaddr_in);

    system("clear");
    printf("\t##### UDP server #####\n");
    printf("\tWaiting for requests...\n");

    printf("\tport %d...\n", htons(saddr.sin_port));

    int temperatura;

    while (1) {
        srand(time(0));
        temperatura = 1 + rand() % 9;

        printf("\tTemperatura: %i\n", temperatura);

        // Recebe dados do socket
        status = recvfrom(sock, buffer, MAXBUFSIZE, 0,
                          (struct sockaddr *) &saddr, &socklen);

        // Envia resposta
        printf("\tReceived data: %s From: %s, port: %d\n\n", buffer, inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));

        // Verifica se o primeiro byte do buffer é igual a 1
//        if (!strcmp(buffer, "1")) {
        if(buffer[0] == '1'){
            printf("\tEntrou aqui\n");
            printf("\tSending response...\n");


            itoa(temperatura, &rng);
            strcat(buffer, rng);

            status = 0;
            status = sendto(sock, buffer, strlen(buffer), 0,
                            (struct sockaddr *) &saddr, socklen);
        } else {
            printf("\tNão entrou aqui, pois o valor do buffer é: %s \n", buffer);
            printf("\tTem uma mensagem de erro genérica aqui\n");


//            strcpy(buffer, "Hello, Im am the server.\n");

            memset(&buffer, 0, sizeof(buffer));

            strcat(buffer, "255");

            status = 0;
            status = sendto(sock, buffer, strlen(buffer), 0,
                            (struct sockaddr *) &saddr, socklen);
        }

        // Preeenche o buffer com zeros
        memset(&buffer, 0, sizeof(buffer));
        memset(&buffer, 0, sizeof(rng));

        // Escreve msg no buffer
//        strcpy(buffer, "Hello, Im am the server.\n");

        // Envia
//        status=0;

//        printf("\tSending response...\n");
//        status = sendto(sock, buffer, strlen(buffer), 0,
//                        (struct sockaddr *)&saddr, socklen);
    }
    shutdown(sock, 2);
    close(sock);

    return 0;
}

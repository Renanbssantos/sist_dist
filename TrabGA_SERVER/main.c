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

int sock, status, socklen;
unsigned char buffer[MAXBUFSIZE];
unsigned char rng[MAXBUFSIZE];
struct sockaddr_in saddr;

void fechaSocket();

void preencheBuffersComZeros();

void iniciaServidorUDP();

void medeUmidade();

void medeTemperatura();

void medeVolume();

int temperatura;
int volume;
int umidade;

bool verificaCodigoDeIdentificacao(char bufferDeVerificacao[]) {
    if(bufferDeVerificacao[0] == '1') {
        return true;
    }
    else {
        return false;
    }
}

void configuraSocketUDP() {
    memset(&saddr, 0, sizeof(struct sockaddr_in));

    // Abre um socket UDP
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        perror("Erro ao criar socket");
        exit(0);
    }

    saddr.sin_family = PF_INET;
    saddr.sin_port = htons(38000); // Escuta na porta 38000. (big endian x little endian)

    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    status = bind(sock, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in));

    if (status < 0) {
        perror("Erro no binding do socket em uma interface");
        exit(0);
    }

    socklen = sizeof(struct sockaddr_in);

    system("clear");
    printf("\t##### Servidor UDP #####\n");
    printf("\tEsperando por chamadas...\n");

    printf("\tport %d...\n", htons(saddr.sin_port));
}

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

    configuraSocketUDP();

    iniciaServidorUDP();

    fechaSocket();

    return 0;
}

void iniciaServidorUDP() {
    while (1) {
        srand(time(0));

        medeTemperatura();
        medeUmidade();
        medeVolume();

        printf("\tTemperatura: %i\n", temperatura);

        printf("\tUmidade: %i\n", umidade);

        printf("\tVolume: %i\n", volume);


        // Recebe dados do socket
        status = recvfrom(sock, buffer, MAXBUFSIZE, 0,
                          (struct sockaddr *) &saddr, &socklen);

        // Envia resposta
        printf("\tDado recebido: %s De: %s, port: %d\n\n", buffer, inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));

        // Verifica se o primeiro byte do buffer é igual a 1
        if(verificaCodigoDeIdentificacao(buffer)) {
            printf("\tEntrou aqui\n");
            printf("\tEnviando resposta...\n");


            itoa(temperatura, rng);
            strcat(buffer, rng);

            status = 0;
            status = sendto(sock, buffer, strlen(buffer), 0,
                            (struct sockaddr *) &saddr, socklen);
        } else {
            printf("\tNão entrou aqui, pois o valor do buffer é: %s \n", buffer);
            printf("\tTem uma mensagem de erro genérica aqui\n");


            preencheBuffersComZeros();

            strcat(buffer, "255");

            status = 0;
            status = sendto(sock, buffer, strlen(buffer), 0,
                            (struct sockaddr *) &saddr, socklen);
        }

        // Preeenche o buffer com zeros
        preencheBuffersComZeros();
    }
}

void medeVolume() { volume = 1 + rand() % 9; }

void medeTemperatura() { temperatura = 1 + rand() % 50; }

void medeUmidade() { umidade = 1 + rand() % 100; }

void preencheBuffersComZeros() {
    memset(&buffer, 0, sizeof(buffer));
    memset(&buffer, 0, sizeof(rng));
}

void fechaSocket() {
    shutdown(sock, 2);
    close(sock);
}

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
#define PERIODO_DE_CHAMADAS_EM_SEGUNDOS 5
#define CHAMADA_TEMPERATURA "1TEM"
#define CHAMADA_UMIDADE "1UMI"
#define CHAMADA_VOLUME "1VOL"
#define CHAMADA_TESTE_ERRO_IDENTIFICACAO "2asd"
#define CHAMADA_TESTE_ERRO_CHAMADA "1asd"
#define TAMANHO_CHAMADA 4
#define TAMANHO_RESPOSTA 4

int sock, status, socklen;
unsigned char buffer[MAXBUFSIZE];
unsigned char chamada[TAMANHO_CHAMADA];
unsigned char resposta[TAMANHO_RESPOSTA];

struct sockaddr_in saddr;


void configuraSocketUDP();

void limpaBuffer();

void fazChamadaAoServidor();

void fechaSocket();

void limpaChamada();

void limpaResposta();

void recebeRespostaDoServidor();

int main() {

    configuraSocketUDP();

    while (1) {

        system("clear");
        printf("\t##### Cliente UDP #####\n");

        srand(time(0));

        int probabilidade;

        probabilidade = 0 + rand() % 100;

        limpaBuffer();

        // Define a chamada
        if (probabilidade < 20) {
            strcat(chamada, CHAMADA_TEMPERATURA);
        }
        if (probabilidade >= 20 && probabilidade < 40) {
            strcat(chamada, CHAMADA_UMIDADE);
        }
        if (probabilidade >= 40 && probabilidade < 60) {
            strcat(chamada, CHAMADA_VOLUME);
        }
        if (probabilidade >= 60 && probabilidade < 80) {
            strcat(chamada, CHAMADA_TESTE_ERRO_CHAMADA);
        }
        if (probabilidade >= 80 && probabilidade < 100) {
            strcat(chamada, CHAMADA_TESTE_ERRO_IDENTIFICACAO);
        }

        printf("\tEnviando chamada:\n\t%s\n", chamada);

        fazChamadaAoServidor();

        recebeRespostaDoServidor();

        sleep(PERIODO_DE_CHAMADAS_EM_SEGUNDOS);
    }


    fechaSocket();

    return 0;
}

void fechaSocket() {
    shutdown(sock, 2);
    close(sock);
}

void fazChamadaAoServidor() {

    socklen = sizeof(struct sockaddr_in);

    // Envia
    printf("\tPara a porta %d...\n", htons(saddr.sin_port));

    status = sendto(sock, chamada, strlen(chamada), 0,
                    (struct sockaddr *) &saddr, socklen);

    // Preenche o buffer com zeros
    limpaBuffer();
    limpaChamada();

    printf("\tAguardando resposta...\n");

}

void recebeRespostaDoServidor() {// Recebe resposta
    status = recvfrom(sock, resposta, MAXBUFSIZE, 0,
                      (struct sockaddr *) &saddr, &socklen);


    printf("\tDado Recebido:\n\t%s\n\n\tDe %s, porta %d\n\n", resposta, inet_ntoa(saddr.sin_addr),
           htons(saddr.sin_port));

    limpaResposta();

    if (status < 0) {
        printf("\tErro ao fazer a chamada, status: %i\n", status);
    }
}

void limpaBuffer() { memset(&buffer, 0, sizeof(buffer)); }

void limpaChamada() { memset(&chamada, 0, sizeof(chamada)); }

void limpaResposta() { memset(&resposta, 0, sizeof(resposta)); }

void configuraSocketUDP() {

    memset(&saddr, 0, sizeof(struct sockaddr_in));

    // Abre um socket UDP
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Erro ao criar socket");
        exit(0);
    }

    status = bind(sock, (struct sockaddr *) &saddr,
                  sizeof(struct sockaddr_in));

    // Define IP e porta de destino
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(38000); // Porta 38000. (big endian x little endian)

    if (status < 0) {
        perror("Erro no binding do socket em uma interface");
        exit(0);
    }

}
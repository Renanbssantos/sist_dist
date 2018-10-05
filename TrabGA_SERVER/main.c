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

#define TAMANHO_BUFFER 1000 // O tamanho max. do pacote UDP Packet é 64 Kbytes (65535 bytes, que é o valor máximo representado pelos dois bytes destinados ao tamanho do datagrama UDP).
#define TAMANHO_CHAMADA 4
#define TAMANHO_RESPOSTA 4
#define IDENTIFICADOR '1'
#define CHAMADA_TEMPERATURA "TEM"
#define CHAMADA_UMIDADE "UMI"
#define CHAMADA_VOLUME "VOL"
#define RANGE_VALORES 99
#define ERRO_IDENTIFICADOR "IDER"
#define ERRO_CHAMADA "CHER"


int sock, status, socklen;
unsigned char buffer[TAMANHO_BUFFER];
unsigned char valorTraduzidoParaString[TAMANHO_BUFFER];
unsigned char chamada[TAMANHO_CHAMADA];
unsigned char resposta[TAMANHO_RESPOSTA];
struct sockaddr_in saddr;
int temperatura;
int volume;
int umidade;

void fechaSocket();

void limpaBuffers();

void iniciaServidorUDP();

void medeUmidade();

void medeTemperatura();

void medeVolume();

void enviaMensagemIdentificadorInvalido();

void limpaChamada();

bool verificaCodigoDeIdentificacao(char[]);

void configuraSocketUDP();

void reverse(char *);

void itoa(int, char[]);

void limpaResposta();

void preparaResposta(char[], int);

void efetuaMedicoes();

void escutaCliente();

void decodificaBufferParaChamada();

void enviaResposta();

void preparaMensagemErroDeChamada();

void filtraChamadas();

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

        efetuaMedicoes();

        escutaCliente();

        if(verificaCodigoDeIdentificacao(buffer)) {

            limpaChamada();

            limpaResposta();

            decodificaBufferParaChamada();

            printf("\tCHAMADA: %s\n", chamada);

            filtraChamadas();

            limpaBuffers();

            enviaResposta();
        }
        else {
            enviaMensagemIdentificadorInvalido();
        }

        // Preeenche o buffer com zeros
        limpaBuffers();
    }
}

void filtraChamadas() {
    if(!strcmp(chamada, CHAMADA_TEMPERATURA)) {
                printf("\tTEMPERATURA SOLICITADA, VALOR ATUAL: %i\n", temperatura);

                preparaResposta("T:", temperatura);
            }
    if(!strcmp(chamada, CHAMADA_UMIDADE)) {
                printf("\tUMIDADE SOLICITADA, VALOR ATUAL: %i\n", umidade);

                preparaResposta("U:", umidade);
            }
    if(!strcmp(chamada, CHAMADA_VOLUME)) {
                printf("\tVOLUME SOLICITADO, VALOR ATUAL: %i\n", volume);

                preparaResposta("V:", volume);
            }
    if(strcmp(chamada, CHAMADA_VOLUME) && strcmp(chamada, CHAMADA_UMIDADE) && strcmp(chamada, CHAMADA_TEMPERATURA)) {
                printf("\tCHAMADA INVALIDA: %s\n", chamada);

                preparaMensagemErroDeChamada();
            }
}

void preparaMensagemErroDeChamada() { strcat(resposta, ERRO_CHAMADA); }

void enviaResposta() {
    status = 0;

    status = sendto(sock, resposta, strlen(resposta), 0,
                            (struct sockaddr *) &saddr, socklen);
}

void decodificaBufferParaChamada() { strncpy(chamada, buffer + 1, 3); }

void escutaCliente() {// Recebe dados do socket
    status = recvfrom(sock, buffer, TAMANHO_BUFFER, 0,
                          (struct sockaddr *) &saddr, &socklen);

    printf("\n\tDado recebido: %s De: %s, port: %d\n", buffer, inet_ntoa(saddr.sin_addr), htons(saddr.sin_port));
}

void efetuaMedicoes() {
    medeTemperatura();
    medeUmidade();
    medeVolume();
}

void enviaMensagemIdentificadorInvalido() {
    printf("\tCodigo identificador invalido\n");
    limpaResposta();
    limpaBuffers();
    strcat(resposta, ERRO_IDENTIFICADOR);
    enviaResposta();
}

void medeVolume() { volume = 0 + rand() % RANGE_VALORES; }

void medeTemperatura() { temperatura = 0 + rand() % RANGE_VALORES; }

void medeUmidade() { umidade = 0 + rand() % RANGE_VALORES; }

void limpaBuffers() {
    memset(&buffer, 0, sizeof(buffer));
    memset(&valorTraduzidoParaString, 0, sizeof(valorTraduzidoParaString));
}

void limpaResposta() { memset(&resposta, 0, sizeof(resposta)); }

void limpaChamada() { memset(&chamada, 0, sizeof(chamada)); }

void fechaSocket() {
    shutdown(sock, 2);
    close(sock);
}

bool verificaCodigoDeIdentificacao(char bufferDeVerificacao[]) {
    if(bufferDeVerificacao[0] == IDENTIFICADOR) {
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

void preparaResposta(char medida[], int valor) {
    strcat(resposta, medida);
    itoa(valor, valorTraduzidoParaString);
    if(valor < 10) {
        strcat(resposta, "0");
    }
    strcat(resposta, valorTraduzidoParaString);
}

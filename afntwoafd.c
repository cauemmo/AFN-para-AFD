#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5000

typedef struct
{
    char origem[10];
    char X;
    char Destino[10];
    char trocaX;
    char Sentido;
}Transicao;

char estados[50][5],estado_inicial[5],estados_finais[50][5],alfabeto[10],alfabeto_fita[10];
int cont_transicoes,cont_estados_finais,cont_comp,cont_estados,cont_alfa_fita,cont_alf;
Transicao vet_Tran[50];

void ler_maquina()
{
    cont_transicoes = 0;
    cont_estados_finais = 0;
    cont_estados = 0;
    cont_alfa_fita = 0;
    cont_alf = 0;
    char aux, sentido;
    int bool;

    printf("Informe a quantidade de estados: \n");
    scanf("%d", &cont_estados);
    fflush(stdin);

    for(int i = 0; i < cont_estados; i++){
        printf("Informe o estado %d: \n", i);
        scanf("%s", estados[i]);
        fflush(stdin);
    }

    printf("Informe a quantidade de letras no alfabeto da maquina: \n");
    scanf("%d", &cont_alf);
    fflush(stdin);
    for(int i = 0; i < cont_alf; i++){
        printf("Informe a %d * letra do alfabeto da maquina: \n", i);
        scanf("%c", &alfabeto[i]);
        alfabeto_fita[i] = alfabeto[i];
        fflush(stdin);
    }
    cont_alfa_fita = cont_alf;
    alfabeto_fita[cont_alfa_fita] = 'B';
    alfabeto_fita[cont_alfa_fita  + 1] = 'X';
    cont_alfa_fita += 2;


    printf("Alfabeto da fita:");
    for(int i = 0; i < cont_alfa_fita; i++){
        if(i < cont_alfa_fita - 1) {
            printf("%c, ", alfabeto_fita[i]);
        }else{
            printf("%c", alfabeto_fita[i]);
        }
    }
    printf("\n");


    printf("Informe a quantidade de Transicoes: \n");
    scanf("%d", &cont_transicoes);
    fflush(stdin);
    for(int i = 0; i < cont_transicoes;i++){
        printf("Informe o estado de origem da %d * transicao : \n", i);

        scanf("%s", vet_Tran[i].origem);
        fflush(stdin);
        printf("Informe a letra de transicao da %d * transicao: \n", i);
        scanf("%c", &vet_Tran[i].X);
        fflush(stdin);
        printf("Informe o estado final da %d * transicao: \n", i);
        scanf("%s", vet_Tran[i].Destino);
        fflush(stdin);
        printf("O que sera colocado na fita depois da %d * transicao: \n", i);

        scanf("%c", &vet_Tran[i].trocaX);
        fflush(stdin);
        printf("Sentido que a fita andara depois da %d * transicao(D/E): \n", i);
        scanf("%c", &sentido);
        fflush(stdin);
        if((sentido == 'd') || (sentido == 'D')){
            vet_Tran[i].Sentido = 'D';
        }
        if((sentido == 'e') || (sentido == 'E')){
            vet_Tran[i].Sentido = 'E';
        }
    }

    printf("Informe o estado inicial: \n");
    scanf("%s", estado_inicial);
    fflush(stdin);
    printf("Informe a quantidade de estados finais: \n");
    scanf("%d", &cont_estados_finais);
    fflush(stdin);
    for(int i = 0; i < cont_estados_finais; i++){
        printf("Informe o estado final %d: \n", i);
        scanf("%s", estados_finais[i]);
        fflush(stdin);


    }

}
int testa_palavra(char palavra[]){
    int i,j,cont;
    for(i=1;i<strlen(palavra)-1;i++){
        cont=0;
        for(j=0;j<cont_alf;j++){
            if(palavra[i] != alfabeto[j]){
                cont++;
            }
        }
        if(cont == cont_alf){
            return 1;
        }
    }
    return 0;
}

int main ()
{
    ler_maquina();
    cont_comp = 0;
    char palavra[100],estado_atual[5],palavra_aux[100],estado_aux[5], entrada[50];
    char* Aux;
    Aux = malloc(100*sizeof(char));
    printf("Informe a palavra inicial\n");
    scanf("%s", entrada);
    strcpy(palavra,"B");
    strcat(palavra,entrada);
    strcat(palavra,"B");

    strcpy(estado_atual,"{");
    strcat(estado_atual,estado_inicial);
    strcat(estado_atual,"}");
    strcpy(estado_aux,estado_inicial);

    strcpy(Aux,estado_atual);
    strcat(Aux,palavra);

    strcpy(palavra_aux,Aux);
    free(Aux);

    int i=0;
    int parou = 0;
    if(testa_palavra(palavra) == 1){
        printf("Palavra fora do alfabeto.\n");
        return 0;
    }
    do{
        int k=0;
        printf("%s\n",palavra_aux);
        while(k < cont_transicoes){
            if(palavra[i] == vet_Tran[k].X && strcmp(estado_aux,vet_Tran[k].origem)==0)
                break;
            k++;
        }
        if(k == cont_transicoes){
            int w=0;
            while(w < cont_estados_finais){
                if((strcmp(estado_aux,estados_finais[w])==0)){
                    parou = 1;
                    printf("aceita\n");
                }
                w++;
            }
            if(parou == 0){
                printf("rejeita\n");
                parou = 1;
            }
        }
        else{
            strcpy(estado_atual,"{");
            strcat(estado_atual,vet_Tran[k].Destino);
            strcat(estado_atual,"}");
            strcpy(estado_aux,vet_Tran[k].Destino);

            palavra[i] = vet_Tran[k].trocaX;
            if(vet_Tran[k].Sentido == 'D'){
                int j;
                char s[100];
                int c=0;
                for(j=i+1;j<strlen(palavra);j++){
                    s[c] = palavra[j];
                    c++;
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i+1);
                palavra_aux[i+1] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);
                i++;

            }
            else if(vet_Tran[k].Sentido == 'N'){
                int j;
                char s[50];
                int c=0;
                for(j=i;j<strlen(palavra);j++){
                    s[c] = palavra[j];
                    c++;
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i);
                palavra_aux[i] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);

            }
            else if(vet_Tran[k].Sentido == 'E'){
                int j;
                char s[50];
                int c=0;
                for(j=i-1;j<strlen(palavra);j++){
                    s[c] = palavra[j];
                    c++;
                }
                s[c] = '\0';
                strncpy(palavra_aux,palavra,i-1);
                palavra_aux[i-1] = '\0';
                strcat(palavra_aux,estado_atual);
                strcat(palavra_aux,s);
                i--;

            }
        }
        cont_comp++;
        if(cont_comp >= MAX){
            printf("Essa maquina pode ter entrado em loop, deseja continuar? <S/N>\n");
            char op;
            scanf("%c%*c",&op);
            if(op == 'S' || op == 's'){
                cont_comp = 0;
            }
            else{
                parou = 1;
            }
        }
    }while(parou == 0);

    return 0;
}

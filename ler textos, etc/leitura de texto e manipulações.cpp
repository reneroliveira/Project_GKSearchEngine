#include <iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;




int main(){
    char vetor[4];


    FILE *arquivo;
    arquivo = fopen("arch.txt","wt"); // ponteiro que aponta para o espa�o de memoria onde est� o nosso arch.txt
                                      // wt grava��o
                                      // rt leitura - a append
    if(arquivo == NULL){
        printf("nao foi possivel abrir o arquivo");
        exit(0); // corta execu��o do programa
    }
    fprintf(arquivo,"ol�");   //gravar strings no arquivo
                              //para ler , temos q abir modo leitura
    fclose(arquivo);
    arquivo = fopen("arch.txt","rt");

    if(arquivo == NULL){
        printf("nao foi possivel abrir o arquivo");
        exit(0); // corta execu��o do programa
    }
    fscanf(arquivo,"%s",&vetor);
    printf(vetor);


    fclose(arquivo);

   return 0;
}

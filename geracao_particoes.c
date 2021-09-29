//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 18/09/2021.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geracao_particoes.h"
#include "nomes.h"
#include "cliente.h"


void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
	int fim = 0; //variável de controle para saber se arquivo de entrada terminou
    FILE *arq; //declara ponteiro para arquivo

    //abre arquivo para leitura
    if ((arq = fopen(nome_arquivo_entrada, "rb")) == NULL) {
        printf("Erro ao abrir arquivo de entrada\n");
    } else {

        //le primeiro cliente
        Cliente *cin = le_cliente(arq);

        while (!(fim)) {
            //le o arquivo e coloca no vetor
            Cliente *v[M];

            int i = 0;
            while (!feof(arq) && i < M) {
                v[i] = cin;
                cin = le_cliente(arq);
                i++;
            }

            //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
            if (i != M) {
                M = i;
            }

            //faz ordenacao
            for (int j = 1; j < M; j++) {
                Cliente *c = v[j];
                i = j - 1;
                while ((i >= 0) && (v[i]->cod_cliente > c->cod_cliente)) {
                    v[i + 1] = v[i];
                    i = i - 1;
                }
                v[i + 1] = c;
            }

            //cria arquivo de particao e faz gravacao
            char *nome_particao = nome_arquivos_saida->nome;
            nome_arquivos_saida = nome_arquivos_saida->prox;

            FILE *p;
            if ((p = fopen(nome_particao, "wb")) == NULL) {
                printf("Erro criar arquivo de saida\n");
            } else {
                for (int i = 0; i < M; i++) {
					salva_cliente(v[i], p);
                }
                fclose(p);
            }
            if (feof(arq)) {
                fim = 1;
            }
        }
    }
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes

    Cliente *le[M], *aux[M];
    Cliente *recemGravado;
    Nomes *novaParticao, *proximo;
    int i = 0, contCongelado = 0, controlador = 1;

    //Abrindo arquivo para leitura
    FILE* entrada = fopen(nome_arquivo_entrada,"rb");
    if(entrada == NULL){
        printf("Erro ao abrir com sucesso");
    }else {
        int posvet = 0;



        FILE* write;
        //Abrindo arquivo para escrita
        write = fopen(nome_arquivos_saida->nome, "wb");
        if(write == NULL){
            printf("Erro ao abrir arquivo");
        }

        proximo = nome_arquivos_saida->prox;
        Cliente *menor;
        menor = (Cliente*)malloc(sizeof(Cliente));


        while (!feof(entrada)) {
            int menorcmp = 100;
            //enquanto nao chegar no fim do arquivo, vai pegando o menor valor
            //condicao para encher o vetor
                if(controlador == 1) {
                    while (i < M && !feof(entrada)) {
                        le[i] = le_cliente(entrada);
                        i++;
                    }
                    controlador = 0;
                    if(i == 1){
                        break;
                    }else if(i != M){
                        M = i-1;
                    }
                }



            for(int j = 0; j < M; j++){
                //tem que ser difente, pois se for igual esta congelado
                    if (le[j]->cod_cliente < menorcmp && le[j]->cod_cliente != 0){
                        menor = le[j];
                        menorcmp = le[j]->cod_cliente;
                        posvet = j;
                    }

            }


            //grava no arquivo
            salva_cliente(le[posvet], write);
            //ler a proxima linha
            recemGravado = le[posvet];
            le[posvet] = le_cliente(entrada);

            if(le[posvet] != NULL) {
                if (le[posvet]->cod_cliente < recemGravado->cod_cliente) {
                    //indica que esta congelado
                    Cliente *temp = (Cliente*) malloc(sizeof(Cliente));
                    temp->cod_cliente = le[posvet]->cod_cliente;
                    strcpy(temp->nome, le[posvet]->nome);
                    //passando para a proxima particao
                    aux[contCongelado] = temp;
                    le[posvet]->cod_cliente = 0;
                    contCongelado++;
                }
            }else{
                //primeira vez que entrar
                if(contCongelado == 0){
                  //no caso, se ele não tiver nenhum cont congelado e o arquivo estiver no fim
                  menorcmp = 100;
                    //gravar os arquivos que faltam

                    for(int i= 0; i < M; i++) {
                        for (int j = 0; j < M; j++) {
                            //tem que ser difente, pois se for igual esta congelado
                            if (le[j] != NULL && le[j]->cod_cliente < menorcmp && le[j]->cod_cliente != 0 ) {
                                posvet = j;
                                menor->cod_cliente = le[j]->cod_cliente;
                                menorcmp = le[j]->cod_cliente;
                            }
                        }
                        if(le[posvet]->cod_cliente != 0) {
                            salva_cliente(le[posvet], write);
                            le[posvet]->cod_cliente = 0;
                        }
                    }


                }

            }
            if(contCongelado == 6){
                fclose(write);
                for(int i = 0; i < M; i++){
                   le[i] = aux[i];
                }

                char *nome_particao = proximo->nome;
                proximo = proximo->prox;
                write = fopen(nome_particao,"wb");
                if(write == NULL){
                    printf("\nErro ao abrir arquivo");
                    break;
                }
            }



        }
        fclose(write);
    }

    fclose(entrada);

}

void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n)
{
	//TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}


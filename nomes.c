//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 18/09/2021.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nomes.h"


char *cria_str(char *str)
{
	char *s = (char *) calloc(strlen(str) + 1, sizeof(char));
	strcpy(s, str);
	return s;
}

Nomes *cria_nomes(char *nome, Nomes *prox)
{
	Nomes *nomes = (Nomes *) malloc(sizeof(Nomes));
	nomes->nome = nome;
	nomes->prox = prox;
	return nomes;
}

void libera_nomes(Nomes *nomes)
{
	Nomes *temp = NULL;
	while(nomes) {
		temp = nomes->prox;
		free(nomes->nome);
		free(nomes);
		nomes = temp;
	}
}

int conta_nomes(Nomes *nomes)
{
	int qtd = 0;
	while(nomes) {
		qtd += 1;
		nomes = nomes->prox;
	}
	return qtd;
}

void inverte_nomes(Nomes *nomes)
{
	int i;
	int qtd = conta_nomes(nomes);
	Nomes *atual = nomes;
	Nomes **temp = (Nomes **) malloc(sizeof(Nomes *) * (qtd + 1));
	temp[qtd] = NULL;
	for (i = qtd - 1; i >= 0; i--) {
		temp[i] = atual;
		atual = atual->prox;
	}
	for (i = 0; i < qtd; i++) {
		temp[i]->prox = temp[i + 1];
	}
}

void imprime_nomes(Nomes *nomes)
{
	while(nomes) {
		printf("%s\n", nomes->nome);
		nomes = nomes->prox;
	}
}

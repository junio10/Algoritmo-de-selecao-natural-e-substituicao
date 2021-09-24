//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 18/09/2021.

#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>

#define TAM_NOME 100

typedef struct Cliente {
	int cod_cliente;
	char nome[TAM_NOME];
} Cliente;

// Imprime cliente
void imprime_cliente(Cliente *cliente);

// Cria cliente. Lembrar de usar free(cliente)
Cliente *cliente(int cod, char *nome);

// Salva cliente no arquivo out, na posicao atual do cursor
void salva_cliente(Cliente *cliente, FILE *out);

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente *le_cliente(FILE *in);

// Compara dois clientes
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_cliente(Cliente *c1, Cliente *c2);

// Retorna tamanho do cliente em bytes
int tamanho_cliente();

#endif
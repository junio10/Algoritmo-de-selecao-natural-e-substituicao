//
// Created by Vanessa Braganholo on 16/09/2018.
// Updated by Raphael Oliveira on 18/09/2021.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <io.h>
#define F_OK 0
#define ACCESS _access
#else
#include <unistd.h>
#define ACCESS access
#endif

#define AFTER_TEST after();
#define NOME_ARQUIVO_ENTRADA "entrada.dat"

#include <limits.h>
#include <stdlib.h>

#include "ufftest.h"
#include "cliente.h"
#include "lista_clientes.h"
#include "nomes.h"
#include "geracao_particoes.h"

Nomes *nomes = NULL;

void after()
{
	Nomes *atual = nomes;
	while (atual) {
		remove(atual->nome);
		atual = atual->prox;
	}
	libera_nomes(nomes);
	nomes = NULL;
}

int file_exist(char *filename)
{
	return (ACCESS(filename, F_OK) != -1);
}

BEGIN_TESTS();

/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A GERAÇÃO DE PARTIÇÃO POR CLASSIFICACAO INTERNA
 * *******************************************************************
 *********************************************************************/


TEST("Teste 1 Classificacao Interna. Arquivo vazio deve criar p1.dat vazio");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;

	entrada = cria_clientes(0);
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(0);
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}


TEST("Teste 2 Classificacao Interna. Arquivo com 2 registros ja ordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 3 Classificacao Interna. Arquivo com 2 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(5, "Maria"),
		cliente(1, "Joao"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 4 Classificacao Interna. Arquivo com 6 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(6,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(1, "Joao"),
		cliente(2, "Marcos"),
		cliente(5, "Maria"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"),
		cliente(10, "Mirtes"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	// ASSERT_FALSE(file_exist(p->nome))
	// p = p->prox;
}

TEST("Teste 5 Classificacao Interna. Arquivo com 9 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(9,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(20, "Mariana"),
		cliente(3, "Matheus"),
		cliente(87, "Jonas"),
		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(1, "Joao"),
		cliente(3, "Matheus"),
		cliente(5, "Maria"),
		cliente(10, "Mirtes"),
		cliente(20, "Mariana"),
		cliente(87, "Jonas"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(3,
		cliente(2, "Marcos"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 6 Classificacao Interna. Arquivo com 20 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(20,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(20, "Mariana"),
		cliente(3, "Matheus"),
		cliente(87, "Jonas"),

		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"),
		cliente(0, "Julia"),
		cliente(9, "Ana Maria"),
		cliente(81, "Bianca"),

		cliente(60, "Hugo"),
		cliente(47, "Martim"),
		cliente(23, "Clarissa"),
		cliente(22, "Lucila"),
		cliente(35, "Marceu"),
		cliente(48, "Tatiana"),

		cliente(90, "Catarina"),
		cliente(85, "Leonardo"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"),
		cria_nomes(cria_str("p2.dat"),
		cria_nomes(cria_str("p3.dat"),
		cria_nomes(cria_str("p4.dat"), NULL))));

	classificacao_interna(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(1, "Joao"),
		cliente(3, "Matheus"),
		cliente(5, "Maria"),
		cliente(10, "Mirtes"),
		cliente(20, "Mariana"),
		cliente(87, "Jonas"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(0, "Julia"),
		cliente(2, "Marcos"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"),
		cliente(9, "Ana Maria"),
		cliente(81, "Bianca"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(22, "Lucila"),
		cliente(23, "Clarissa"),
		cliente(35, "Marceu"),
		cliente(47, "Martim"),
		cliente(48, "Tatiana"),
		cliente(60, "Hugo"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(85, "Leonardo"),
		cliente(90, "Catarina"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A GERAÇÃO DE PARTIÇÃO POR SELECAO COM SUBSTITUICAO
 * *******************************************************************
 *********************************************************************/

TEST("Teste 1 Selecao com Substituicao. Arquivo vazio deve criar p1.dat vazio");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;

	entrada = cria_clientes(0);
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(0);
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 2 Selecao com Substituicao. Arquivo com 2 registros ja ordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 3 Selecao com Substituicao. Arquivo com 2 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(5, "Maria"),
		cliente(1, "Joao"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 4 Selecao com Substituicao. Arquivo com 6 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(6,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(1, "Joao"),
		cliente(2, "Marcos"),
		cliente(5, "Maria"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"),
		cliente(10, "Mirtes"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 5 Selecao com Substituicao. Arquivo com 54 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(54,
		cliente(29, "Maria"),
		cliente(14, "Joao"),
		cliente(76, "Mirtes"),
		cliente(75, "Mariana"),
		cliente(59, "Matheus"),
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(74, "Karla"),
		cliente(48, "Tatiana"),
		cliente(46, "Larissa"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(56, "Catarina"),
		cliente(20, "Leonel"),
		cliente(26, "Leo"),
		cliente(4, "Yasmin"),
		cliente(21, "Ana"),
		cliente(65, "Yoko"),
		cliente(22, "Mauricio"),
		cliente(49, "Jose"),
		cliente(11, "Alice"),
		cliente(16, "JC"),
		cliente(8, "TJ"),
		cliente(15, "Maira"),
		cliente(5, "Viviane"),
		cliente(19, "Fernanda"),
		cliente(50, "Daniel"),
		cliente(55, "Diego"),
		cliente(25, "Harry Potter"),
		cliente(66, "James Bond"),
		cliente(57, "Clark Kent"),
		cliente(77, "Lois Lane"),
		cliente(12, "Iris"),
		cliente(30, "Rosa"),
		cliente(17, "Helo"),
		cliente(9, "Joel"),
		cliente(54, "Carlos"),
		cliente(78, "Alex"),
		cliente(43, "Adriel"),
		cliente(38, "Ana Paula"),
		cliente(51, "Bia"),
		cliente(32, "Milton"),
		cliente(58, "Xande"),
		cliente(13, "Fausto"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"),
		cliente(27, "Alexandre"),
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(60, "Murilo"),
		cliente(36, "Rafael"),
		cliente(47, "Ricardo"),
		cliente(31, "Regiane"),
		cliente(80, "Fabio"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"),
		cria_nomes(cria_str("p2.dat"),
		cria_nomes(cria_str("p3.dat"),
		cria_nomes(cria_str("p4.dat"),
		cria_nomes(cria_str("p5.dat"), NULL)))));

	selecao_com_substituicao(NOME_ARQUIVO_ENTRADA, nomes, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(10,
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(14, "Joao"),
		cliente(29, "Maria"),
		cliente(46, "Larissa"),
		cliente(48, "Tatiana"),
		cliente(59, "Matheus"),
		cliente(74, "Karla"),
		cliente(75, "Mariana"),
		cliente(76, "Mirtes"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(10,
		cliente(4, "Yasmin"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(20, "Leonel"),
		cliente(21, "Ana"),
		cliente(22, "Mauricio"),
		cliente(26, "Leo"),
		cliente(49, "Jose"),
		cliente(56, "Catarina"),
		cliente(65, "Yoko"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(13,
		cliente(5, "Viviane"),
		cliente(8, "TJ"),
		cliente(11, "Alice"),
		cliente(15, "Maira"),
		cliente(16, "JC"),
		cliente(19, "Fernanda"),
		cliente(25, "Harry Potter"),
		cliente(50, "Daniel"),
		cliente(55, "Diego"),
		cliente(57, "Clark Kent"),
		cliente(66, "James Bond"),
		cliente(77, "Lois Lane"),
		cliente(78, "Alex"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(12,
		cliente(9, "Joel"),
		cliente(12, "Iris"),
		cliente(17, "Helo"),
		cliente(30, "Rosa"),
		cliente(32, "Milton"),
		cliente(38, "Ana Paula"),
		cliente(43, "Adriel"),
		cliente(51, "Bia"),
		cliente(54, "Carlos"),
		cliente(58, "Xande"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(9,
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(13, "Fausto"),
		cliente(27, "Alexandre"),
		cliente(31, "Regiane"),
		cliente(36, "Rafael"),
		cliente(47, "Ricardo"),
		cliente(60, "Murilo"),
		cliente(80, "Fabio"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A GERAÇÃO DE PARTIÇÃO POR SELECAO NATURAL
 * *******************************************************************
 *********************************************************************/

TEST("Teste 1 Selecao Natural. Arquivo vazio deve criar p1.dat vazio");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;

	entrada = cria_clientes(0);
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(0);
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 2 Selecao Natural. Arquivo com 2 registros ja ordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 3 Selecao Natural. Arquivo com 2 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(2,
		cliente(5, "Maria"),
		cliente(1, "Joao"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(2,
		cliente(1, "Joao"),
		cliente(5, "Maria"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 4 Selecao Natural. Arquivo com 6 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(6,
		cliente(5, "Maria"),
		cliente(1, "Joao"),
		cliente(10, "Mirtes"),
		cliente(8, "Vanessa"),
		cliente(7, "Bruna"),
		cliente(2, "Marcos"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"), NULL);

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(6,
		cliente(1, "Joao"),
		cliente(2, "Marcos"),
		cliente(5, "Maria"),
		cliente(7, "Bruna"),
		cliente(8, "Vanessa"),
		cliente(10, "Mirtes"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

TEST("Teste 5 Selecao Natural. Arquivo com 54 registros desordenados");
if (!skip) {
	ListaClientes *entrada, *oraculo, *saida;
	Nomes *p;
	entrada = cria_clientes(54,
		cliente(29, "Maria"),
		cliente(14, "Joao"),
		cliente(76, "Mirtes"),
		cliente(75, "Mariana"),
		cliente(59, "Matheus"),
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(74, "Karla"),
		cliente(48, "Tatiana"),
		cliente(46, "Larissa"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(56, "Catarina"),
		cliente(20, "Leonel"),
		cliente(26, "Leo"),
		cliente(4, "Yasmin"),
		cliente(21, "Ana"),
		cliente(65, "Yoko"),
		cliente(22, "Mauricio"),
		cliente(49, "Jose"),
		cliente(11, "Alice"),
		cliente(16, "JC"),
		cliente(8, "TJ"),
		cliente(15, "Maira"),
		cliente(5, "Viviane"),
		cliente(19, "Fernanda"),
		cliente(50, "Daniel"),
		cliente(55, "Diego"),
		cliente(25, "Harry Potter"),
		cliente(66, "James Bond"),
		cliente(57, "Clark Kent"),
		cliente(77, "Lois Lane"),
		cliente(12, "Iris"),
		cliente(30, "Rosa"),
		cliente(17, "Helo"),
		cliente(9, "Joel"),
		cliente(54, "Carlos"),
		cliente(78, "Alex"),
		cliente(43, "Adriel"),
		cliente(38, "Ana Paula"),
		cliente(51, "Bia"),
		cliente(32, "Milton"),
		cliente(58, "Xande"),
		cliente(13, "Fausto"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"),
		cliente(27, "Alexandre"),
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(60, "Murilo"),
		cliente(36, "Rafael"),
		cliente(47, "Ricardo"),
		cliente(31, "Regiane"),
		cliente(80, "Fabio"));
	salva_clientes(NOME_ARQUIVO_ENTRADA, entrada);
	libera_clientes(entrada);
	nomes = cria_nomes(cria_str("p1.dat"),
		cria_nomes(cria_str("p2.dat"),
		cria_nomes(cria_str("p3.dat"),
		cria_nomes(cria_str("p4.dat"),
		cria_nomes(cria_str("p5.dat"), NULL)))));

	selecao_natural(NOME_ARQUIVO_ENTRADA, nomes, 6, 6);

	p = nomes;
	saida = le_clientes(p->nome);
	oraculo = cria_clientes(11,
		cliente(6, "Jonas"),
		cliente(7, "Vanessa"),
		cliente(14, "Joao"),
		cliente(29, "Maria"),
		cliente(46, "Larissa"),
		cliente(48, "Tatiana"),
		cliente(56, "Catarina"),
		cliente(59, "Matheus"),
		cliente(74, "Karla"),
		cliente(75, "Mariana"),
		cliente(76, "Mirtes"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(9,
		cliente(4, "Yasmin"),
		cliente(10, "Marcela"),
		cliente(18, "Bruna"),
		cliente(20, "Leonel"),
		cliente(21, "Ana"),
		cliente(22, "Mauricio"),
		cliente(26, "Leo"),
		cliente(49, "Jose"),
		cliente(65, "Yoko"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(15,
		cliente(5, "Viviane"),
		cliente(8, "TJ"),
		cliente(11, "Alice"),
		cliente(15, "Maira"),
		cliente(16, "JC"),
		cliente(19, "Fernanda"),
		cliente(25, "Harry Potter"),
		cliente(30, "Rosa"),
		cliente(50, "Daniel"),
		cliente(54, "Carlos"),
		cliente(55, "Diego"),
		cliente(57, "Clark Kent"),
		cliente(66, "James Bond"),
		cliente(77, "Lois Lane"),
		cliente(78, "Alex"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(12,
		cliente(9, "Joel"),
		cliente(12, "Iris"),
		cliente(17, "Helo"),
		cliente(32, "Milton"),
		cliente(38, "Ana Paula"),
		cliente(43, "Adriel"),
		cliente(47, "Ricardo"),
		cliente(51, "Bia"),
		cliente(58, "Xande"),
		cliente(60, "Murilo"),
		cliente(73, "Sidney"),
		cliente(79, "Igor"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;

	saida = le_clientes(p->nome);
	oraculo = cria_clientes(7,
		cliente(1, "Aline"),
		cliente(3, "Andrea"),
		cliente(13, "Fausto"),
		cliente(27, "Alexandre"),
		cliente(31, "Regiane"),
		cliente(36, "Rafael"),
		cliente(80, "Fabio"));
	ASSERT_TRUE(file_exist(p->nome))
	ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
	libera_clientes(oraculo);
	libera_clientes(saida);
	p = p->prox;
}

END_TESTS();
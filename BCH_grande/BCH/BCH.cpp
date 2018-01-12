// BCH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#pragma warning	(disable: 4996)

//teste para BCH(7,4,1)
/*
#define m 3
#define n 6
#define k 3
#define n_extension 1 //numero de zeroas a acrescntar em n
#define t 1
int pol_gerador[n-k+1] = {1,1,0,1}; //g(x) = 1 + x + x^3
int pol_primitivo[m+1] = {1,1,0,1}; //g(x) = 1 + x + x^3
*/

//teste para BCH(15,7,2)
/*
#define m 4
#define n 13
#define k 5
#define n_extension 2 //numero de zeroas a acrescntar em n
#define t 2
int pol_gerador[n-k+1] = {1,0,0,0,1,0,1,1,1}; //g(x) = 1 + x^4 + x^6 + x^7 + x^8
int pol_primitivo[m+1] = {1,1,0,0,1}; //g(x) = 1 + x + x^4
*/

//teste para BCH(31,16,3)
/*
#define m 5
#define n 28
#define k 13
#define n_extension 3 //numero de zeroas a acrescntar em n
#define t 3
int pol_gerador[n-k+1] = {1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,1};
int pol_primitivo[m+1] = {1,0,1,0,0,1}; //g(x) = 1 + x^2 + x^5
*/

//BCH 10/15 short_frame (10800,10632,12) - 168 bits de paridade

#define m 14
#define n 10800 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir (2^14)-1 = 16383 amostras
#define k 10632	
#define n_extension 5583  //numero de zeroas a acrescntar em n
#define t 12

int pol_gerador[n-k+1] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
	0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(o do vitor está assim)
/*
int pol_gerador[n-k+1] = {1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,
	0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,1,0,0,1,1,0,1,0,0,0,1,1,0,0,1,0,0,1,
	1,0,1,1,0,0,1,0,1,1,0,0,0,0,1,1,0,0,1,0,1,0,1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1,0,1}; //(matlab está assim - ELE CODIFICA INVERTIDO MESMO)
*/
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,1,0,0,0,0,1,1}; // NAO RECONHECEU 					
int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,0,0,0,1}; // NAO RECONHECEU (MATLAB)
//int pol_primitivo[m+1] = {1,0,0,0,1,1,0,1,1,0,1,1,0,1,1}; // NAO RECONHECEU 					
//int pol_primitivo[m+1] = {1,1,0,1,1,0,1,1,0,1,1,0,0,0,1}; // NAO RECONHECEU 	
//int pol_primitivo[m+1] = {1,0,1,0,0,1,1,1,1,1,1,0,0,0,1}; // NAO RECONHECEU 					
//int pol_primitivo[m+1] = {1,0,0,0,1,1,1,1,1,1,0,0,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,0,1,0,1,0,0,0,0,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,1,0,0,0,0,0,1}; // NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,1,1,1,1,1,0,0,1,1,0,0,0,0,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,0,0,0,0,1,1,0,0,1,1,1,1,1,1}; // NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,1,0,0,1,0,1,1,0,1,1,1,1,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,1,1,1,1,0,1,1,1,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,1,0,0,0,0,1,0,0,0,0,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,0,1,0,0,1}; // NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,0,0,1,0,1,0,0,1,1,0,0,1,0,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,0,1,0,0,1,1,0,0,1,0,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,1,1,1,0,0,1,1,0,0,0,0,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,1,0,0,1,1,1,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,1,0,0,1,0,0,1,0,1,1,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,1,1,0,1,0,0,1,0,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,1,0,1,0,0,1,1,0,0,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,0,0,1,1,0,0,1,0,1,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,1,1,1,0,1,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,1,0,1,1,1,0,0,0,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,0,0,0,1,1,0,1,0,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,0,1,0,1,1,0,0,0,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,0,1,1,1,1,1,0,1,0,1,1}; // NAO RECONHECEU					
//int pol_primitivo[m+1] = {1,1,0,1,0,1,1,1,1,1,0,1,1,0,1}; // NAO RECONHECEU
//MEU TESTE
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,0,0,1,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,1,1,0,0,0,0,0,1,1,1,1}; // NAO RECONHECEU 		  
//int pol_primitivo[m+1] = {1,0,0,0,1,1,0,0,1,0,0,0,1,1,1}; // NAO RECONHECEU	   
//int pol_primitivo[m+1] = {1,0,0,1,0,0,1,0,1,0,0,0,0,0,1};	// NAO RECONHECEU   
//int pol_primitivo[m+1] = {1,0,0,1,1,1,1,0,0,1,0,0,0,0,1}; // NAO RECONHECEU  
//int pol_primitivo[m+1] = {1,0,1,0,1,0,1,1,0,0,1,0,0,0,1}; // NAO RECONHECEU 
//int pol_primitivo[m+1] = {1,0,1,1,0,0,0,0,0,0,1,0,0,0,1}; // NAO RECONHECEU	   
//int pol_primitivo[m+1] = {1,0,1,1,0,1,0,0,1,0,0,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,0,0,0,1,0,0,1}; // NAO RECONHECEU		   
//int pol_primitivo[m+1] = {1,1,0,0,1,0,1,1,1,1,0,1,1,1,1}; // NAO RECONHECEU		   
//int pol_primitivo[m+1] = {1,1,0,1,0,1,1,0,1,0,1,0,1,0,1}; // NAO RECONHECEU		   
//int pol_primitivo[m+1] = {1,1,0,1,1,0,0,1,1,1,0,0,1,0,1}; // NAO RECONHECEU
// MEU TESTE INVERTIDO
//int pol_primitivo[m+1] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,1,1,0,0,0,0,0,1,1,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,1,0,0,0,1,0,0,1,1,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,0,1,0,1,0,0,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,1,0,0,1,1,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,1,1,0,1,0,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,1,1,0,1}; // NAO RECONHECEU	   
//int pol_primitivo[m+1] = {1,0,0,1,0,0,1,0,0,1,0,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,1,0,0,0,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,1,1,0,1,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,0,1,0,1,0,1,1,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,0,0,1,1,1,0,0,1,1,0,1,1}; // NAO RECONHECEU

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade
/*
#define m 16
#define n 43200 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir (2^16)-1 = 65535 amostras
#define k 43008	
#define n_extension 22335  //numero de zeroas a acrescntar em n
#define t 12
int pol_gerador[n-k+1] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(norma)
//int pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1}; // NAO RECONHECEU
int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1}; // NAO RECONHECEU (MATLAB)
//int pol_primitivo[m+1] = {1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1};	// NAO RECONHECEU	
//int pol_primitivo[m+1] = {1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1};	// NAO RECONHECEU		
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1};	// NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1}; // NAO RECONHECEU
//int pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1};	// NAO RECONHECEU			
//int pol_primitivo[m+1] = {1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1}; // NAO RECONHECEU
*/

//VARIAVEIS AUXILIARES
int *GF; //campo de galois [potencias] = valor decimal
int *inv_GF; //campo de galois [valor decimal] = potencias
int aux_GF[2][m+1] = {0}; //auxiliar para calcular o valor decimal
int *tab_inv_alpha; //tabela inversa alpha
int *tab_inv_dec; //tabela inversa decimal
unsigned char *r; //palavra c�digo recebida
unsigned char *err; //vetor com as posi��es de erro
int sindrome[2*t+1] = {0}; //sindrome da palavra recebida

//DECODIFICADOR PETERSON (GAUSS)
int S[t][t+1] = {0}; //matriz s�ndrome
int LAMBDA[t+1] = {0}; //vetor lambda final
int aux_LAMBDA[t+1] = {0}; //vetor lambda final auxiliar
int lamb = 0; //lambda com alpha substituido
int inv_S_i_i; //inverso de S[i][i]
int n_err = t; //numero de erros
int pos_err[t] = {0}; //posi��o dos erros
int teste_erros[t] = {0}; //posi�ao dos erros a serem testados
unsigned char *aux_r; //auxiliar para calcular r no metodo de gauss
int pre_sindrome[2*t+1] = {0}; //pre-sindrome da palavra no metodo de gauss

int tab_mult(int multi1, int multi2);

int _tmain(int argc, _TCHAR* argv[])
{
	GF = new int[n+n_extension];
	inv_GF = new int[n+n_extension+1];
	tab_inv_alpha = new int[n+n_extension];
	tab_inv_dec = new int[n+n_extension];
	r = new unsigned char[n+n_extension]; 
	err = new unsigned char[n+n_extension]; 
	aux_r = new unsigned char[n+n_extension]; 

	//zerar variáveis

	memset (GF, 0, sizeof(GF[0])*(n+n_extension));
	memset (inv_GF, 0, sizeof(inv_GF[0])*(n+n_extension+1));
	memset (tab_inv_alpha, 0, sizeof(tab_inv_alpha[0])*(n+n_extension));
	memset (tab_inv_dec, 0, sizeof(tab_inv_dec[0])*(n+n_extension));
	memset (r, 0, sizeof(r[0])*(n+n_extension));
	memset (err, 0, sizeof(err[0])*(n+n_extension));
	memset (aux_r, 0, sizeof(aux_r[0])*(n+n_extension));

	clock_t setup = clock();

	// ------------------------------CAMPO DE GALOIS 2^m -----------------------------

	int index = m;

	for(int i = 0; i < n+n_extension; i++) // cada linha (potencia) do GF
	{
		for(int j = 0; j < m; j++) // zerar aux_GF
		{
			aux_GF[1][j] = aux_GF[0][j];
			aux_GF[0][j] = 0;
		}

		if(i < m)
			aux_GF[0][i] = 1;
		else if(i == m)
		{
			for(int j = 0; j < m; j++)
				aux_GF[0][j] = pol_primitivo[j];
		}
		else
		{
			for(int j = 0; j < m; j++)
				aux_GF[0][j+1] = aux_GF[1][j];

			if(aux_GF[0][m] == 1)
			{
				aux_GF[0][m] = 0;
				for(int j = 0; j < m; j++)
				{
					aux_GF[0][j] = aux_GF[0][j]^pol_primitivo[j];
				}
			}
		}

		for(int j = 0; j < m; j++)
		{
			if(aux_GF[0][j] == 1)
			{
				GF[i] += pow(2, j);
			}
		}

		inv_GF[GF[i]] = i;
	}         

	printf("BCH - CAMPO DE GALOIS OK\n");

	// ------------------------------TABELA INVERSA -----------------------------

	for(int i = 0; i <= (n+n_extension); i++)
	{
		for(int j = 0; j <= (n+n_extension); j++)
		{
			//if(tab_multi[i][j] == 1)
			if(tab_mult(i,j) == 1)
			{
				tab_inv_dec[i-1] = j; // tabela inversa decimal

				for(int l = 1; l < (n+n_extension)+1; l++)
				{
					if(GF[l] == i)
					{
						for(int L = 1; L < (n+n_extension)+1; L++)
						{
							if(GF[L] == j)
								tab_inv_alpha[l] = L;
						}
					}
				}
				break;
			}
		}
	}

	printf("BCH - TABELA INVERSA OK\n");

	clock_t codificador = clock();

	// ------------------------------CODIFICANDO u - DIVISAO POLINOMIAL -----------------------------

	int index_i = 0;

	unsigned char *v; //palavra c�digo enviada
	v = new unsigned char[n+n_extension]; 
	memset (v, 0, sizeof(r[0])*(n+n_extension));

	unsigned char *aux_v; //palavra c�digo enviada
	aux_v = new unsigned char[n+n_extension];
	memset (aux_v, 0, sizeof(r[0])*(n+n_extension));

	unsigned char *u; //mensagem enviada
	u = new unsigned char[k]; 
	memset (u, 0, sizeof(r[0])*(k));

	printf("");

	//escolhendo u
	/*
	for(int i = 0; i < k; i++)
	{
	if(i%2 == 0)
	u[i] = 1;
	}
	*/
	u[k-1] = 1;
	printf("");

	//codificando

	for(int i = 0; i < k; i++)
	{
		aux_v[n+n_extension-k+i] = u[i];
	}

	index = (sizeof(pol_gerador)/sizeof(pol_gerador[0])) - 1;

	printf ("");

	for(int j = (n+n_extension)-1; j >=0; j--) // encontrar o maior grau do dividendo
	{
		if(aux_v[j] > 0)
		{
			index_i = j;
			break;
		}
	}

	printf ("");

	while(index_i >= index)
	{
		// divisao em si

		for(int j = 0; j < (n-k+1); j++) // para cada elemento do pol_gerador 
		{
			aux_v[index_i-index+j] = aux_v[index_i-index+j]^pol_gerador[j];

			printf ("");
		}

		for(int j = (n+n_extension)-1; j >=0; j--) // encontrar o maior grau do polinomo a ser dividido
		{
			if(aux_v[j] == 1)
			{
				index_i = j;
				break;
			}
		}

	}

	for(int i = 0; i < (n+n_extension); i++)
	{
		v[i+k+n_extension] = aux_v[i];
	}

	for(int i = 0; i < k; i++)
	{
		v[i+n_extension] = v[i+n_extension]^u[i];
	}

	printf ("");

	//MENSAGEM GERADA PELO MATLAB (short)
	FILE *ff = fopen("in_decoder_bch.txt","r");

	for(int i = 0; i < n+n_extension; i++)
	{
		fscanf(ff, "%c", &v[i]);
		v[i] = v[i] - 48;
	}

	fclose(ff);

	// ------------------------------RECEBENDO r -----------------------------

	//memcpy(&r[0], &v[0], sizeof(v[0])*(n+n_extension)); //pequenos 

	for (int j = 0; j < (n+n_extension); j++) //grandes
	{
		r[n+n_extension-1-j] = v[j];
	}

	//adicionando erro 
	//r[0] = r[0]^1;
	//r[1] = r[1]^1;
	r[2] = r[2]^1;
	//r[3] = r[3]^1;
	//r[4] = r[4]^1;
	r[5] = r[5]^1;
	//r[6] = r[6]^1;
	//r[7] = r[7]^1;
	//r[8] = r[8]^1;
	//r[9] = r[9]^1;
	//r[10] = r[10]^1;
	//r[11] = r[11]^1;
	//r[12] = r[12]^1;
	r[13] = r[13]^1;

	//r[5465] = r[5465]^1; //erro em [4]
	//r[10926] = r[10926]^1; //erro em [4]
	
	//r[4091] = r[4091]^1; // erro em [4] e [10]

	r[563] = r[563]^1; // erro em [2] [5] [9] [13]
	//r[12940] = r[12940]^1; // erro em [2] [5] [9] [13]

	printf ("");

	FILE *F = fopen("vetores_BCH.txt", "w+");
	fprintf(F, "u = ");
	for (int j = 0; j < (n_extension); j++)
	{
		fprintf(F, " ");
	}
	for (int j = 0; j < (k); j++)
	{
		fprintf(F, "%i", u[j]);
	}
	fprintf(F, "\n");
	fprintf(F, "v = ");
	for (int j = 0; j < (n_extension); j++)
	{
		fprintf(F, " ");
	}
	for (int j = 0; j < (n); j++)
	{
		fprintf(F, "%i", v[j+n_extension]);
	}
	fprintf(F, "\n");
	fprintf(F, "r = ");
	for (int j = (n+n_extension-1); j >= 0; j--)
	{
		fprintf(F, "%i", r[j]);
	}
	fclose(F);
	printf("vetores_BCH OK\n");

	printf ("");

	clock_t decodificador = clock();

	int count = 0;

	// ------------------------------SINDROME BCH - METODO DE HORNER ------------------------------

	for(int i = 1; i < 2*t+1; i++)
	{
		for(int j = 0; j < (n+n_extension); j++)
		{
			sindrome[i] = sindrome[i]^(tab_mult(r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
			printf ("");
		}
		printf ("");
	}

	for(int i = 0; i < 2*t; i++)
	{
		sindrome[i] = sindrome[i+1];
	}
	sindrome[2*t] = 0;

	int aux_s = 1; //auxiliar para verificar sindromes

	for(int l = 0; l < 2*t+1; l++)
	{
		if(sindrome[l] == 0)
			aux_s = aux_s*1;
		else
			aux_s = 0;
	}
	/*
	for(int l = 0; l < 2*t+1; l++)
	{
	printf("%i ", sindrome[l]);
	}
	printf("\n");
	*/
	if(aux_s == 1)
	{
		printf("SINAL RECEBIDO OK\n"); // ------------ FIM ------------
		goto end;
	}

	printf("");

	// ------------------------------SINDROME BCH - CALCULO DO POLINOMIO LAMBDA - PETERSON (GAUSS) (https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/)------------------------------

	//calcular as matrizes S e C
	for(int i = 0; i < t; i++)
	{
		for(int j = 0; j < t; j++)
		{
			S[i][j] = sindrome[i+j];
		}

		S[i][t] = sindrome[i+t];
	}
	/*
	for(int i = 0; i < t; i++)
	{
	for(int j = 0; j < t; j++)
	{
	printf("%.5i ", S[i][j]);
	}
	printf("\n");
	}
	printf("\n");
	*/
	//----------------------------------------------------------------
	for(int i=0; i<t; i++) 
	{
		// Search for maximum in this column
		int maxEl = S[i][i];
		int maxRow = i;
		for (int j=i+1; j<t; j++) 
		{
			if (S[j][i] > maxEl) 
			{
				maxEl = S[j][i];
				maxRow = j;
			}
		}

		// Make all rows below this one 0 in current column
		for (int KK=i+1; KK<t; KK++) 
		{

			if(S[i][i] == 0)
				inv_S_i_i = 0;
			else
				inv_S_i_i = tab_inv_dec[S[i][i]-1];

			int c = tab_mult(S[KK][i],inv_S_i_i);
			for (int j=i; j<t+1; j++) 
			{
				if (i==j) 
					S[KK][j] = 0;
				else 
				{
					S[KK][j] = S[KK][j]^tab_mult(c,S[i][j]);
				}
			}
		}
		/*
		for(int i = 0; i < t; i++)
		{
		for(int j = 0; j < t; j++)
		{
		printf("%.5i ", S[i][j]);
		}
		printf("\n");
		}
		printf("\n");
		*/
	}

	// Solve equation Ax=b for an upper triangular matrix S
	for (int i=t-1; i>=0; i--) 
	{

		if(S[i][i] == 0)
			inv_S_i_i = 0;
		else
			inv_S_i_i = tab_inv_dec[S[i][i]-1];

		aux_LAMBDA[i] = tab_mult(S[i][t],inv_S_i_i);
		printf("");
		for (int j=i-1;j>=0; j--) 
		{
			S[j][t] = S[j][t] ^ tab_mult(S[j][i],aux_LAMBDA[i]);
			printf("");
		}

	}
	//----------------------------------------------------------------

	for(int i = 0; i <= t; i++)
	{
		LAMBDA[i] = aux_LAMBDA[t-i];
	}

	LAMBDA[0] = 1;
	// ------------------------------DECODIFICADOR BCH - ENCONTRAR POSI��O DOS ERROS - FORNEY ------------------------------

	count = 0;

	for(int i = 0; i < (n+n_extension); i++)
	{
		lamb = 0;
		for(int j = 0; j <= t; j++)
		{
			if(j == 0)
				lamb = LAMBDA[j];
			else
			{
				lamb = lamb^tab_mult(LAMBDA[j],GF[tab_inv_alpha[(i*j)%(n+n_extension)]]);
			}
		}

		if(lamb == 0)
		{
			err[i] = 1;

			pos_err[count] = i;
			count++;
		}
	}

	//o numero de erros � dado pelo numero de linhas n�o-nulas da matriz S.
	//se 1 > n_err > t, eu calculo todas as possibilidades de posi��o de erro at� a sindrome zerar que d� no m�ximo 924 tentativas para 6 de 12 bits de erro

	int gamb;

	//contar numero de erros
	for(int i = t-1; i >= 0; i--)
	{
		gamb = 0;
		for(int j = 0; j <= t; j++)
		{
			gamb = gamb + S[i][j];
		}

		if(gamb == 0)
		{
			n_err--;
		}
	}

	if(n_err < t)
	{
		//PR�-SINDROME (deixar calculadoas s�ndromes das posi�oes que est�o certas)

		memset (pre_sindrome,0, sizeof(pre_sindrome[0])*(2*t+1));

		int a = 0;

		for(int I = 1; I < 2*t+1; I++)
		{
			for(int j = 0; j < (n+n_extension); j++)
			{
				if(j != pos_err[a]) //ignorar posi�oes com erro
				{
					pre_sindrome[I] = pre_sindrome[I]^(tab_mult(aux_r[j],GF[(I*j)%(n+n_extension)])); //soma em binario
				}
				else 
				{
					a++;
				}
			}
			a = 0;
		}
		//permutar os erros
		int aux;
		for(int i = 0; i < pow(2, t); i++)
		{
again:
			count = 0;
			aux = i;
			for(int j = 0; j < t; j++)
			{
				if(aux%2 == 1)
				{
					teste_erros[j] = 1;
					count ++;
				}
				else
					teste_erros[j] = 0;

				if(count > n_err)//mais erros que n_err, nao preciso testar
				{
					i++;
					goto again;
				}

				aux = aux/2;
			}

			if(count < n_err)//menos erros que n_err, nao preciso testar
			{
				i++;
				goto again;
			}

			for(int ii = 0; ii < (n+n_extension); ii++)
			{
				aux_r[ii] = r[ii];
			}

			for(int ii = 0; ii < t; ii++)
			{
				if(teste_erros[ii] == 1)
					aux_r[pos_err[ii]] = aux_r[pos_err[ii]]^1;
			}

			//CALCULAR SINDROME (GAUSS)

			for(int I = 0; I < 2*t+1; I++)
			{
				sindrome[I] = pre_sindrome[I];
			}

			for(int I = 1; I < 2*t+1; I++)
			{
				for(int j = 0; j < n_err; j++)
				{
					sindrome[I] = sindrome[I]^(tab_mult(aux_r[pos_err[j]],GF[(I*pos_err[j])%(n+n_extension)])); //soma em binario
					printf("");
				}
			}

			for(int I = 0; I < 2*t; I++)
			{
				sindrome[I] = sindrome[I+1];
			}
			sindrome[2*t] = 0;

			int aux_s = 1; //auxiliar para verificar sindromes

			for(int l = 0; l < 2*t+1; l++)
			{
				if(sindrome[l] == 0)
					aux_s = aux_s*1;
				else
					aux_s = 0;
			}

			if(aux_s == 1)
			{
				for(int I = 0; I < (n+n_extension); I++)
				{
					r[I] = aux_r[I];
				}
				printf("%i ERROS, SINAL CORRIGIDO\n", n_err); // ------------ FIM ------------
				goto end;
			}
		}
	}
	else if (n_err == t)
	{

		memset (sindrome,0, sizeof(sindrome[0])*(2*t+1));

		for(int ii = 0; ii < (n+n_extension); ii++)
		{
			aux_r[ii] = r[ii];
		}

		for(int i = 0; i < t; i++)
		{
			aux_r[pos_err[i]] = aux_r[pos_err[i]]^1;
		}

		//SINDROME (GAUSS)

		for(int i = 1; i < 2*t+1; i++)
		{
			for(int j = 0; j < (n+n_extension); j++)
			{
				sindrome[i] = sindrome[i]^(tab_mult(aux_r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
			}
		}

		for(int i = 0; i < 2*t; i++)
		{
			sindrome[i] = sindrome[i+1];
		}
		sindrome[2*t] = 0;

		int aux_s = 1; //auxiliar para verificar sindromes

		for(int l = 0; l < 2*t+1; l++)
		{
			if(sindrome[l] == 0)
				aux_s = aux_s*1;
			else
				aux_s = 0;
		}

		if(aux_s == 1)
		{
			for(int I = 0; I < (n+n_extension); I++)
			{
				r[I] = aux_r[I];
			}
			printf("%i ERROS, SINAL CORRIGIDO\n", n_err); // ------------ FIM ------------
			goto end;
		}
		else
			printf("SINDROMES != 0, SINAL NAO CORRIGIDO\n"); // ------------ FIM ------------
	} 

end:
	printf ("\n");

	clock_t fim = clock();

	double tempo_setup = (codificador - setup);// /CLOCKS_PER_SEC*1000;
	double tempo_transmiss = (decodificador - codificador);// /CLOCKS_PER_SEC*1000;
	double tempo_decodif = (fim - decodificador);// /CLOCKS_PER_SEC*1000;

	printf ("\n\n");
	printf ("Setup = %.3lf ms\n", tempo_setup);
	printf ("Transmissao = %.3lf ms\n", tempo_transmiss);
	printf ("Decodificacao = %.3lf ms\n", tempo_decodif);
	printf ("\n");

	return 0;
}

int tab_mult(int multi1, int multi2)
{
	if((multi1 == 0)||(multi2 == 0))
		return 0;
	else
		return GF[(inv_GF[multi1]+inv_GF[multi2])%(n+n_extension)];

}
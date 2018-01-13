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
int A[t][t] = {0}; //matriz sindrome
int LAMBDA[t+1] = {0}; //vetor lambda final
int aux_LAMBDA[t+1] = {0}; //vetor lambda final auxiliar
int lamb = 0; //lambda com alpha substituido
int inv_S_i_i; //inverso de S[i][i]
int pos_err[t] = {-1}; //posi��o dos erros
int teste_erros[t] = {0}; //posi�ao dos erros a serem testados
unsigned char *aux_r; //auxiliar para calcular r no metodo de gauss
int pre_sindrome[2*t+1] = {0}; //pre-sindrome da palavra no metodo de gauss

int tab_mult(int multi1, int multi2);
int det_gf(int **MAT, int size);
int det(int **MAT, int size);

int _tmain(int argc, _TCHAR* argv[])
{
	GF = new int[n+n_extension];
	inv_GF = new int[n+n_extension+1];
	tab_inv_alpha = new int[n+n_extension];
	tab_inv_dec = new int[n+n_extension+1];
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

	for(int i = 0; i <= (n+n_extension+1); i++)
	{
		for(int j = 0; j <= (n+n_extension); j++)
		{
			//if(tab_multi[i][j] == 1)
			if(tab_mult(i,j) == 1)
			{
				tab_inv_dec[i] = j; // tabela inversa decimal

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
	//r[2] = r[2]^1;
	//r[3] = r[3]^1;
	r[4] = r[4]^1;
	//r[5] = r[5]^1;
	//r[6] = r[6]^1;
	r[7] = r[7]^1;
	//r[8] = r[8]^1;
	//r[9] = r[9]^1;
	r[10] = r[10]^1;
	//r[11] = r[11]^1;
	r[12] = r[12]^1;
	//r[13] = r[13]^1;

	//r[5465] = r[5465]^1; //erro em [4]
	//r[10926] = r[10926]^1; //erro em [4]

	//r[4091] = r[4091]^1; // erro em [4] e [10]

	//r[563] = r[563]^1; // erro em [2] [5] [9] [13]
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

	if(aux_s == 1)
	{
		printf("SINAL RECEBIDO OK\n"); // ------------ FIM ------------
		goto end;
	}

	printf("");

	// ------------------------------SINDROME BCH - CALCULO DO POLINOMIO LAMBDA - PETERSON (https://www.ece.uvic.ca/~agullive/decodingbch405-511-2016.pdf) - (GAUSS) (https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/) ------------------------------

	int A_size = t;

	for(int i = 0; i < A_size; i++)
	{
		for(int j = 0; j < A_size; j++)
		{
			A[i][j] = 0;
		}
	}

	//calcular matriz A
	A[0][0] = 1;
	for(int i = 1; i < A_size; i++)
	{
		for(int j = 0; j < A_size; j++)
		{
			if(((i*2)-1-j) == -1)
				A[i][j] = 1;
			else if(((i*2)-1-j) < -1)
				A[i][j] = 0;
			else
				A[i][j] = sindrome[(i*2)-1-j];
		}
	}
	printf("");

	//-----------------------------------------------------------------  descobrir numero de erros

	int SS[t][t+1];

	for(int i = 0; i < t; i++)
	{
		for(int j = 0; j < t; j++)
		{
			SS[i][j] = sindrome[i+j];
		}

		SS[i][t] = sindrome[i+t];
	}

	for (int i = 0; i < t; i++) 
	{

		printf("");

		// Search for maximum in this column
		int maxEl = SS[i][i];
		int maxRow = i;
		for (int kk = i+1; kk < t; kk++)
		{
			if (abs(SS[kk][i]) > maxEl) 
			{
				maxEl = SS[kk][i];
				maxRow = kk;
			}
		}

		printf("");

		// Swap maximum row with current row (column by column)
		for (int kk = i; kk < t+1; kk++) 
		{
			int tmp = SS[maxRow][kk];
			SS[maxRow][kk] = SS[i][kk];
			SS[i][kk] = tmp;
		}

		printf("");

		// Make all rows below this one 0 in current column
		for (int kk = i+1; kk < t; kk++) 
		{
			int c = tab_mult(SS[kk][i], tab_inv_dec[SS[i][i]]); //c = -SS[kk][i]/SS[i][i]
			printf("");
			for (int j = i; j < t+1; j++) 
			{
				if (i==j) 
				{
					SS[kk][j] = 0;
				} 
				else 
				{
					SS[kk][j] = SS[kk][j] ^ tab_mult(c, SS[i][j]);
				}
			}
		}
	}

	//o numero de erros é dado pelo numero de linhas n�o-nulas da matriz SS.

	int aux;

	//contar numero de erros
	for(int i = t-1; i >= 0; i--)
	{
		aux = 0;
		for(int j = 0; j <= t; j++)
		{
			aux = aux + SS[i][j];
		}

		if(aux == 0)
		{
			A_size--;
		}
	}

	printf("");

	//---------------------------------------------------------------- RESOLVER AS EQUAÇÕES (GAUSS)

	//calcular a matriz S

	for(int i = 0; i < A_size; i++)
	{
		for(int j = 0; j < A_size; j++)
		{
			S[i][j] = A[i][j];
		}

		S[i][t] = sindrome[2*i];
	}

	printf("");

	for (int i = 0; i < t; i++) 
	{

		printf("");

		// Search for maximum in this column
		int maxEl = S[i][i];
		int maxRow = i;
		for (int kk = i+1; kk < t; kk++)
		{
			if (abs(S[kk][i]) > maxEl) 
			{
				maxEl = S[kk][i];
				maxRow = kk;
			}
		}

		printf("");

		// Swap maximum row with current row (column by column)
		for (int kk = i; kk < t+1; kk++) 
		{
			int tmp = S[maxRow][kk];
			S[maxRow][kk] = S[i][kk];
			S[i][kk] = tmp;
		}

		printf("");

		// Make all rows below this one 0 in current column
		for (int kk = i+1; kk < t; kk++) 
		{
			int c = tab_mult(S[kk][i], tab_inv_dec[S[i][i]]); //c = -S[kk][i]/S[i][i]
			printf("");
			for (int j = i; j < t+1; j++) 
			{
				if (i==j) 
				{
					S[kk][j] = 0;
				} 
				else 
				{
					S[kk][j] = S[kk][j] ^ tab_mult(c, S[i][j]);
				}
			}
		}
	}

	printf("");

	// Solve equation Ax=b for an upper triangular matrix A
	for (int i = A_size-1; i >= 0; i--) 
	{
		LAMBDA[i] = tab_mult(S[i][t], tab_inv_dec[S[i][i]]); //LAMBDA[i] = S[i][n]/S[i][i]
		printf("");
		for (int kk = i-1; kk >= 0; kk--) 
		{
			S[kk][t] = S[kk][t] ^ tab_mult(S[kk][i], LAMBDA[i]);
			printf("");
		}
	}

	printf("");

	//----------------------------------------------------------------
	
	for(int i = t; i > 0; i--)
	{
		LAMBDA[i] = LAMBDA[i-1];
	}

	LAMBDA[0] = 1;


	printf("");
	
	// ------------------------------DECODIFICADOR BCH - ENCONTRAR POSI��O DOS ERROS - FORNEY ------------------------------

	count = 0;

	for(int i = 0; i < t; i++)
		pos_err[i] = -1;

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

	printf("");


	for(int ii = 0; ii < (n+n_extension); ii++)
	{
		aux_r[ii] = r[ii];
	}

	for(int ii = 0; ii < t; ii++)
	{
		if(pos_err[ii] >= 0)
			aux_r[pos_err[ii]] = aux_r[pos_err[ii]]^1;
	}

	printf ("");

	//zerar sindrome

	for(int i = 0; i < 2*t+1; i++)
	{
		sindrome[i] = 0;
	}

	printf ("");

	//CALCULAR SINDROME (GAUSS)

	for(int i = 1; i < 2*t+1; i++)
	{
		for(int j = 0; j < (n+n_extension); j++)
		{
			sindrome[i] = sindrome[i]^(tab_mult(aux_r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
			printf ("");
		}
		printf ("");
	}

	for(int i = 0; i < 2*t; i++)
	{
		sindrome[i] = sindrome[i+1];
	}
	sindrome[2*t] = 0;

	aux_s = 1; //auxiliar para verificar sindromes

	for(int l = 0; l < 2*t+1; l++)
	{
		if(sindrome[l] == 0)
			aux_s = aux_s*1;
		else
			aux_s = 0;
	}

	for(int I = 0; I < (n+n_extension); I++)
	{
		r[I] = aux_r[I];
	}

	if(aux_s == 1)
	{
		printf("%i ERROS, SINAL CORRIGIDO\n", A_size); // ------------ FIM ------------
		goto end;
	}
	else
		printf("SINDROMES != 0, SINAL NAO CORRIGIDO\n"); // ------------ FIM ------------

end:

	F = fopen("vetores_BCH.txt", "a+");
	fprintf(F, "\n");
	fprintf(F, "c = ");
	for (int j = (n+n_extension-1); j >= 0; j--)
	{
		fprintf(F, "%i", r[j]);
	}
	fclose(F);
	printf("vetores_BCH_end OK\n");
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

int det_gf(int **MAT, int size)
{
	int deter = 0;
	if(size == 1)
	{
		deter = MAT[0][0]; //determinante 1x1
	}
	else if(size == 2)
	{
		deter = tab_mult(MAT[0][0], MAT[1][1]) ^ tab_mult(MAT[1][0], MAT[0][1]); //determinante 2x2
	}
	else
	{
		int a = 0;

		int **mat = new int*[size-1];
		for(int i = 0; i < (size-1); i++)
			mat[i] = new int[size-1];

		for(int ii = 0; ii < size; ii++) //elementos da 1a linha da matriz
		{
			//criar matriz menor
			for(int j = 0; j < size-1; j++) //cada linha 
			{
				a = 0;
				for(int i = 0; i < size; i++) //cada coluna
				{
					if (i == ii)
						a = 1;
					mat[j][i] = MAT[j][i+a];
				}
			}

			//calcular determinante 
			deter = deter ^ tab_mult(MAT[size-1][ii], det_gf(mat,size-1)); //parcela do determinante
		}

		for (int i = 0; i < size-1; ++i)
			delete [] mat[i];
		delete [] mat;
	}
	return deter;
}

int det(int **MAT, int size)
{
	int deter = 0;
	if(size == 1)
	{
		deter = MAT[0][0]; //determinante 1x1
	}
	else if(size == 2)
	{
		deter = (MAT[0][0] * MAT[1][1]) - (MAT[1][0] * MAT[0][1]); //determinante 2x2
	}
	else
	{
		int a = 0;

		int **mat = new int*[size-1];
		for(int i = 0; i < (size-1); i++)
			mat[i] = new int[size-1];

		for(int ii = 0; ii < size; ii++) //elementos da 1a linha da matriz
		{
			//criar matriz menor
			for(int j = 0; j < size-1; j++) //cada linha 
			{
				a = 0;
				for(int i = 0; i < size; i++) //cada coluna
				{
					if (i == ii)
						a = 1;
					mat[j][i] = MAT[j][i+a];
				}
			}

			//calcular determinante
			deter = deter + pow(-1, ii+size)*MAT[size-1][ii]*det(mat,size-1); //parcela do determinante
		}

		for (int i = 0; i < size-1; ++i)
			delete [] mat[i];
		delete [] mat;
	}
	return deter;
}
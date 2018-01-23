// BCH.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bch.h"
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
/*
unsigned char pol_gerador[n-k+1] = {1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,1,
	0,0,1,0,0,1,1,0,0,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,0,0,0,
	1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1}; //(o do victor está assim)
			
unsigned char pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,0,0,0,1}; // (MATLAB)
*/

//BCH 10/15 normal_frame (43200,43008,12) - 192 bits de paridade

#define m 16
#define n 43200 //acrescentar n_extension zeros no come�o do vetor recebido ate atingir (2^16)-1 = 65535 amostras
#define k 43008	
#define n_extension 22335  //numero de zeroas a acrescntar em n
#define t 12
unsigned char pol_gerador[n-k+1] = {1,0,1,0,0,1,1,1,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1,
0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,
1,1,1,0,0,1,1,1}; //(norma, victor)
//unsigned char pol_primitivo[m+1] = {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1};// NAO RECONHECEU (MATLAB)
//unsigned char pol_primitivo[m+1] = {1,0,0,1,1,1,0,0,0,1,1,0,0,1,0,1,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,1,0,0,1,1,0,0,0,1,1,1,0,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,1,1};// NAO RECONHECEU		
//unsigned char pol_primitivo[m+1] = {1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,0,0,1,0,0,0,1,1,1};// NAO RECONHECEU	
//unsigned char pol_primitivo[m+1] = {1,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,1};// NAO RECONHECEU		
//unsigned char pol_primitivo[m+1] = {1,1,1,0,1,0,1,0,1,1,1,1,0,0,0,1,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,0,0,1,1,0,0,1,1,1,0,1,1,1,1};// NAO RECONHECEU		
//unsigned char pol_primitivo[m+1] = {1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,1,1,1,0,1,1,1,1,0,0,0,0,0,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1};// NAO RECONHECEU			
//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,1};// NAO RECONHECEU			
//unsigned char pol_primitivo[m+1] = {1,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,0,1,1,1,0,0,0,0,0,1,1,0,1,1,0,1};// NAO RECONHECEU			
//unsigned char pol_primitivo[m+1] = {1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1};// NAO RECONHECEU
//unsigned char pol_primitivo[m+1] = {1,1,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1};// NAO RECONHECEU			
//unsigned char pol_primitivo[m+1] = {1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1};// NAO RECONHECEU
  unsigned char pol_primitivo[m+1] = {1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1};


//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,1,1,1,0,1,0,1,0,0,0,0,1};
//unsigned char pol_primitivo[m+1] = {1,1,0,1,0,1,1,1,1,0,1,1,0,0,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,1,1,1,1,0,1,1,1,1,0,1,1,0,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,1,1,1,0,1,0,0,0,1,0,1,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,0,1,1,0,1,0,1,1,1,0,0,0,1,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,0,0,0,0,0,1,0,1,1,1,0,0,1,1};
//unsigned char pol_primitivo[m+1] = {1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,1};
//unsigned char pol_primitivo[m+1] = {1,0,1,1,1,0,0,1,1,0,1,1,0,0,1,1,1};
//unsigned char pol_primitivo[m+1] = {1,0,0,0,1,1,1,1,1,0,0,1,0,1,1,1,1};




int _tmain(int argc, _TCHAR* argv[])
{
	int n_err;

	bch teste;

	teste.init(n, k, t, m);

	teste.set_pol_prim(pol_primitivo);

	teste.set_pol_ger(pol_gerador);

	teste.calc_gf();

	teste.calc_tab_inv();

	unsigned char uu[k];
	unsigned char vv[n];
	unsigned char rr[n];

	for(int i = 0; i < k; i++)
	{
		uu[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		vv[i] = 0;
	}

	uu[k-1] = 1;

	//teste.encode(uu, vv);

	//MENSAGEM GERADA PELO MATLAB
	//FILE *fff = fopen("in_decoder_bch_short.txt","r");
	//FILE *fff = fopen("in_decoder_bch_normal.txt","r");
	FILE *fff = fopen("in_decoder_bch_normal_victor.txt","r");

	for(int i = 0; i < n_extension; i++)
	{
		fscanf(fff, "%c", &vv[i]);
	}
	
	for(int i = 0; i < n; i++)
	{
		fscanf(fff, "%c", &vv[i]);
		vv[i] = vv[i] - 48;
	}

	fclose(fff);

	for (int j = 0; j < (n); j++) //o matlab codifica ao contrario
	{
		rr[n-1-j] = vv[j];
	}

	printf("");

	//adicionando erro 
	//rr[0] = rr[0]^1;
	//rr[1] = rr[1]^1;
	//rr[2] = rr[2]^1;
	//rr[3] = rr[3]^1;
	rr[4] = rr[4]^1;
	//rr[5] = rr[5]^1;
	//rr[6] = rr[6]^1;
	rr[7] = rr[7]^1;
	//rr[8] = rr[8]^1;
	//rr[9] = rr[9]^1;
	rr[10] = rr[10]^1;
	//rr[11] = rr[11]^1;
	rr[12] = rr[12]^1;
	//rr[13] = rr[13]^1;

	printf ("");

	FILE *FF = fopen("teste_lib_BCH.txt", "w+");
	fprintf(FF, "u = ");
	for (int j = 0; j < (k); j++)
	{
		fprintf(FF, "%i", uu[j]);
	}
	fprintf(FF, "\n");
	fprintf(FF, "v = ");
	for (int j = 0; j < (n); j++)
	{
		fprintf(FF, "%i", vv[j]);
	}
	fprintf(FF, "\n");
	fprintf(FF, "r = ");
	for (int j = (n-1); j >= 0; j--)
	{
		fprintf(FF, "%i", rr[j]);
	}
	fclose(FF);
	printf("teste_lib_BCH OK\n");

	printf ("");


	teste.decode(rr, n_err);


	FF = fopen("teste_lib_BCH.txt", "a+");
	fprintf(FF, "\n");
	fprintf(FF, "c = ");
	for (int j = (n-1); j >= 0; j--)
	{
		fprintf(FF, "%i", rr[j]);
	}
	fclose(FF);
	printf("teste_lib_BCH_end OK\n");
	printf ("\n");

	printf("");

	return 0;
}

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include "bch.h"

using namespace std;

int bch::tab_mult(int multi1, int multi2)
{
	if((multi1 == 0)||(multi2 == 0))
		return 0;
	else
		return GF[(inv_GF[multi1]+inv_GF[multi2])%(n+n_extension)];

}

int bch::det_gf(int **MAT, int size)
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

int bch::det(int **MAT, int size)
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

void bch::init(int N, int K, int T, int M) 
{
	n = N;
	k = K;
	t = T;
	m = M;

	n_extension = pow(2, m) - 1 - n;

	printf("");
}

void bch::set_pol_prim(unsigned char *p_prim)
{
	pol_primitivo = p_prim;
}

void bch::set_pol_ger(unsigned char *p_ger)
{
	pol_gerador = p_ger;
}

void bch::calc_gf() 
{
	int index = m;

	GF = new int[n+n_extension];
	memset (GF, 0, sizeof(GF[0])*(n+n_extension));

	inv_GF = new int[n+n_extension+1];
	memset (inv_GF, 0, sizeof(inv_GF[0])*(n+n_extension+1));

	int **aux_GF = new int*[2]; //auxiliar para calcular o valor decimal
	for(int i = 0; i < (2); i++)
		aux_GF[i] = new int[m+1];

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

	for (int i = 0; i < 2; ++i)
		delete [] aux_GF[i];
	delete [] aux_GF;

	printf("BCH - CAMPO DE GALOIS OK\n");
}

void bch::calc_tab_inv()
{
	tab_inv_alpha = new int[n+n_extension];
	tab_inv_dec = new int[n+n_extension+1];

	for(int i = 0; i < n+n_extension; i++)
	{
		tab_inv_alpha[i] = 0;
		tab_inv_dec[i] = 0;
	}
	tab_inv_dec[n+n_extension] = 0;

	for(int i = 0; i < (n+n_extension+1); i++)
	{
		for(int j = 0; j <= (n+n_extension); j++)
		{
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
}

void bch::encode(unsigned char *u, unsigned char *v)
{
	int index_i = 0, index;

	unsigned char *aux_v; //v invertido
	aux_v = new unsigned char[n+n_extension];

	for(int i = 0; i < n+n_extension; i++)
		aux_v[i] = 0;

	for(int i = 0; i < sizeof(v)/sizeof(v[0]); i++)
	{
		v[i] = 0;
	}

	//codificando

	for(int i = 0; i < k; i++)
	{
		aux_v[n+n_extension-k+i] = u[i];
	}

	index = n-k;

	for(int j = (n+n_extension)-1; j >=0; j--) // encontrar o maior grau do dividendo
	{
		if(aux_v[j] > 0)
		{
			index_i = j;
			break;
		}
	}

	while(index_i >= index)
	{
		// divisao em si

		for(int j = 0; j < (n-k+1); j++) // para cada elemento do pol_gerador 
		{
			aux_v[index_i-index+j] = aux_v[index_i-index+j]^pol_gerador[j];
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
}

bool bch::decode(unsigned char *rr, int &n_err)
{
	int *r;
	r = new int[n+n_extension]; //r a ser processado

	int *pos_err;
	pos_err = new int[t]; //posições dos erros

	int *sindrome;
	sindrome = new int[2*t+1]; //sindrome da palavra recebida

	int **S = new int*[t]; //matriz sindrome (https://en.wikipedia.org/wiki/BCH_code#Peterson%E2%80%93Gorenstein%E2%80%93Zierler_algorithm)
	for(int i = 0; i < t; i++)
		S[i] = new int[t+1];

	int **A = new int*[t]; //matriz sindrome (https://www.ece.uvic.ca/~agullive/decodingbch405-511-2016.pdf)
	for(int i = 0; i < t; i++)
		A[i] = new int[t];

	int *LAMBDA; //vetor lambda
	LAMBDA = new int[t+1]; 

	int lamb = 0; //lambda com alpha substituido
	int inv_S_i_i; //inverso de S[i][i]

	unsigned char *aux_r; //auxiliar para calcular r no metodo de gauss
	aux_r = new unsigned char[n+n_extension]; 

	unsigned char *err; //vetor de erros
	err = new unsigned char[n+n_extension]; 

	//setar variáveis

	for(int i = 0; i < n_extension; i++)
		r[i] = 0;

	for(int i = n_extension; i < n+n_extension; i++)
		r[i] = rr[i-n_extension];

	for(int i = 0; i < (2*t+1); i++)
		sindrome[i] = 0;

	for(int i = 0; i < (t+1); i++)
		LAMBDA[i] = 0;

	for(int i = 0; i < t; i++)
		pos_err[i] = -1;

	for(int i = 0; i < t; i++)

	{
		for(int j = 0; j < t; j++)
		{
			A[i][j] = 0;
			S[i][j] = 0;
		}
		S[i][t] = 0;
	}

	// ------------------------------SINDROME BCH - METODO DE HORNER ------------------------------

	for(int i = 1; i < 2*t+1; i++)
	{
		for(int j = 0; j < (n+n_extension); j++)
		{
			sindrome[i] = sindrome[i]^(tab_mult(r[j],GF[(i*j)%(n+n_extension)])); //soma em binario
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
		printf("SINAL RECEBIDO OK\n"); // ------------ FIM ------------

		delete [] sindrome;

		for (int i = 0; i < t; ++i)
			delete [] S[i];
		delete [] S;

		for (int i = 0; i < t; ++i)
			delete [] A[i];
		delete [] A;

		delete [] LAMBDA;

		delete [] aux_r;

		delete [] err;

		for(int i = 0; i < n; i++)
			rr[i] = r[i+n_extension];

		n_err = 0;

		return true;
	}

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

	//-----------------------------------------------------------------  descobrir numero de erros

	int **SS = new int*[t]; //matriz sindrome (https://en.wikipedia.org/wiki/BCH_code#Peterson%E2%80%93Gorenstein%E2%80%93Zierler_algorithm)
	for(int i = 0; i < t; i++)
		SS[i] = new int[t+1];

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

		// Swap maximum row with current row (column by column)
		for (int kk = i; kk < t+1; kk++) 
		{
			int tmp = SS[maxRow][kk];
			SS[maxRow][kk] = SS[i][kk];
			SS[i][kk] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int kk = i+1; kk < t; kk++) 
		{
			int c = tab_mult(SS[kk][i], tab_inv_dec[SS[i][i]]); //c = -SS[kk][i]/SS[i][i]
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


	for (int i = 0; i < t; ++i)
		delete [] SS[i];
	delete [] SS;

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

	for (int i = 0; i < t; i++) 
	{
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

		// Swap maximum row with current row (column by column)
		for (int kk = i; kk < t+1; kk++) 
		{
			int tmp = S[maxRow][kk];
			S[maxRow][kk] = S[i][kk];
			S[i][kk] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int kk = i+1; kk < t; kk++) 
		{
			int c = tab_mult(S[kk][i], tab_inv_dec[S[i][i]]); //c = -S[kk][i]/S[i][i]
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

	// Solve equation Ax=b for an upper triangular matrix A
	for (int i = A_size-1; i >= 0; i--) 
	{
		LAMBDA[i] = tab_mult(S[i][t], tab_inv_dec[S[i][i]]); //LAMBDA[i] = S[i][n]/S[i][i]
		for (int kk = i-1; kk >= 0; kk--) 
		{
			S[kk][t] = S[kk][t] ^ tab_mult(S[kk][i], LAMBDA[i]);
		}
	}

	//----------------------------------------------------------------

	for(int i = t; i > 0; i--)
	{
		LAMBDA[i] = LAMBDA[i-1];
	}

	LAMBDA[0] = 1;

	// ------------------------------DECODIFICADOR BCH - ENCONTRAR POSI��O DOS ERROS - FORNEY ------------------------------

	int count = 0;

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


	for(int ii = 0; ii < (n+n_extension); ii++)
	{
		aux_r[ii] = r[ii];
	}

	for(int ii = 0; ii < t; ii++)
	{
		if(pos_err[ii] >= 0)
			aux_r[pos_err[ii]] = aux_r[pos_err[ii]]^1;
	}

	//zerar sindrome

	for(int i = 0; i < 2*t+1; i++)
	{
		sindrome[i] = 0;
	}


	//CALCULAR SINDROME (GAUSS)

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

		delete [] sindrome;

		for (int i = 0; i < t; ++i)
			delete [] S[i];
		delete [] S;

		for (int i = 0; i < t; ++i)
			delete [] A[i];
		delete [] A;

		delete [] LAMBDA;

		delete [] aux_r;

		delete [] err;

		for(int i = 0; i < n; i++)
			rr[i] = r[i+n_extension];

		for(int i = 0; i < t; i++)
		{
			if(pos_err[i] >= 0)
				pos_err[i] = pos_err[i]-n_extension;
		}

		n_err = A_size;

		return true;
	}
	else
	{
		printf("SINDROMES != 0, SINAL NAO CORRIGIDO\n"); // ------------ FIM ------------

		delete [] sindrome;

		for (int i = 0; i < t; ++i)
			delete [] S[i];
		delete [] S;

		for (int i = 0; i < t; ++i)
			delete [] A[i];
		delete [] A;

		delete [] LAMBDA;

		delete [] aux_r;

		delete [] err;

		return false;
	}

}
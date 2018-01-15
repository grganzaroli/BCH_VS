#ifndef BCH_H
#define BCH_H

class bch
{
private:
	int n; //quantidade de bits de entrada
	int k; //quantidade de bits de saída
	int t; //capacidade de correção de erros
	int m; //ordem do decodificador
	int n_extension; //numero de zeros a adicionar ao inicio da palavra-codigo recebida para obter n+n_extension = (2^m)-1
	unsigned char *pol_primitivo; //polinomio primitivo
	unsigned char *pol_gerador; //polinomio gerador

	int *GF; //campo de galois [potencias] = valor decimal
	int *inv_GF; //campo de galois [valor decimal] = potencias
	int *tab_inv_alpha; //tabela inversa alpha
	int *tab_inv_dec; //tabela inversa decimal

	int *p_erros; //posicao dos erros

public:
	void init(int n, int k, int t, int m); //inicializa variavais
	void set_pol_prim(unsigned char *p_prim); //polinomio primitivo para decodificação
	void set_pol_ger(unsigned char *p_ger); //polinomio gerador para codificação
	void calc_gf(); // calculo do campo de galois
	void calc_tab_inv(); // calculo da tabela inversa

	void encode(unsigned char *u, unsigned char *v); // codifica u[k] em v[n+n_extension] (nao funciona direito)
	bool decode(unsigned char *rr, int &n_err); //decodifica [r] e retorna sucessso (true) ou fracasso (false) na decodificação

	int tab_mult(int multi1, int multi2);
	int det_gf(int **MAT, int size);
	int det(int **MAT, int size);
};

#endif

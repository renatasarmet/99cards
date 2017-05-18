#ifndef PILHA_BURRA_H
#define PILHA_BURRA_H

#include "cartas.h"
#define QUANT_CARTAS 99

class pilha_burra: public cartas{
public:
	//CONSTRUTOR
	pilha_burra();

	//DESTRUTOR
	~pilha_burra();

	//FUNCOES
	bool Vazia() const;
	bool Cheia() const;
	void Empilha(int, bool &);
	void Desempilha(int &, bool &);
	void aumenta_topo();
	void diminui_topo();
	int get_topo() const;
	void set_topo(int);
	void set_elemento_topo(int);
	int get_elemento_topo() const;

private:
	int Elementos[QUANT_CARTAS];
	int topo;
};
#endif // PILHABURRA_H
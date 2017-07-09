#ifndef PILHA_CRESCENTE_H
#define PILHA_CRESCENTE_H
#include <iostream>
#include "pilha_burra.h"

using namespace std;

class pilha_crescente : public pilha_burra{
public:
	//CONSTRUTOR
	pilha_crescente();

	//DESTRUTOR
	~pilha_crescente();

	//FUNCOES
	void Empilha(int, bool &);
};
#endif //PILHACRESCENTE_H
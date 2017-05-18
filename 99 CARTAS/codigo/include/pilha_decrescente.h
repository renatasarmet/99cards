#ifndef PILHA_DECRESCENTE_H
#define PILHA_DECRESCENTE_H

#include <iostream>
#include "pilha_burra.h"
using namespace std;

class pilha_decrescente : public pilha_burra {

public:
	//CONSTRUTOR
	pilha_decrescente();

	//DESTRUTOR
	~pilha_decrescente();

	//FUNÇOES
	void Empilha(int, bool &);
};
#endif //PILHADECRESCENTE_H
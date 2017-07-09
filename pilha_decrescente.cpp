#include <iostream>
#include "pilha_decrescente.h"
using namespace std;

pilha_decrescente::pilha_decrescente() :pilha_burra() 
{
}

pilha_decrescente::~pilha_decrescente()
{
}

void pilha_decrescente::Empilha(int X, bool &DeuCerto) {

	bool DeuCertoTbm = false;
	if ((Vazia()) || (X < get_elemento_topo()) || (X == get_elemento_topo() + 10)) 
	{
		pilha_burra::Empilha(X, DeuCertoTbm);
	}
	if (DeuCertoTbm)
		DeuCerto = true;
	else
		DeuCerto = false;
}


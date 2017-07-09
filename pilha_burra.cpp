#include "pilha_burra.h"
#include "headers.h"
#include <iostream>
using namespace std;

pilha_burra::pilha_burra() 
{
	set_topo(-1);
}

pilha_burra::~pilha_burra() 
{
}

bool pilha_burra::Vazia() const 
{
	if (get_topo() == -1)
		return true;
	else
		return false;
}

bool pilha_burra::Cheia() const 
{
	if (get_topo() == (QUANT_CARTAS - 1))
		return true;
	else
		return false;
}

void pilha_burra::Empilha(int X, bool &DeuCerto) 
{
	if (Cheia())
		DeuCerto = false;
	else {
		DeuCerto = true;
		aumenta_topo();
		set_elemento_topo(X);
	}
}

void pilha_burra::Desempilha(int &X, bool &DeuCerto)
{
	if (Vazia())
		DeuCerto = false;
	else {
		DeuCerto = true;
		X = get_elemento_topo();
		diminui_topo();
	}
}

void pilha_burra::aumenta_topo() 
{
	this->topo += 1;
}

void pilha_burra::diminui_topo() 
{
	this->topo -= 1;
}

int pilha_burra::get_topo() const 
{
	return this->topo;
}

void pilha_burra::set_topo(int t) 
{
	this->topo = t;
}

void pilha_burra::set_elemento_topo(int X) 
{
	this->Elementos[this->topo] = X;
}

int pilha_burra::get_elemento_topo() const 
{
	return this->Elementos[this->topo];
}
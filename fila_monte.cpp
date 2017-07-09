#include "headers.h"

fila_monte::fila_monte() 
{
	InicializaElementos();
}

fila_monte::~fila_monte() 
{
}

void fila_monte::InicializaElementos() 
{
	bool DeuCerto;

	NroElementos = 0;
	Primeiro = -1;
	Ultimo = -1;

	//Inicializando vetor na ordem
	for (int i = 1; i<=(QUANT_CARTAS); i++)
		Insere(i, DeuCerto);

	//Chamando funcao para embaralhar vetor
	srand(time(NULL));
	EmbaralhaElementos();
}

void fila_monte::EmbaralhaElementos()
{
	int r;
	for (int i = 0; i<NroElementos; i++) 
	{
		r = (rand() % NroElementos);
		int temp = Elementos[i];
		Elementos[i] = Elementos[r];
		Elementos[r] = temp;
	}
}

bool fila_monte::Vazia() const 
{
	if (get_NroElementos() == 0)
		return true;
	else
		return false;
}

bool fila_monte::Cheia() const 
{
	if (get_NroElementos() == QUANT_CARTAS)
		return true;
	else
		return false;
}

void fila_monte::Insere(int X, bool &DeuCerto)
{
	if (Cheia())
		DeuCerto = false;
	else 
	{
		if (Vazia())
			proximo_primeiro();

		DeuCerto = true;
		aumenta_NroElementos();
		proximo_ultimo();
		set_elemento_ultimo(X);
	}
}

void fila_monte::Retira(int &X, bool &DeuCerto) 
{
	if (Vazia())
		DeuCerto = false;
	else
	{
		DeuCerto = true;
		diminui_NroElementos();
		X = get_elemento_primeiro();
		proximo_primeiro();
	}
}

void fila_monte::proximo_primeiro() 
{
	this->Primeiro += 1; 
}

void fila_monte::proximo_ultimo() 
{
	this->Ultimo += 1;
}

int fila_monte::get_primeiro() const 
{
	return this->Primeiro;
}

int fila_monte::get_ultimo() const
{
	return this->Ultimo;
}

void fila_monte::set_elemento_ultimo(int novo)
{
	this->Elementos[this->Ultimo] = novo;
}

void fila_monte::diminui_NroElementos() 
{
	this->NroElementos -= 1;
}

void fila_monte::aumenta_NroElementos() 
{
	this->NroElementos += 1;
}

int fila_monte::get_elemento_primeiro() const 
{
	return this->Elementos[this->Primeiro];
}

int fila_monte::get_elemento_ultimo() const 
{
	return this->Elementos[this->Ultimo];
}

int fila_monte::get_NroElementos() const
{
	return this->NroElementos;
}

void fila_monte::set_primeiro(int X) 
{
	this->Primeiro = X;
}

int fila_monte::get_elemento_X(int X) const
{
	return this->Elementos[X];
}

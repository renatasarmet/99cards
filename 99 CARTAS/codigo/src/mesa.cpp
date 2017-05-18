#include "headers.h"

mesa::mesa()
{
	LimpaMesa();
	carregou = false;

	for (int j = 0; j < TAMANHO_MESA; j++) {
		teste[j] = new cartas();
	}
}

mesa::~mesa() 
{
}

void mesa::LimpaMesa()
{
	bool DeuCerto;
	set_NroElementos(0);
	for (int i = 0; i<TAMANHO_MESA; i++) 
	{
		set_elemento_i(i, 0, DeuCerto);
	}
	set_NroElementos(0);
}

bool mesa::Vazia() const 
{
	if (get_NroElementos() == 0)
		return true;
	else
		return false;
}

bool mesa::Cheia() const
{
	if (get_NroElementos() == TAMANHO_MESA)
		return true;
	else
		return false;
}

void mesa::diminui_NroElementos()
{
	this->NroElementos -= 1;
}

void mesa::aumenta_NroElementos() 
{
	this->NroElementos += 1;
}

int mesa::get_NroElementos() const 
{
	return this->NroElementos;
}

void mesa::set_NroElementos(int X) 
{
	this->NroElementos = X;
}

int mesa::get_elemento_i(int i, bool &DeuCerto) const
{
	if ((i >= 0) && (i<TAMANHO_MESA)) 
	{
		DeuCerto = true;
		return this->Elementos[i];
	}
	DeuCerto = false;
	return 0;
}

void mesa::set_elemento_i(int i, int X, bool &DeuCerto)
{
	if ((i >= 0) && (i < TAMANHO_MESA))
	{
		DeuCerto = true;
		this->Elementos[i] = X;

		std::string aux = std::to_string(X);
		aux = "imagens/cartaazul" + aux + ".jpg";

		if (X != 0)
		{
			teste[i]->carregar(aux);

			teste[i]->_sprite.setOrigin(teste[i]->_sprite.getLocalBounds().width/2, teste[i]->_sprite.getLocalBounds().height/2);

			if (i % 2 == 0)
				teste[i]->set_posicao(250 + (i * 100), 1020);
			else
				teste[i]->set_posicao(150 + (i * 100), 1270);
		}
	}
	else
		DeuCerto = false;
}

bool mesa::insereMesa(int X, bool &DeuCerto)
{
	if (Cheia()) 
	{
		DeuCerto = false;
	}
	else 
	{
		for (int i = 0; i < TAMANHO_MESA; i++)
		{
			if (get_elemento_i(i, DeuCerto) == 0)
			{
				aumenta_NroElementos();
				set_elemento_i(i, X, DeuCerto);
				return true;
			}
		}
	}
	return false;
}

void mesa::removeMesa(sf::RenderWindow& window, int i)
{
	bool DeuCerto;
	set_elemento_i(i, 0, DeuCerto);
	diminui_NroElementos();
	teste[i]->carregar("");
}

void mesa::distribuicao(fila_monte &f, int quantidade)
{
	bool DeuCerto;
	int X;
	for (int i = 0; i < quantidade; i++)
	{
		f.Retira(X, DeuCerto);
		if (DeuCerto)
			insereMesa(X, DeuCerto);
	}
}

void mesa::NovaDistribuicao(fila_monte &f, bool &DeuCerto)
{
	if (get_NroElementos() > 6)
		DeuCerto = false;
	else
	{
		distribuicao(f, 2);
		DeuCerto = true;
	}
}

void mesa::PrimeiraDistribuicao(fila_monte &f, bool &DeuCerto)
{
	if (get_NroElementos() != 0)
		DeuCerto = false;
	else 
	{
		distribuicao(f, 8);
		DeuCerto = true;
	}
}

void mesa::set_posicao(float x, float y)
{
	if (carregou)
		_sprite.setPosition(x, y);
}

float mesa::get_altura() const
{
	return _sprite.getLocalBounds().height;
}

float mesa::get_largura() const
{
	return _sprite.getLocalBounds().width;
}

void mesa::adicionar_mesa(std::string nome, cartas* carta_mesa)
{
	_carta_mesa.insert(std::pair<std::string, cartas*>(nome, carta_mesa));
}

sf::Rect<float> mesa::get_bounding_rect()
{
	sf::Vector2f size = _sprite.getScale();
	sf::Vector2f position = _sprite.getPosition();

	return sf::Rect<float>(position.x - size.x / 2, position.y - size.y / 2, position.x + size.x / 2, position.y + size.y / 2);
}
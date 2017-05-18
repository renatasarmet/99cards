#include "gerenciador_cartas.h"

gerenciador_cartas::gerenciador_cartas()
{
}

gerenciador_cartas::~gerenciador_cartas()
{
	std::for_each(_carta_jogo.begin(), _carta_jogo.end(), carta_jogo_alocador());
}

void gerenciador_cartas::adicionar(std::string nome, cartas* carta_jogo)
{
	_carta_jogo.insert(std::pair<std::string, cartas*>(nome, carta_jogo));
}


void gerenciador_cartas::remover(std::string nome)
{
	std::map<std::string, cartas*>::iterator resultado = _carta_jogo.find(nome);
	if (resultado != _carta_jogo.end())
	{
		delete resultado->second;
		_carta_jogo.erase(resultado);
	}
}

cartas* gerenciador_cartas::get(std::string nome) const
{
	std::map<std::string, cartas*>::const_iterator resultado = _carta_jogo.find(nome);
	if (resultado == _carta_jogo.end())
		return NULL;
	return resultado->second;
}

int gerenciador_cartas::get_contador_cartas() const
{
	return _carta_jogo.size();
}

void gerenciador_cartas::desenhar_todos(sf::RenderWindow& renderWindow)
{
	std::map<std::string, cartas*>::const_iterator itr = _carta_jogo.begin();
	while (itr != _carta_jogo.end())
	{
		itr->second->desenhar(renderWindow);
		itr++;
	}
}
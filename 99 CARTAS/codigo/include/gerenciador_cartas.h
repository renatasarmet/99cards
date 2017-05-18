#ifndef GERENCIADOR_CARTAS_H
#define GERENCIADOR_CARTAS_H

#include "headers.h"

class gerenciador_cartas
{
public:
	//CONSTRUTOR
	gerenciador_cartas();
	//DESTRUTOR
	~gerenciador_cartas();
	//FUNÇOES
	void adicionar(std::string nome, cartas* carta_jogo);
	void remover(std::string nome);
	int get_contador_cartas() const;
	cartas* get(std::string nome) const;

	void desenhar_todos(sf::RenderWindow& renderWindow);

private:
	std::map<std::string, cartas*> _carta_jogo;

	struct carta_jogo_alocador
	{
		void operator()(const std::pair < std::string, cartas*> & p) const
		{
			delete p.second;
		}
	};
};
#endif // !gerenciador_cartas

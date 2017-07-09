#ifndef MESA_H
#define MESA_H

#include "headers.h"
#define TAMANHO_MESA 8

class mesa
{
public:

	//CONSTRUTOR
	mesa();

	//DESTRUTOR
	~mesa();

	//METODOS
	bool Vazia() const;
	bool Cheia() const;
	bool insereMesa(int X, bool &DeuCerto);
	void removeMesa(sf::RenderWindow& window, int i);
	void LimpaMesa();
	void distribuicao(fila_monte &f, int quantidade);
	void NovaDistribuicao(fila_monte &f, bool &DeuCerto);
	void PrimeiraDistribuicao(fila_monte &f, bool &DeuCerto);

	//METODOS GET E SET
	int get_NroElementos() const;
	void set_NroElementos(int);
	void diminui_NroElementos();
	void aumenta_NroElementos();
	int get_elemento_i(int i, bool &DeuCerto) const;
	void set_elemento_i(int i, int X, bool &DeuCerto);

	virtual void set_posicao(float x, float y);

	virtual float get_altura() const;
	virtual float get_largura() const;

	void adicionar_mesa(std::string nome, cartas* carta_mesa);

	virtual sf::Rect<float> get_bounding_rect();

	cartas *teste[TAMANHO_MESA];
	
private:
	int Elementos[TAMANHO_MESA];
	int NroElementos;
	std::map<std::string, cartas*> _carta_mesa;
	sf::Sprite _sprite;
	sf::Texture _imagem;
	std::string nome_arquivo;
	bool carregou;
	
	struct carta_mesa_alocador
	{
		void operator()(const std::pair < std::string, cartas*> & p) const
		{
			delete p.second;
		}
	};
};
#endif // MESA_H
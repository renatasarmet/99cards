//#ifndef GERENCIADOR_MESA_H
//#define GERENCIADOR_MESA_H
//
//#include "headers.h"
//
//class gerenciador_mesa
//{
//public:
//	//CONSTRUTOR
//	gerenciador_mesa();
//	//DESTRUTOR
//	~gerenciador_mesa();
//	//FUNÇOES
//	void adicionar(std::string nome, mesa* carta_mesa);
//	//void remover(std::string nome);
//	//int get_contador_cartas() const;
//	//mesa* get(std::string nome) const;
//
//	void desenhar_todos(sf::RenderWindow& renderWindow);
//
//private:
//	std::map<std::string, mesa*> _carta_mesa;
//
//	struct carta_jogo_alocador
//	{
//		void operator()(const std::pair < std::string, mesa*> & p) const
//		{
//			delete p.second;
//		}
//	};
//};
//#endif // !gerenciador_cartas

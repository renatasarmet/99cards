//#include "headers.h"
//
//gerenciador_mesa::gerenciador_mesa()
//{
//}
//
//gerenciador_mesa::~gerenciador_mesa()
//{
//	std::for_each(_carta_mesa.begin(), _carta_mesa.end(), carta_jogo_alocador());
//}
//
//void gerenciador_mesa::adicionar(std::string nome, mesa* carta_mesa)
//{
//	_carta_mesa.insert(std::pair<std::string, mesa*>(nome, carta_mesa));
//}
//
////void gerenciador_mesa::remover(std::string nome)
////{
////	std::map<std::string, mesa*>::iterator resultado = _carta_mesa.find(nome);
////	if (resultado != _carta_mesa.end())
////	{
////		delete resultado->second;
////		_carta_mesa.erase(resultado);
////	}
////}
//
////mesa* gerenciador_mesa::get(std::string nome) const
////{
////	std::map<std::string, mesa*>::const_iterator resultado = _carta_mesa.find(nome);
////	if (resultado == _carta_mesa.end())
////		return NULL;
////	return resultado->second;
////}
//
////int gerenciador_mesa::get_contador_cartas() const
////{
////	return _carta_mesa.size();
////}
//
//void gerenciador_mesa::desenhar_todos(sf::RenderWindow& renderWindow)
//{
//	std::map<std::string, mesa*>::const_iterator itr = _carta_mesa.begin();
//	while (itr != _carta_mesa.end())
//	{
//		itr->second->desenhar();
//		itr++;
//	}
//}
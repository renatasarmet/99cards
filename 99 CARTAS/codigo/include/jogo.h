#ifndef JOGO_H
#define JOGO_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "headers.h"

class Jogo
{

public:
	static void Start(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, fila_monte&, bool&);
	static void Desfazer(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, bool&);
	static void CriandoTudo();
	static void JogarNovamente(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, fila_monte&, bool&);

private:
	static bool IsExiting();
	static void loop_jogo(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, fila_monte&, bool&);

	static void mostrar_tela_inicial();
	static void mostrar_menu(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*);
	static void mostrar_instrucao(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*);
	static void mostrar_ganhou(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, fila_monte&, bool&);
	static void mostrar_perdeu(mesa*, pilha_crescente*, pilha_crescente*, pilha_decrescente*, pilha_decrescente*, fila_monte&, bool&);

	enum GameState{ 
		Inicializado, Mostrando_Tela_Inicial, Pausado, Mostrando_Menu, Jogando, Saindo, Ganhando, Perdendo, Mostrando_Instrucao}; // estado que o jogo pode estar durante a partida

	static GameState estado_jogo;
	static sf::RenderWindow janela;
	static sf::Sprite background;
	static gerenciador_cartas _gerenciador_cartas;
	static bool selecionado;
	static bool podeDesfazer;
	static int ultimaPilhaAtualizada;
	static int i;
};
#endif
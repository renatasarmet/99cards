#include "headers.h"
#include "jogo.h"

#define LARGURA 1125;
#define ALTURA 1500;

Jogo::GameState Jogo::estado_jogo = Inicializado;
sf::RenderWindow Jogo::janela;
gerenciador_cartas Jogo::_gerenciador_cartas;
sf::Sprite Jogo::background;
bool Jogo::selecionado = false;
int Jogo::i = 0;
bool Jogo::podeDesfazer = false;
int Jogo::ultimaPilhaAtualizada = 0;

bool VerificaGameOver(mesa m, pilha_crescente &c1, pilha_crescente &c2, pilha_decrescente &d1, pilha_decrescente &d2) {
	int i, carta;
	bool DeuCerto, ok;

	for (i = 0; i<TAMANHO_MESA; i++) {
		carta = m.get_elemento_i(i, DeuCerto);
		if (carta != 0) {
			ok = false;
			c1.Empilha(carta, DeuCerto);
			if (DeuCerto) {
				c1.Desempilha(carta, DeuCerto);
				ok = true;
			}
			else {
				c2.Empilha(carta, DeuCerto);
				if (DeuCerto) {
					c2.Desempilha(carta, DeuCerto);
					ok = true;
				}
				else {
					d1.Empilha(carta, DeuCerto);
					if (DeuCerto) {
						d1.Desempilha(carta, DeuCerto);
						ok = true;
					}
					else {
						d2.Empilha(carta, DeuCerto);
						if (DeuCerto) {
							d2.Desempilha(carta, DeuCerto);
							ok = true;
						}
					}
				}
			}
			if (ok)
				return false;
		}
	}
	return true;
}


bool VerificaGanhou(mesa m, fila_monte f) {
	int i;
	i = f.get_NroElementos() + m.get_NroElementos();
	if (i == 0) {
		return true;
	}
	return false;
}

void Jogo::Desfazer(mesa *m, pilha_crescente* pilha_c1, pilha_crescente* pilha_c2, pilha_decrescente* pilha_d1, pilha_decrescente* pilha_d2, bool& DeuCerto)
{
	int carta;
	std::string aux;
	if (podeDesfazer) {
		podeDesfazer = false;
		switch (ultimaPilhaAtualizada)
		{
		case 1:
			pilha_c1->Desempilha(carta, DeuCerto);
			if (DeuCerto) {
				if (pilha_c1->Vazia()) 
				{
					aux = "imagens/fundo0.jpg";
				}
				else
				{
					aux = std::to_string(pilha_c1->get_elemento_topo());
					aux = "imagens/cartaroxa" + aux + ".jpg";
				}
				pilha_c1->carregar(aux);
			}
			break;
		case 2:
			pilha_c2->Desempilha(carta, DeuCerto);
			if (DeuCerto) {
				if (pilha_c2->Vazia()) {
					aux = "imagens/fundo0.jpg";
				}
				else {
					aux = std::to_string(pilha_c2->get_elemento_topo());
					aux = "imagens/cartaroxa" + aux + ".jpg";
				}
				pilha_c2->carregar(aux);
			}
			break;
		case 3:
			pilha_d1->Desempilha(carta, DeuCerto);
			if (DeuCerto) {
				if (pilha_d1->Vazia()) {
					aux = "imagens/fundo100.jpg";
				}
				else {
					aux = std::to_string(pilha_d1->get_elemento_topo());
					aux = "imagens/cartaroxa" + aux + ".jpg";
				}
				pilha_d1->carregar(aux);
			}
			break;
		case 4:
			pilha_d2->Desempilha(carta, DeuCerto);
			if (DeuCerto) {
				if (pilha_d2->Vazia()) {
					aux = "imagens/fundo100.jpg";
				}
				else {
					aux = std::to_string(pilha_d2->get_elemento_topo());
					aux = "imagens/cartaroxa" + aux + ".jpg";
				}
				pilha_d2->carregar(aux);
			}
			break;
		default:
			DeuCerto = false;
		}
		m->insereMesa(carta, DeuCerto);

	}
}

void Jogo::CriandoTudo(void)
{
	mesa *m = new mesa();
	fila_monte f; 
	pilha_crescente *pilha_c1 = new pilha_crescente();
	pilha_crescente *pilha_c2 = new pilha_crescente();
	pilha_decrescente *pilha_d1 = new pilha_decrescente();
	pilha_decrescente *pilha_d2 = new pilha_decrescente();
	bool DeuCerto;

	Jogo::Start(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);

}

void Jogo::JogarNovamente(mesa* m, pilha_crescente* pilha_c1, pilha_crescente* pilha_c2, pilha_decrescente* pilha_d1, pilha_decrescente* pilha_d2, fila_monte& f, bool& DeuCerto)
{
	Jogo::Start(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
	estado_jogo = Jogo::Jogando;
	pilha_c1->carregar("imagens/fundo0.jpg");
	pilha_c2->carregar("imagens/fundo0.jpg");
	pilha_d1->carregar("imagens/fundo100.jpg");
	pilha_d2->carregar("imagens/fundo100.jpg");
}

void Jogo::Start(mesa* m, pilha_crescente* pilha_c1, pilha_crescente* pilha_c2, pilha_decrescente* pilha_d1, pilha_decrescente* pilha_d2, fila_monte& f, bool& DeuCerto)
{
	f.InicializaElementos();
	pilha_c1->set_topo(-1);
	pilha_c2->set_topo(-1);
	pilha_d1->set_topo(-1);
	pilha_d2->set_topo(-1);
	m->LimpaMesa(); 	

	m->PrimeiraDistribuicao(f, DeuCerto);

	if (estado_jogo != Inicializado)
		return;

	janela.create(sf::VideoMode(1125, 1500), "99 Cartas", sf::Style::Close); //DEFINE TAMANHO DA JANELA, O QUE APARECE NO CABEÇALHO E FUNCOES DISPONIVEIS (FECHAR, RESIZE, MINIMIZAR)
	
	sf::Texture imagem;
	imagem.loadFromFile("imagens/fundo2.jpg");
	background.setTexture(imagem); //DEFINE O BACKGROUND
	
	pilha_c1->carregar("imagens/fundo0.jpg");
	pilha_c1->set_posicao(760, 160);

	pilha_c2->carregar("imagens/fundo0.jpg");
	pilha_c2->set_posicao(250, 160);

	pilha_d1->carregar("imagens/fundo100.jpg");
	pilha_d1->set_posicao(760, 570);

	pilha_d2->carregar("imagens/fundo100.jpg");
	pilha_d2->set_posicao(250, 570);

	_gerenciador_cartas.adicionar("pilha_c1", pilha_c1); //adiciona as novas pilhas ao gerenciador de cartas
	_gerenciador_cartas.adicionar("pilha_c2", pilha_c2);
	_gerenciador_cartas.adicionar("pilha_d1", pilha_d1);
	_gerenciador_cartas.adicionar("pilha_d2", pilha_d2);

	for (int j = 0; j < TAMANHO_MESA; j++)
	{
		std::string aux = std::to_string(j);
		aux = "teste" + aux;
		_gerenciador_cartas.adicionar(aux, m->teste[j]);
	}

	estado_jogo = Jogo::Mostrando_Tela_Inicial;

	while (!IsExiting())
	{
		loop_jogo(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
	}

	janela.close();
}

bool Jogo::IsExiting()
{
	if (estado_jogo == Jogo::Saindo)
		return true;
	else
		return false;
}

void Jogo::loop_jogo(mesa *m, pilha_crescente *pilha_c1, pilha_crescente *pilha_c2, pilha_decrescente *pilha_d1, pilha_decrescente *pilha_d2, fila_monte& f, bool& DeuCerto)
{
	int x;
	switch (estado_jogo)
	{
		case Jogo::Mostrando_Menu:
		{
			mostrar_menu(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2);
			break;
		}
		case Jogo::Mostrando_Tela_Inicial:
		{
			mostrar_tela_inicial();
			break;
		}
		case Jogo::Mostrando_Instrucao:
		{
			mostrar_instrucao(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2);
			break;
		}
		case Jogo::Ganhando:
		{
			mostrar_ganhou(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
			break;
		}
		case Jogo::Perdendo:
		{
			mostrar_perdeu(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
			break;
		}
		case Jogo::Jogando:
		{
			sf::Event evento_atual;
			sf::Sprite botao_desfazer;
			sf::Texture imagem;
			sf::Sprite botao_menu;
			sf::Texture imagem1;
			sf::Sprite botao_dnv;
			sf::Texture imagem2;
			bool DeuCerto;
			int pilha = 0;

			imagem.loadFromFile("imagens/desfazer.png");
			botao_desfazer.setTexture(imagem);
			botao_desfazer.setPosition(510, 450);

			imagem1.loadFromFile("imagens/botao_menu.png");
			botao_menu.setTexture(imagem1);
			botao_menu.setPosition(690, 50);

			imagem2.loadFromFile("imagens/botao_dnv.png");
			botao_dnv.setTexture(imagem2);
			botao_dnv.setPosition(70, 50);
			
			while (janela.pollEvent(evento_atual))
			{
				if (f.get_NroElementos() > 0)
				{
					if (m->get_NroElementos() == 6)
					{
						m->NovaDistribuicao(f, DeuCerto);
						podeDesfazer = false;
					}
					else if (m->get_NroElementos() == 8)
						podeDesfazer = false;
				}

				janela.clear();
				janela.draw(background);
				janela.draw(botao_menu);
				janela.draw(botao_dnv);
				if (podeDesfazer)
				{
					janela.draw(botao_desfazer);
				}
				_gerenciador_cartas.desenhar_todos(janela);
				
				janela.display();
			
				switch (evento_atual.type)
				{
				case sf::Event::Closed:
					estado_jogo = Jogo::Saindo;

				case sf::Event::MouseButtonPressed:
					if (evento_atual.mouseButton.button == sf::Mouse::Left && selecionado == false)
						for (i = 0; i < TAMANHO_MESA; i++)
						{
							if (m->teste[i]->pressionado(janela))
							{
								selecionado = true;
								break;
							}
						}
					if(evento_atual.mouseButton.button == sf::Mouse::Left && podeDesfazer == true)
						if (botao_desfazer.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							Jogo::Desfazer(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, DeuCerto);
						}
					if (evento_atual.mouseButton.button == sf::Mouse::Left)
						if (botao_menu.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							mostrar_menu(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2);
						}
					if (evento_atual.mouseButton.button == sf::Mouse::Left)
						if (botao_dnv.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							Jogo::JogarNovamente(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
						}
					break;

				case sf::Event::MouseMoved:
					if (selecionado == true)
					{
						m->teste[i]->_sprite.setPosition((float)sf::Mouse::getPosition(janela).x, (float)sf::Mouse::getPosition(janela).y);
					}		
					break;

				case sf::Event::MouseButtonReleased:
					if (selecionado == true)
					{
						if (pilha_c1->_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x,sf::Mouse::getPosition(janela).y))
						{
							pilha_c1->Empilha(m->get_elemento_i(i, DeuCerto), DeuCerto);
							if (DeuCerto)
							{
								if (m->get_elemento_i(i, DeuCerto) != 0) {
									podeDesfazer = true;
									ultimaPilhaAtualizada = 1;
									std::string aux = std::to_string(m->get_elemento_i(i, DeuCerto));
									aux = "imagens/cartaroxa" + aux + ".jpg";
									pilha_c1->carregar(aux);
									m->removeMesa(janela, i);
								}
								else {
									pilha_c1->Desempilha(x, DeuCerto);
								}
								
							}
							else
							{
								if (i % 2 == 0)
									m->teste[i]->set_posicao(250 + (i * 100), 1020);
								else
									m->teste[i]->set_posicao(150 + (i * 100), 1270);
							}
						}
								
						else if (pilha_c2->_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							pilha_c2->Empilha(m->get_elemento_i(i, DeuCerto), DeuCerto);
							if (DeuCerto)
							{
								if (m->get_elemento_i(i, DeuCerto) != 0) {
									podeDesfazer = true;
									ultimaPilhaAtualizada = 2;
									std::string aux = std::to_string(m->get_elemento_i(i, DeuCerto));
									aux = "imagens/cartaroxa" + aux + ".jpg";
									pilha_c2->carregar(aux);
									m->removeMesa(janela, i);
								}
								else {
									pilha_c2->Desempilha(x, DeuCerto);
								}

							}
							else
							{
								if (i % 2 == 0)
									m->teste[i]->set_posicao(250 + (i * 100), 1020);
								else
									m->teste[i]->set_posicao(150 + (i * 100), 1270);
							}
						}
						else if (pilha_d1->_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							pilha_d1->Empilha(m->get_elemento_i(i, DeuCerto), DeuCerto);
							if (DeuCerto)
							{
								if (m->get_elemento_i(i, DeuCerto) != 0) {
									podeDesfazer = true;	
									ultimaPilhaAtualizada = 3;
									std::string aux = std::to_string(m->get_elemento_i(i, DeuCerto));
									aux = "imagens/cartaroxa" + aux + ".jpg";
									pilha_d1->carregar(aux);
									m->removeMesa(janela, i);
								}
								else {
									pilha_d1->Desempilha( x, DeuCerto);
								}
							}
							else
							{
								if (i % 2 == 0)
									m->teste[i]->set_posicao(250 + (i * 100), 1020);
								else
									m->teste[i]->set_posicao(150 + (i * 100), 1270);
							}
						}
						else if (pilha_d2->_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
						{
							pilha_d2->Empilha(m->get_elemento_i(i, DeuCerto), DeuCerto);
							if (DeuCerto)
							{
								if (m->get_elemento_i(i, DeuCerto) != 0) {
									podeDesfazer = true;
									ultimaPilhaAtualizada = 4;
									std::string aux = std::to_string(m->get_elemento_i(i, DeuCerto));
									aux = "imagens/cartaroxa" + aux + ".jpg";
									pilha_d2->carregar(aux);
									m->removeMesa(janela, i);
								}
								else {
									pilha_d2->Desempilha(x, DeuCerto);
								}
							}
							else
							{
								if (i % 2 == 0)
									m->teste[i]->set_posicao(250 + (i * 100), 1020);
								else
									m->teste[i]->set_posicao(150 + (i * 100), 1270);
							}
						}
						else
						{
							if (i % 2 == 0)
								m->teste[i]->set_posicao(250 + (i * 100), 1020);
							else
								m->teste[i]->set_posicao(150 + (i * 100), 1270);
						}
						selecionado = false;
					}
					if (VerificaGanhou(*m, f))
					{
						estado_jogo = Jogo::Ganhando;
						break;
					}
					else if (VerificaGameOver(*m, *pilha_c1, *pilha_c2, *pilha_d1, *pilha_d2))
					{
						estado_jogo = Jogo::Perdendo;
						break;
					}
					break;
				case sf::Event::KeyPressed:
					if (evento_atual.key.code == sf::Keyboard::Escape)
						mostrar_menu(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2);
					break;	
				default:
					break;
				}

			}
			break;
		}
	}
}

void Jogo::mostrar_tela_inicial()
{
	Tela_Inicial tela_incial;
	tela_incial.Mostrar(janela);
	estado_jogo = Jogo::Mostrando_Menu;
}

void Jogo::mostrar_ganhou(mesa *m, pilha_crescente *pilha_c1, pilha_crescente *pilha_c2, pilha_decrescente *pilha_d1, pilha_decrescente *pilha_d2, fila_monte& f, bool& DeuCerto)
{	
	Ganhou ganhou;
	Ganhou::ganhou resultado = ganhou.Mostrar(janela);
	switch (resultado)
	{
	case Ganhou::Sair:
		estado_jogo = Jogo::Saindo;
		break;
	case Ganhou::Jogar_Novamente:
		Jogo::JogarNovamente(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
		break;
	}
}

void Jogo::mostrar_perdeu(mesa *m, pilha_crescente *pilha_c1, pilha_crescente *pilha_c2, pilha_decrescente *pilha_d1, pilha_decrescente *pilha_d2, fila_monte& f, bool& DeuCerto)
{
	Perdeu perdeu;
	Perdeu::perdeu resultado = perdeu.Mostrar(janela);
	switch (resultado)
	{
	case Perdeu::Sair:
		estado_jogo = Jogo::Saindo;
		break;
	case Perdeu::Jogar_Novamente:
		Jogo::JogarNovamente(m, pilha_c1, pilha_c2, pilha_d1, pilha_d2, f, DeuCerto);
		break;
	}
}

void Jogo::mostrar_menu(mesa *m, pilha_crescente *pilha_c1, pilha_crescente *pilha_c2, pilha_decrescente *pilha_d1, pilha_decrescente *pilha_d2)
{
	Menu menu;
	Menu::menu_inicial resultado = menu.Mostrar(janela);
	switch (resultado)
	{
	case Menu::Sair:
		estado_jogo = Jogo::Saindo;
		break;
	case Menu::Jogar:
		estado_jogo = Jogo::Jogando;
		break;
	case Menu::Instrucoes:
		estado_jogo = Jogo::Mostrando_Instrucao;
	}
}

void Jogo::mostrar_instrucao(mesa *m, pilha_crescente *pilha_c1, pilha_crescente *pilha_c2, pilha_decrescente *pilha_d1, pilha_decrescente *pilha_d2)
{
	Instrucoes instrucao;
	instrucao.set_k(1);
	int continua = 1;
	while (continua == 1) {
		Instrucoes::instrucoes_opcoes resultado = instrucao.Mostrar(janela);
		switch (resultado)
		{
		case Instrucoes::Menu:
			estado_jogo = Jogo::Mostrando_Menu;
			continua = 0;
			break;
		case Instrucoes::Jogar:
			estado_jogo = Jogo::Jogando;
			continua = 0;
			break;
		case Instrucoes::Sair:
			estado_jogo = Jogo::Saindo;
			continua = 0;
			break;
		case Instrucoes::Proximo:
			instrucao.proximo_k();
			break;
		case Instrucoes::Anterior:
			instrucao.anterior_k();
			break;
		}
	}
}

int main(int argc, char** argv)
{
	Jogo::CriandoTudo();

	return 0;
}
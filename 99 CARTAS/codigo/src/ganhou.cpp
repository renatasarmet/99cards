#include "headers.h"
#include "ganhou.h"

Ganhou::ganhou Ganhou::Mostrar(sf::RenderWindow & renderWindow)
{
	sf::Texture imagem;
	imagem.loadFromFile("imagens/ganhou2.jpg");

	sf::Sprite sprite;
	sprite.setTexture(imagem);

	item_ganhou botao_jogar;
	botao_jogar.rect.top = 1250;
	botao_jogar.rect.height = 1300;
	botao_jogar.rect.left = 250;
	botao_jogar.rect.width = 850;
	botao_jogar.action = Jogar_Novamente;

	//Coordenadas do botao SAIR
	item_ganhou botao_sair;
	botao_sair.rect.top = 1300;
	botao_sair.rect.height = 1450;
	botao_sair.rect.left = 300;
	botao_sair.rect.width = 800;
	botao_sair.action = Sair;

	itens_ganhou.push_back(botao_jogar);
	itens_ganhou.push_back(botao_sair);

	renderWindow.draw(sprite);
	renderWindow.display();

	return obter_resposta_ganhou(renderWindow);
}

Ganhou::ganhou Ganhou::clique(int x, int y)
{
	std::list<item_ganhou>::iterator it;

	for (it = itens_ganhou.begin(); it != itens_ganhou.end(); it++)
	{
		sf::Rect<int> item_do_ganhou = (*it).rect;
		if (item_do_ganhou.top < y && item_do_ganhou.height > y && item_do_ganhou.left < x && item_do_ganhou.width > x)
			return (*it).action;
	}

	return Nada;
}

Ganhou::ganhou Ganhou::obter_resposta_ganhou(sf::RenderWindow& window)
{
	sf::Event evento_ganhou;

	while (1 != 0)
	{
		while (window.pollEvent(evento_ganhou))
		{
			if (evento_ganhou.type == sf::Event::MouseButtonPressed)
				return clique(int(evento_ganhou.mouseButton.x), int(evento_ganhou.mouseButton.y));
			if (evento_ganhou.type == sf::Event::Closed)
				return Sair;
		}
	}
}

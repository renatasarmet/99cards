#include "headers.h"

cartas::cartas()
{
	carregou = false;
}

cartas::~cartas()
{
}

void cartas::carregar(std::string nomearquivo)
{
	if (_imagem.loadFromFile(nomearquivo) == false)
	{
		nome_arquivo = "";
		carregou = false;
	}
	else
	{
		nome_arquivo = nomearquivo;
		_sprite.setTexture(_imagem);
		carregou = true;
	}
}

void cartas::desenhar(sf::RenderWindow& renderWindow)
{
	if (carregou)	
		renderWindow.draw(_sprite);
}

void cartas::set_posicao(float x, float y)
{
	if (carregou)
		_sprite.setPosition(x, y);
}

float cartas::get_x() const
{
	return _sprite.getPosition().x;
}

float cartas::get_y() const
{
	return _sprite.getPosition().y;
}

void cartas::set_origem(float x, float y)
{
	if (carregou)
		_sprite.setOrigin(x, y);
}

float cartas::get_origem_x() const
{
	return _sprite.getOrigin().x;
}

float cartas::get_origem_y() const
{
	return _sprite.getOrigin().y;
}

float cartas::get_altura() const
{
	return _sprite.getLocalBounds().height;
}

float cartas::get_largura() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> cartas::get_bounding_rect()
{
	sf::Vector2f position = _sprite.getPosition();

	return sf::Rect<float>(position.x - _sprite.getGlobalBounds().width/ 2, position.y - _sprite.getGlobalBounds().height / 2, _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

bool cartas::selecionado(sf::RenderWindow & window)
{
	if (mouse_intersects(window))
	{
		estado = true;
		return true;
	}
	else
	{
		estado = false;
		return false;
	}
}

bool cartas::pressionado(sf::RenderWindow & window)
{
	if (selecionado(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		estado = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool cartas::mouse_intersects(sf::RenderWindow & window)
{
	sf::FloatRect aux;
	aux = get_bounding_rect();

	if (sf::Mouse::getPosition(window).x >= aux.left
		&& sf::Mouse::getPosition(window).x <= aux.left + aux.width
		&& sf::Mouse::getPosition(window).y >= aux.top
		&& sf::Mouse::getPosition(window).y <= aux.top + aux.height)
	{
		return true;
	}
	else
	{
		return false;
	}
}
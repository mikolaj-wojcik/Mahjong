#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include <iostream>
#include<filesystem>
#include <string>
export module Tile;


class colours{};


export class Tile : public sf::Drawable{
public:
	sf::Sprite sprite;
	
	bool movable = false;
	bool exist = false; 
	int type;
	float scaleX;
	float scaleY;
	
	Tile() {
	};
	Tile(sf::Texture& texture, float t_widht, float t_height, float t_x = 0.0, float t_y = 0.0, int t_type = 0, bool mov = false) :type(t_type) {
		sprite.setTexture(texture);
		scaleX = t_widht / sprite.getTexture()->getSize().x;
		scaleY = t_height / sprite.getTexture()->getSize().y;
		sprite.setScale(scaleX, scaleY);
		sprite.setPosition(sf::Vector2f{ t_x, t_y});
		movable = mov;
		exist = true;
	}
	~Tile(){}

	
	void changeToMov(sf::Texture& texture) {
		movable = true;
		sprite.setTexture(texture);
		sprite.setScale(scaleX, scaleY);
	}

	int getType() {
		return type;
	}
	const bool getMovable() {
		return movable;
	}
	const bool getExist() {
		return exist;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const {
		if(exist)
		target.draw(sprite);
	}

	bool isInside(sf::Vector2f pos) {
		if (this->getExist()) {
			if (sprite.getGlobalBounds().contains(pos))
				return true;
		}

		return false;


	}
	void remove();

	void selectedColor(bool select);
};

void Tile::remove() {
	movable = false;
	exist = false;
	
}

void Tile::selectedColor(bool select) {
	if (select)
		sprite.setColor(sf::Color::Red);
	else
		sprite.setColor(sf::Color::White);
}
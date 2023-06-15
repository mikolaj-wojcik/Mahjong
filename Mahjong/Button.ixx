#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<iostream>

export module Button;
import GameState;
//import Game;


export class Button {
		sf::RectangleShape shape;
		
		sf::Text tekst;
		sf::Font font;
		sf::Color font_color = sf::Color::Magenta;
		sf::Color line_color = sf::Color::White;

		sf::Color clicked_color;
		sf::Color regular_color;

		bool pressed;
		Button() = delete;

		void loadFont();
	public:
		Button(float t_X, float t_Y, float width, float height, std::string _tekst, unsigned int font_size,
			sf::Color tekst_color, sf::Color regular_color, sf::Color clicked_color);
		~Button() = default;
		const bool isPressed() const;
		const std::string getText() const;
		void setText(const std::string text);
		void update(const sf::Vector2f& mousePosition);
		void render(sf::RenderTarget& target);
	};



Button::Button(float t_X, float t_Y, float width, float height, std::string _tekst, unsigned int font_size,
	sf::Color tekst_color, sf::Color regular_color, sf::Color clicked_color) {
	this->shape.setPosition(sf::Vector2f(t_X, t_Y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(regular_color);
	loadFont();
	this->tekst.setFont(font);
	this->tekst.setString(_tekst);
	this->tekst.setFillColor(tekst_color);
	this->tekst.setCharacterSize(font_size);
	this->tekst.setStyle(sf::Text::Regular);
	this->tekst.setPosition(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->tekst.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y+5.0); 
	this->regular_color = regular_color;
	this->clicked_color = clicked_color;

}

void Button::update(const sf::Vector2f& mousePosition) {

	if (this->shape.getGlobalBounds().contains(mousePosition))
	{
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			pressed = true;
			this->shape.setFillColor(this->clicked_color);
		}
	}
	else {
		pressed = false;
		this->shape.setFillColor(this->regular_color);
	}


	
}

const std::string Button::getText() const {
	return this->tekst.getString();
}

void Button::Button::render(sf::RenderTarget& target) {
	target.draw(this->shape);
	target.draw(this->tekst);
}

const bool Button::isPressed() const{
	return pressed;
}

void Button::loadFont(){
		if (!font.loadFromFile("C:/Users/Mikolaj/Downloads/Lab4/Mahjong/Textures/Tiles/riichi-mahjong-tiles-master/Naprawiony/Fonts/KdamThmorPro-Regular.ttf")) {
			std::cerr << "Error loading font\n";
		}
}




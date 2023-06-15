#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<string>
#include<sstream>

#define DELETE 8
#define ENTER 13
#define ESC 27


export module Textbox;

export class Textbox {
	sf::Text textbox;
	std::ostringstream text;
	int limit;
	void inputLogic(int charTyped);
	void delete_char();
public:
	Textbox() {}
	Textbox(sf::Font* font, unsigned int _limit, unsigned int font_size, sf::Vector2f position, sf::Color color);
	std::string getString();
	void draw(sf::RenderTarget& target);
	void resetText();
	void typeChar(sf::Event& _input);
	
};

Textbox::Textbox(sf::Font* font, unsigned int _limit, unsigned int font_size, sf::Vector2f position, sf::Color color= sf::Color::White): limit(_limit) {
	textbox.setFont(*font);
	textbox.setCharacterSize(font_size);
	textbox.setPosition(position);
	textbox.setFillColor(color);
}

void Textbox::inputLogic(int charTyped) {
	if (charTyped != DELETE && charTyped != ENTER && charTyped != ESC) {
		text << static_cast<char>(charTyped);
	 }
	else if (charTyped != DELETE) {	
			delete_char();
	}
	textbox.setString(text.str() + "_");

}

void Textbox::delete_char() {
	if (text.str().length() > 0) {
		std::string temp(text.str());
		temp.pop_back();
	}
	//textbox.setString(temp);
}

std::string Textbox::getString() {
	return text.str();
}

void Textbox::draw(sf::RenderTarget& target) {
	target.draw(textbox);
}

void Textbox::resetText() {
	text.str("");
}

void Textbox::typeChar(sf::Event& _input) {
	int charTyped = _input.text.unicode;
	if (charTyped < 128 && (text.str().length() < limit || charTyped == DELETE)) {
		inputLogic(charTyped);
	}
}

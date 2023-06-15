#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<string>
#include<iostream>
export module GameState;

export class gameState { 
protected:
	gameState* next_state = nullptr;
	bool ended = false;
	bool doubleReturnValue = false;
	sf::Font* font = nullptr;
public:
	virtual void mousePos(int x, int y) = 0;
	virtual void mouseClick(int x, int y) = 0;
	virtual void keyboardInput(sf::Event& _event) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
	const bool returnFromState() { return ended; };
	const bool double_return() { return doubleReturnValue; };
	sf::Text returnText(std::string text, sf::Vector2f position, unsigned int size, sf::Color kolor);
	gameState* newSate();
	const bool isNewState();
	~gameState();
	//virtual bool stateChange
};

const bool gameState::isNewState() {
	if (next_state)
		return true;
	else
		return false;
}

gameState* gameState::newSate() {
	if (next_state){
		gameState* temp = next_state;
		next_state = nullptr;
		return temp;
	}
	else
		return nullptr;
}
gameState::~gameState() {
	delete next_state;
	delete font;
}

sf::Text gameState::returnText(std::string text, sf::Vector2f position,
	unsigned int size, sf::Color kolor = sf::Color::White) {
	if (!font) {
		font = new sf::Font();
		if (!font->loadFromFile("C:/Users/Mikolaj/Downloads/Lab4/Mahjong/Textures/Tiles/riichi-mahjong-tiles-master/Naprawiony/Fonts/KdamThmorPro-Regular.ttf")) {
			std::cerr << "Error loading font\n";
		}
	}
	sf::Text tempText;
	tempText.setFont(*font);
	tempText.setFillColor(kolor);
	tempText.setPosition(position);
	tempText.setString(text);
	tempText.setCharacterSize(size);

	return tempText;
}
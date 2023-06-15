#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
export module Menu;

import GameState;
import Button;
import Ranking;
import Game;

export class Menu : public gameState {
	Button* exit_button = nullptr;
	Button* ranking_button = nullptr;
	Button* game_button = nullptr;
	sf::Text mahjong_title;

public:
	Menu();
	~Menu();
	void mousePos(int x, int y);
	void mouseClick(int x, int y);
	void keyboardInput(sf::Event& _event){}
	void draw(sf::RenderTarget& target);
	const bool returnFromState() { return ended; }
	const bool double_return() { return false; }
	//gameState* newSate(int i);
};


Menu::Menu(){
	game_button = new Button(400.0, 300.0, 90.0, 50.0, "Start", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	ranking_button = new Button(400.0, 400.0, 90.0, 50.0, "Ranking", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	exit_button = new Button(400.0, 500.0, 90.0, 50.0, "Exit", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	mahjong_title = returnText("MAHJONG", sf::Vector2f(400.0f, 50.0f), 30);
}

Menu::~Menu() {
	delete game_button;
	delete ranking_button;
	delete exit_button;
}

void Menu::mouseClick(int x, int y) {
	exit_button->update(sf::Vector2f(x, y));
	game_button->update(sf::Vector2f(x, y));
	ranking_button->update(sf::Vector2f(x, y));
	if (game_button->isPressed()) {
		next_state = new Game();
	}
	if (ranking_button->isPressed()) {
		next_state = new Ranking();
	}
	if (exit_button->isPressed()) {
		ended = true;
	}

}

void Menu::draw(sf::RenderTarget& target) {
	exit_button->render(target);
	game_button->render(target);
	ranking_button->render(target);
	target.draw(mahjong_title);
}

void Menu::mousePos(int x, int y) {
	exit_button->update(sf::Vector2f(x, y));
	game_button->update(sf::Vector2f(x, y));
	ranking_button->update(sf::Vector2f(x, y));
}
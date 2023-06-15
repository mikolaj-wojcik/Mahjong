#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
//#include <SFML\Time.hpp>
export module Pause;

import GameState;
import Button;
import EndGameStates;

export class Pause : public gameState {
	Button* exit_button = nullptr;
	Button* return_button = nullptr;
	Button* instant_win = nullptr;

	sf::Time elapsed;
	sf::Clock* gameClock;
	sf::Text pause_text;

public:
	Pause(sf::Time elapsedConstruct, sf::Clock* clock);
	~Pause();
	void mousePos(int x, int y){}
	void mouseClick(int x, int y);
	void keyboardInput(sf::Event& _event){}
	void draw(sf::RenderTarget& target);
};


Pause::Pause(sf::Time elapsedConstruct, sf::Clock* clock):elapsed(elapsedConstruct),gameClock(clock) {
	exit_button = new Button(400.0, 400.0, 90.0, 50.0, "Exit", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	return_button = new Button(400.0, 300.0, 90.0, 50.0, "Return", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	instant_win = new Button(400.0, 500.0, 90.0, 50.0, "Cheat", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	pause_text = returnText("Pause", sf::Vector2f(400.0f, 50.0f), 30);
}

void Pause::mouseClick(int x, int y) {
	exit_button->update(sf::Vector2f(x, y));
	return_button->update(sf::Vector2f(x, y));
	instant_win->update(sf::Vector2f(x, y));
	if (return_button->isPressed()) {
		ended = true;
		gameClock->restart();
	}
	if (instant_win->isPressed()) {
		next_state = new Win(elapsed);
	}
	if (exit_button->isPressed()) {
		doubleReturnValue = true;
	}

}

void Pause::draw(sf::RenderTarget& target){
	exit_button->render(target); 
	return_button->render(target); 
	instant_win->render(target);
	target.draw(pause_text);
}
Pause::~Pause() {
	delete exit_button;
	delete return_button;
	delete instant_win;
}

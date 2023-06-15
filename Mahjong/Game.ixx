//#include <time.h>
//#include<compare>
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
//#include<Time.hpp>
#include <iostream>
export module Game;

import GameState;
import Board;
import Button;
import Pause;
import EndGameStates;


export class Game : public gameState {
	
	Board* board = nullptr;
	
	Button* pause_button = nullptr;
	sf::Text czas;
	//sf::Font font;

	sf::Clock* clock;
	sf::Time elapsedTillPause = sf::Time::Zero;

public:
	Game();

	void draw(sf::RenderTarget& target);

	void mousePos(int x, int y);

	void mouseClick(int x, int y);

	void keyboardInput(sf::Event& _event){}

	~Game();

	

};

Game::Game( ) {
	board = new Board();
	pause_button = new Button(0.0,0.0, 60.0,30.0, "||", 12, 
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	clock = new sf::Clock();
	clock->restart();
	
	czas = returnText("0", sf::Vector2f(900.0f, 1.0f), 30, sf::Color::Blue);
	
}

void Game::mouseClick(int x, int y) {
	board->getMouseClick(x, y);
	pause_button->update(sf::Vector2f(x, y));
	if (pause_button->isPressed()) {
		elapsedTillPause += clock->getElapsedTime();
		next_state = new Pause(elapsedTillPause, clock);
	}
	if (!board->isThereMoreMoves()) {
		if (board->isEmpty())
			next_state = new Win(elapsedTillPause + clock->getElapsedTime());
		else
			next_state = new Lose();
	}

}

void Game::mousePos(int x, int y) {
	pause_button->update(sf::Vector2f(x, y));
}


void Game::draw(sf::RenderTarget& target) {
	sf::String temp = std::to_string(((int)(clock->getElapsedTime() + elapsedTillPause).asSeconds()));
	czas.setString(temp);
	board->draw(target);
	pause_button->render(target);
	target.draw(czas);

}



Game::~Game() {
	delete board;
	delete pause_button;
	delete clock;
}

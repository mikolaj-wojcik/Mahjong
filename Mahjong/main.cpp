#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<iostream>
#include<stack>
#include<compare>
#include <string>


import StackManagment;
import GameState;

int main() {
	
	sf::RenderWindow window{ sf::VideoMode(1000,600),"Pk4Mahjong" };

	StackManagment statesStack;
	
	gameState* currentState = nullptr;
	
    sf::Event event;
	window.setFramerateLimit(30);
	while (true) {
			currentState = statesStack.current();
			
			
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {

						currentState->mouseClick(event.mouseButton.x, event.mouseButton.y);
					}
				}
				else if (event.type == sf::Event::KeyPressed)
					currentState->keyboardInput(event);
				currentState->mousePos(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			}
			window.clear();
			
			currentState->draw(window);
			
			window.display();
			statesStack.stackUpdate();
			if (statesStack.endProgram())
				break;
			
	}
	return 0;
}




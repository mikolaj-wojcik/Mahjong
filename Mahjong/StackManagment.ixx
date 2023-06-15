#include<stack>
export module StackManagment;

import GameState;
import Game;
import Board;
import Button;
import Pause;
import Menu;
import Ranking;

export class StackManagment {
	std::stack<gameState*> states;
	gameState* currentState = nullptr;

public:
	StackManagment();
	gameState* current();
	void stackUpdate();
	const bool endProgram();
};

StackManagment::StackManagment() {
	Menu* menu = new Menu();
	states.push(menu);
}

gameState* StackManagment::current() {
	return states.top();
}

void StackManagment::stackUpdate() {
	currentState = states.top();
	if (currentState->isNewState()) {
		states.push(currentState->newSate());
	}
	if (currentState->returnFromState()) {
		states.pop();
		//delete currentState;
	}
	if (currentState->double_return()) {
		states.pop();
		//delete currentState;
		if (!endProgram()) {
			currentState = states.top();
			states.pop();
			//delete currentState;
		}
	}
}

const bool StackManagment::endProgram() {
	if (states.empty())
		return true;
	else
		return false;
}
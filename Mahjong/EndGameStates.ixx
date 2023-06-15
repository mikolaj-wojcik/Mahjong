#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<iostream>
#include<string>
#include <regex>
#include <filesystem>
#include <fstream>
export module EndGameStates;

import GameState;
import Button;
//import Textbox;

//check name

export class Win : public gameState {
	sf::Time timeToSave;
	//Textbox textbox;
	Button* accept_button = nullptr;
	sf::Text win_text;
	std::string name;
	void getName();
	bool correctname = false;
	const bool match(std::string name);
	void saveToFile();
public:
	void mousePos(int x, int y) {}
	void draw(sf::RenderTarget& target);
	void mouseClick(int x, int y);
	void keyboardInput(sf::Event& _event);
	Win(sf::Time elapsed);
	~Win();
};


Win::Win(sf::Time elapsed) : timeToSave(elapsed) {
	accept_button = new Button(400.0, 500.0, 90.0, 50.0, "OK", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	win_text = returnText("You won!!!", sf::Vector2f(500.0f, 50.0f), 50);
	//textbox = Textbox(font, 24, 20, sf::Vector2f(300.0f, 400.0f));
}
Win::~Win() {
	delete accept_button;
}

void Win::draw(sf::RenderTarget& target) {
	accept_button->render(target);
	target.draw(win_text);
	//textbox.draw(target);
}

void Win::mouseClick(int x, int y) {
	accept_button->update(sf::Vector2f(x, y));
	if (accept_button->isPressed()) {
		getName();
		saveToFile();
		doubleReturnValue = true;
	}
}

void Win::keyboardInput(sf::Event& _event) {
	//textbox.typeChar(_event);
}

void Win::getName() {
	std::cout << "Podaj swoja nazwe:\n" << "Nazwa moze sie skladac wylacznie z liter i cyfr \n"
		<< "oraz miec maksymalnie 15 znakow.\n";
	std::string _name;
	std::cin >> _name;
	while (!match(_name)) {
		std::cin >> _name;
	}
	correctname = true;
	name = _name;
}

const bool Win::match(std::string name) {
	std::regex regex("([A-Z]|[0-9]|[a-z]){1,20}");
	std::smatch result;
	return std::regex_match(name, regex);
	
}

void Win::saveToFile() {
	std::ofstream outfile;
	std::filesystem::path folder("C:\\Users\\Mikolaj\\Downloads\\Lab4\\Mahjong\\Ranking");
	if (!std::filesystem::exists(folder)) {
		std::filesystem::create_directory(folder);
	}
	std::string full_path = folder.string() + "\\" + name + ".txt";
	outfile.open(full_path, std::ios_base::app); // append instead of overwrite
	outfile << std::to_string((int)timeToSave.asSeconds()) << "\n";
}












//-----------------------------------

export class Lose : public gameState {
	Button* accept_button = nullptr;
	sf::Text game_over_text;
public:
	void mousePos(int x, int y) {}
	void mouseClick(int x, int y);
	void keyboardInput(sf::Event& _event) {}
	void draw(sf::RenderTarget& target);
	Lose();
	~Lose();
};



Lose::Lose(){
	accept_button = new Button(400.0, 500.0, 90.0, 50.0, "OK", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	game_over_text = returnText("GameOver", sf::Vector2f(500.0f, 50.0f), 50);
}
Lose::~Lose() {
	delete accept_button;
}

void Lose::draw(sf::RenderTarget& target) {
	accept_button->render(target);
	target.draw(game_over_text);
}

void Lose::mouseClick(int x, int y) {
	accept_button->update(sf::Vector2f(x, y));
	if (accept_button->isPressed()) {
		doubleReturnValue = true;
	}
}

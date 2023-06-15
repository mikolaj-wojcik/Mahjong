#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<filesystem>
#include<string>
#include<regex>
#include <vector>
#include <ranges>
#include <fstream>
#include <iostream>
export module Ranking;


import GameState;
import Button;

//ranges sort
//ranges take 10
//regex to remove .csv
//regex/ ranges to split 



export class Ranking : public gameState {
	Button* return_button = nullptr;
	std::vector<sf::Text> allTexts;

public:
	Ranking();
	~Ranking();
	void mousePos(int x, int y){}
	void mouseClick(int x, int y);
	void keyboardInput(sf::Event& _event){}
	void draw(sf::RenderTarget& target);
	//const bool returnFromState() { return false; }
	std::vector<std::pair<std::string, unsigned int>> loadTopRecords();
	bool onlyNumbers(std::string score);
	void loadTexts();

};


Ranking::Ranking() {
	return_button = new Button(700.0, 400.0, 90.0, 50.0, "Return", 18,
		sf::Color::Black, sf::Color::Red, sf::Color::Magenta);
	loadTexts();
	
}
Ranking::~Ranking() {
	delete return_button;
}

void Ranking::mouseClick(int x, int y) {
	return_button->update(sf::Vector2f(x, y));
	if (return_button->isPressed()) {
		ended = true;
	}

}
void Ranking::draw(sf::RenderTarget& target) {
	return_button->render(target);
	for (auto& it : allTexts)
		target.draw(it);
}

bool sortBySec(const std::pair<std::string, unsigned int>& a,
	const std::pair<std::string, unsigned int>& b){
	return (a.second < b.second);
}

bool Ranking::onlyNumbers(std::string score) {
	std::regex numbers("[0-9]+");
	std::smatch result;
	if (std::regex_match(score, result, numbers))
		return true;
	else
		return false;
}

std::vector<std::pair<std::string, unsigned int>> Ranking::loadTopRecords() {
	std::filesystem::path folder("C:\\Users\\Mikolaj\\Downloads\\Lab4\\Mahjong\\Ranking");
	std::vector<std::pair<std::string, unsigned int>> records;
	std::string player_name;
	std::string tempscore;
	//std::string ranking_string("Ranking");
	if (!std::filesystem::exists(folder)) {
		std::filesystem::create_directory(folder);
	}
	for (auto& it : std::filesystem::directory_iterator(folder)) {
		std::fstream dataFromFile(it.path());
		player_name = it.path().stem().string();
		while (std::getline(dataFromFile, tempscore)) {
			if (onlyNumbers(tempscore))
				records.push_back(std::pair<std::string, unsigned int>(player_name, stoi(tempscore)));
		}
		dataFromFile.close();
	}
	std::ranges::sort(records, sortBySec);
	auto top10view = records | std::views::take(10);
	for (auto& it : top10view) {
		std::cout << it.first << " " << it.second << "\n";
	}
	return std::vector<std::pair<std::string, unsigned int>>(top10view.begin(), top10view.end());
}

void Ranking::loadTexts() {
	sf::Text top10 = returnText("TOP 10", sf::Vector2f(300.0f, 20.0f), 50);
	std::string temp;
	allTexts.push_back(top10);
	float heigh = 100.0;
	for (auto& it : loadTopRecords()) {
		temp = it.first + "      " + std::to_string(it.second);
		sf::Text single_record = returnText(temp, sf::Vector2f(300.0f, heigh), 20);
		allTexts.push_back(single_record);
		heigh += 40;
	}
}

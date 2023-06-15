#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include <string>
#include <vector>
#include <filesystem>
#include <array>
#include <algorithm>
#include <iostream>
#include <random>
#include <ranges>
#include <future>
#include<map>
#include <regex>
#include <sstream>

export module Board;

import Tile;

export class Board {
	//tilesBoard: array<array<array<Tile,12>,8>4>
	sf::Window wind;
	float width; 
	float height;
	const int x_space = 10, x_pre = 100, y_space = 10, y_pre = 0;
	Tile* selected = nullptr;
	std::map <int, sf::Texture*> tileTextures;
	std::array<int, 144> tileTypes;
	std::array<std::array<std::array<Tile, 12>, 8>, 4> tilesBoard;
	sf::Texture Background;
	sf::Sprite sprite;
	std::array<Tile, 4> extraTiles;
	std::map<int, int> avalibleTiles;
	std::vector<Tile*> open;
	std::filesystem::path pathy = "C:/Users/Mikolaj/Downloads/Lab4/Mahjong/Textures/Tiles/riichi-mahjong-tiles-master/Naprawiony/RegularLambda/";
	void textureLoad(std::filesystem::path path);
	void textureLoadAsync(std::vector<std::filesystem::path> range);
	void tileInitFunc(int begin, int end,  int ver, int &iter, std::vector<int> rows);
	void toMatch(Tile* only);
	void removeTiles(Tile* first, Tile* second);
	void tileInit();
	void array_initialize();
public:
	Board();
	~Board();

	void draw(sf::RenderTarget& target);

	void checkMovable();
	void getMouseClick(int mous_x, int mous_y);
	const bool isThereMoreMoves();
	const bool isEmpty();

};

Board::Board() {
	Background.loadFromFile("C:/Users/Mikolaj/Downloads/Lab4/Mahjong/Mahjong/Images/wood.jpg");
	width = 50.0;
	height = 60.0;
	sprite.setTexture(Background);
	textureLoad(pathy);
	array_initialize();
	tileInit();
	checkMovable();
}

Board::~Board() {
	for (auto& it : tileTextures) {
		delete it.second;
	}
}

void Board::textureLoad(std::filesystem::path path) {
	sf::Texture t;
	std::vector<std::filesystem::path> textureNames;
	std::vector<std::thread> futurez;
	//std::regex name("^?(\d+)(?:_\d+)?.png$");
	for (auto& fIt : std::filesystem::directory_iterator(path)) {
		textureNames.push_back(fIt.path());		
	}
	textureNames.begin();
	
	if (textureNames.size() < 74)
		std::cerr << "Not enough textures it folder";
	size_t quaterTexture = textureNames.size()/2;
	std::vector<std::filesystem::path>textureFileNames(textureNames.begin(), textureNames.end());
	
	futurez.push_back(std::thread(&Board::textureLoadAsync, this, std::vector<std::filesystem::path>(textureNames.begin(), textureNames.begin() + quaterTexture)));
	futurez.push_back(std::thread(&Board::textureLoadAsync, this, std::vector<std::filesystem::path>(textureNames.begin() + quaterTexture, textureNames.end())));
	for (auto& it : futurez)
		it.join();
		
}

void Board::textureLoadAsync(std::vector<std::filesystem::path> range) {
	std::string onlyName;
	int num;
	std::stringstream ss;
	for (auto& it : range) {
		sf::Texture* temp = new sf::Texture();
		if (!temp->loadFromFile(it.string())) {
			std::cerr << "Error loading file";
		}
		onlyName = it.stem().string();
		
		tileTextures.emplace(stoi(onlyName), temp);
	}
}

void Board::draw(sf::RenderTarget & target) {
	target.draw(sprite);
	for (auto& itY : tilesBoard[0]) {
		for (auto& itX : itY) {
			itX.draw(target);
		}
	}
	for (int z = 1; z < 4; z++) {
		for (int y = 1; y < 7; y++) {
			for (int x = 3; x < 9; x++) {
				tilesBoard[z][y][x].draw(target);
			}
		}
	}
	for (auto& it : extraTiles)
		it.draw(target);

}


void Board::array_initialize() {
	int i = 0;
	for (auto& it : tileTypes) {
		it = (i++ % 36) + 1;
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(tileTypes, g);
	for (int i = 1; i < 38; i++)
		avalibleTiles.emplace(i,0);
}

void Board::tileInit() {
	int i = 0;
	int s = 0;
	tileInitFunc(0, 12, 0, i, std::vector<int>{0, 3,4, 7});
	tileInitFunc(1, 11, 0, i, std::vector<int>{2,5});
	tileInitFunc(2, 10, 0, i, std::vector<int>{1,6});
	tileInitFunc(3, 9, 1, i, std::vector<int>{1,2,3,4,5,6});
	tileInitFunc(4, 8, 2, i, std::vector<int>{2,3,4,5});
	tileInitFunc(5, 7, 3, i, std::vector<int>{3, 4});

	float y = 3.5;
	s = tileTypes[i++];
	extraTiles[0] = Tile(*tileTextures[s], width, height, ((width + x_space) * -1) + x_pre, (height + y_space) *  y + y_pre, s, true);
	s = tileTypes[i++];
	extraTiles[1] = Tile(*tileTextures[s], width, height, ((width + x_space) * 5.5) + x_pre, (height + y_space) * y + y_pre, s, true);
	s = tileTypes[i++];
	extraTiles[2] = Tile(*tileTextures[s + 37], width, height, ((width + x_space) * 12) + x_pre, (height + y_space) * y + y_pre, s);
	s = tileTypes[i++];
	extraTiles[3] = Tile(*tileTextures[s], width, height, ((width + x_space) * 13) + x_pre, (height + y_space) * y + y_pre, s , true);
	avalibleTiles[extraTiles[0].getType()]++;
	avalibleTiles[extraTiles[1].getType()]++;
	avalibleTiles[extraTiles[3].getType()]++;
}

void Board::tileInitFunc(int begin, int end, int ver, int& iter, std::vector<int> rows) {
	int s;
	for (auto it : rows) {
		for (int i = begin; i < end; i++) {
			s = tileTypes[iter++];
			tilesBoard[ver][it][i] = Tile(*tileTextures[s + 37], width, height, ((width + x_space) * i) + x_pre, (height + y_space) * it + y_pre, s);
		}
	}
}


void Board::checkMovable() {
	Tile* temp = nullptr;
	Tile* upper = nullptr;
	for (int z = 0; z < 3; z++) {
		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 12; x++) {
				temp = &tilesBoard[z][y][x];
				upper = &tilesBoard[z + 1][y][x];
				if (temp->getExist() && !temp->getMovable()) {
					if ((y == 3 || y == 4) && z ==0) {
						if (x == 0) {
							if (!extraTiles[0].getExist()) {
								temp->changeToMov(*tileTextures[temp->getType()]);
								avalibleTiles[temp->getType()]++;
							}
						}
						else if (x == 11) {
							if (!extraTiles[2].getExist()) {
								temp->changeToMov(*tileTextures[temp->getType()]);
								avalibleTiles[temp->getType()]++;
							}
						}
						else {
							if (!upper->getExist() && (!tilesBoard[z][y][x - 1].getExist() || !tilesBoard[z][y][x + 1].getExist())) {
								temp->changeToMov(*tileTextures[temp->getType()]);
								avalibleTiles[temp->getType()]++;
							}
						}
					}
					else {
						if (x == 0 || x == 11) {
							temp->changeToMov(*tileTextures[temp->getType()]);
							avalibleTiles[temp->getType()]++;
						}
						else {
							if (!upper->getExist() && (!tilesBoard[z][y][x - 1].getExist() || !tilesBoard[z][y][x + 1].getExist())) {
								temp->changeToMov(*tileTextures[temp->getType()]);
								avalibleTiles[temp->getType()]++;
							}
						}
					}
				}
			}
		}
	}
	if (!extraTiles[1].getExist()) {
		for (auto& itY : tilesBoard[3])
			for (auto& itX : itY) {
				if (itX.getExist() && !itX.getMovable()) {
					itX.changeToMov(*tileTextures[itX.getType()]);
					avalibleTiles[itX.getType()]++;
				}
			}
	}
	if (!extraTiles[3].getExist() || (!tilesBoard[0][3][11].getExist() && !tilesBoard[0][4][11].getExist())) {
		if (!extraTiles[2].getMovable()) {
			extraTiles[2].changeToMov(*tileTextures[extraTiles[2].getType()]);
			avalibleTiles[extraTiles[2].getType()]++;
		}
	}
	
}

void Board::getMouseClick(int mous_x, int mous_y) {
	for (auto& it : extraTiles) {
		if (it.isInside(sf::Vector2f( mous_x, mous_y )))
			toMatch(&it);
	}
	int z = 4;
	while (z--) {
		for (auto& itY : tilesBoard[z]) {
			for (auto& itX : itY) {
				if (itX.isInside(sf::Vector2f(mous_x, mous_y))) {
					if (!itX.getMovable())
						break;
					else
						toMatch(&itX);

				}
			}
		}
	}
}



void Board::toMatch(Tile* only) {
	only->selectedColor(true);
	if (!selected || selected == only)
		selected = only;
	else if (selected->getType() == only->getType()) {
		removeTiles(selected, only);
		selected = nullptr;
	}
	else {
		selected->selectedColor(false);
		selected = only;
	}
}

const bool Board::isThereMoreMoves() {
	for (auto& it : avalibleTiles)
		if (it.second > 1)
			return true;
	return false;
}

const bool Board::isEmpty() {
	for (auto& it : avalibleTiles)
		if (it.second != 0)
			return false;
	return true;
}

void Board::removeTiles(Tile* first, Tile* second) {
	avalibleTiles[first->getType()] -= 2;
	first->remove();
	second->remove();
	checkMovable();
}
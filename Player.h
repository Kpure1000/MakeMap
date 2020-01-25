#pragma once
#include "Plat.h"
class Player :
	public GameObject {
private:
	vector<Plat>&Plats;
public:

	Player(sf::Sprite& sp, sf::RenderWindow& app,
		std::string const& objecttypename, vector<Plat>&);

public: //  Control

	friend void MoverX(Player& player, sf::Vector2f speed);

	friend void MoverJump(Player& player, sf::RenderWindow& App, time_t& timedata);

	virtual int CollisionCheck();

public: //  Game

	virtual void Draw();

	virtual void SetUp();

	virtual void Update();
};

void MoverX(Player& player, sf::Vector2f speed);

void MoverJump(Player& player, sf::RenderWindow& App, time_t& timedata);


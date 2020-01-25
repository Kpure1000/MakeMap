#pragma once
#include"GameObject.h"
class Plat : public GameObject {
private:
	bool IsCousor;
	bool IsMover;

	vector<Plat>& Plats;

public:

	Plat(sf::Sprite& sp, sf::RenderWindow& app, 
		std::string const& objecttypename, vector<Plat>&);

public: //  Control

	virtual int CollisionCheck();

	void SetCousor(bool);

	void SetMover(bool);

public: //  Game

	virtual void Draw();

	virtual void SetUp();

	virtual void Update();

public:

	Vector2f GetSize();

};


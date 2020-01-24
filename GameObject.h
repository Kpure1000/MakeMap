#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<vector>
#include<thread>
#include<fstream>
#include"AssetManager.h"
class GameObject {
protected:

	//Reference:

	sf::Sprite sprite;
	
	sf::RenderWindow& App;

	std::string ObjectTypeName;

	//MoveControlBuffer

	enum CollisionEvent
	{
		IsLanding = 1,
		IsTop
	};

	sf::Vector2f const MoveSpeed = { 7.0f,7.0f };

	const float Ffkx = 0.01f, Ffky = 0.01f;

	float dx, dy, vx, vy;

	float Ffx, Ffy;

	float newx, newy;

	//Gravity:

	bool IsGravity;
	
	//Draw and Visible:

	bool Visible;
	
	float DrawPriority;
	
	const int MaxPriority = 10;

public: //	Set
	
	GameObject(sf::Sprite sp, sf::RenderWindow& app,
		std::string const& objecttypename);
	
	//GameObject(GameObject const& gameobject);
	
	virtual ~GameObject() {}
	
	void SetTexture(sf::Texture const& texture);
	
	void LoadTextureFromFile(std::string const& name);
	
	void SetPosition(sf::Vector2f const& position);
	
	void SetScale(sf::Vector2f const& scale);
	
	void SetVisible(bool const& visible);

	void SetGravity(bool const& gravity);

public: //  Get
	
	bool IsVisible();
	
	sf::Vector2f GetPosition();

	std::string GetName();

public: //  Control

	void Gravity();

	virtual int CollisionCheck() = 0;

public: //  Game

	virtual void Draw() = 0;

	virtual void SetUp() = 0;

	virtual void Update() = 0;

};

class Objects {
private:
	vector<GameObject>GameObjects;

	string FileName;
	
public:
	Objects(std::string const& filename);

	void SetMap();
	
	void GetMap();
	
};

#include "Plat.h"

Plat::Plat(sf::Sprite& sp, sf::RenderWindow& app, std::string const& objecttypename)
	:GameObject(sp, app, objecttypename) {

}

 //  Control:///////////

int Plat::CollisionCheck() {
	if (newy > App.getSize().y)
	{
		dy = -25.0f;
	}
	return 1;
}

 //  Game://////////////

void Plat::Draw() {
	App.draw(sprite);
}

void Plat::SetUp() {
	newx = sprite.getPosition().x,
		newy = sprite.getPosition().y;
	
	sf::IntRect size = sprite.getTextureRect();
	sprite.setOrigin((float)size.width / 2, (float)size.height / 2);
}

void Plat::Update() {
	newx = sprite.getPosition().x,
		newy = sprite.getPosition().y;

	sf::Vector2f Speed(0, 0);

	Gravity();

	sprite.setPosition(newx, newy);

	Draw();
}
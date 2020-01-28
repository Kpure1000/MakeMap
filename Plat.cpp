#include "Plat.h"

Plat::Plat(sf::Sprite& sp, sf::RenderWindow& app,
	std::string const& objecttypename, vector<Plat>&plats)
	:GameObject(sp, app, objecttypename), Plats(plats) {
	IsCousor = true;
	IsMover = false;
}

 //  Control:///////////

int Plat::CollisionCheck() {
	if (newy >= App.getSize().y)
	{
		newy = (float)App.getSize().y;
		return IsLanding;
	}
	else {
		return IsTop;
	}
}

void Plat::SetCousor(bool setting) {
	IsCousor = setting;
}

void Plat::SetMover(bool setting) {
	IsMover = setting;
}

 //  Game://////////////

void Plat::Draw() {
	float subX = App.getView().getCenter().x - App.getSize().x / 2;
	float subY = App.getView().getCenter().y - App.getSize().y / 2;
	float XR = GetPosition().x + GetSize().x-subX;
	float XL = GetPosition().x - GetSize().x-subX;
	float YD = GetPosition().y + GetSize().y-subY;
	float YU = GetPosition().y - GetSize().y-subY;
	if (XR <= App.getSize().x + 100
		and XL >= -100
		and YD <= App.getSize().y + 100
		and YU >= -100) {
		App.draw(sprite);
	}
}

void Plat::SetUp() {
	newx = sprite.getPosition().x,
		newy = sprite.getPosition().y;
	
	sf::IntRect size = sprite.getTextureRect();
	sprite.setOrigin((float)size.width / 2, (float)size.height / 2);
}

void Plat::Update() {
	//if (IsMover) {
	//	newx = sprite.getPosition().x,
	//		newy = sprite.getPosition().y;
	//}

	Gravity();

	if (IsCousor) {
		Vector2i MousePos = Mouse::getPosition(App);
		float scaleX = App.getView().getSize().x / App.getSize().x;
		float scaleY = App.getView().getSize().y / App.getSize().y;
		float subX = App.getView().getCenter().x - App.getSize().x / 2;
		float subY = App.getView().getCenter().y - App.getSize().y / 2;
		
		newx = App.getView().getCenter().x * (1 - scaleX) + (MousePos.x + subX) * scaleX;

		newy = App.getView().getCenter().y * (1 - scaleY) + (MousePos.y + subY) * scaleY;
	}
	if (IsMover) {
		sprite.setPosition(newx, newy);
	}

	Draw();
}

Vector2f Plat::GetSize() {
	return Vector2f((float)sprite.getTextureRect().width,
		(float)sprite.getTextureRect().height);
}
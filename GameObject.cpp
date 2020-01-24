#include "GameObject.h"
GameObject::GameObject
(sf::Sprite& sp, sf::RenderWindow& app, std::string const& objecttypename)
	:sprite(sp), App(app), ObjectTypeName(objecttypename)
{
	newx = newy = 0;
	dx = dy = vx = vy = 0;
	Ffx = Ffy = 0;
	IsGravity = false;
	Visible = true;
	GameObject::DrawPriority = (float)MaxPriority;
}

//  Set://///////////

void GameObject::SetTexture(sf::Texture const& texture) {
	sprite.setTexture(texture);
}

void GameObject::LoadTextureFromFile(std::string const& name) {
	sprite.setTexture(AssetManager::GetTexture(name));
	sf::IntRect Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.width = AssetManager::GetTexture(name).getSize().x;
	Rect.height = AssetManager::GetTexture(name).getSize().y;
	sprite.setTextureRect(Rect);
}

void GameObject::SetPosition(sf::Vector2f const& position) {
	sprite.setPosition(position);
}

void GameObject::SetScale(sf::Vector2f const& scale) {
	sprite.setScale(scale);
}

void GameObject::SetVisible(bool const& visible) {
	Visible = visible;
}

void GameObject::SetGravity(bool const& gravity) {
	IsGravity = gravity;
}

//  Get:///////////

bool GameObject::IsVisible() {
	return Visible;
}

sf::Vector2f GameObject::GetPosition() {
	return sprite.getPosition();
}

std::string GameObject::GetName() {
	return ObjectTypeName;
}

//  Control:///////////

void GameObject::Gravity() {
	/*if (newy < App.getSize().y) {
		cout << "Check " << newy << endl;
	}*/
	if (!IsGravity) {
		return;
	}

	if (CollisionCheck() == IsTop) {
		dy += GRAVITY; 
	}
	else {
		dy = 0;
	}

	newy += dy;
}


//end

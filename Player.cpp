#include "Player.h"

Player::Player(sf::Sprite& sp, sf::RenderWindow& app,
	std::string const& objecttypename, vector<Plat>&plats)
	:GameObject(sp, app, objecttypename), Plats(plats)
{}

void MoverX(Player& player,sf::Vector2f speed) {
	if (KeyPressing and KeyEvent(Left)) {
		player.newx -= speed.x;
	}
	if (KeyPressing and KeyEvent(Right)) {
		player.newx += speed.x;
	}
}

void MoverJump(Player& player, sf::RenderWindow& App, time_t& timedata) {
	time_t FrameTime = timedata;
	while (App.isOpen()) {
		if (KeyPressing and KeyEvent(Up)) {
			if (player.CollisionCheck() == player.IsLanding) {
				player.dy = -20.0f;
				player.newy += player.dy;
				while (KeyEvent(Up))
					;
			}
		}
	}
}

int Player::CollisionCheck() {
	if (newy >= App.getSize().y) { //  if not landing, JumpBaning 
		newy = (float)App.getSize().y;
		return IsLanding;
	}
	for (auto it = Plats.begin(); it != Plats.end(); it++) {
		float HalfW = it->GetSize().x, HalfH = it->GetSize().y/2;
		float PosX = it->GetPosition().x, PosY = it->GetPosition().y;
		if (GetPosition().x<PosX + 2*HalfW and GetPosition().x>PosX - 2*HalfW
			and GetPosition().y<PosY + HalfH and GetPosition().y>PosY - 2*HalfH
			and dy > 0) {
			newy = (float)(PosY - HalfH);
			return IsLanding;
		}
	}
	return IsTop;
}

void Player::Draw() {
	App.draw(sprite);
}

void Player::SetUp() {
	newx = sprite.getPosition().x;
	newy = sprite.getPosition().y;

	sf::IntRect size = sprite.getTextureRect();
	sprite.setOrigin((float)size.width / 2, (float)size.height);
}

void Player::Update() {
	Gravity();

	thread MoveXThread(MoverX, ref(*this), ref(MoveSpeed));
	MoveXThread.join();

	sprite.setPosition(newx, newy);

	//有可能是在setPosition后，MoveJump进程才检测跳跃
	//证实了
	//解决方法：
	//1.Update的Gravity前不更新newy,nyewx
	//2.

	Draw();
}
#include "Player.h"

Player::Player(sf::Sprite& sp, sf::RenderWindow& app,
	std::string const& objecttypename, vector<Plat>&plats)
	:GameObject(sp, app, objecttypename), Plats(plats){
	isStatic = false;
}

void MoverX(Player& player,sf::Vector2f speed) {
	if (KeyPressing and (KeyEvent(Left) or KeyEvent(A))) {
		player.newx -= speed.x;
	}
	if (KeyPressing and (KeyEvent(Right) or KeyEvent(D))) {
		player.newx += speed.x;
	}
}

void MoverJump(Player& player, sf::RenderWindow& App, time_t& timedata) {
	time_t FrameTime = timedata;
	while (App.isOpen()) {
		if (KeyPressing and (KeyEvent(Up) or KeyEvent(W))) {
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
		float HalfW = it->GetSize().x/2, HalfH = it->GetSize().y/2;
		float PosX = it->GetPosition().x, PosY = it->GetPosition().y;
		if (GetPosition().x <= PosX + 4 * HalfW and GetPosition().x >= PosX - 4 * HalfW
			and
			GetPosition().y <= PosY + HalfH and GetPosition().y >= PosY - 2 * HalfH
			and dy >= 0) {
				newy = (float)(PosY - HalfH);
			return IsLanding;
			//���vector��ĳһ��Plat�����½������ܽ�
			//���Գ�������IsLanding
			//��һ���ʿ������������Զ�������(�����½�)
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

	//�п�������setPosition��MoveJump���̲ż����Ծ
	//֤ʵ��
	//���������
	//1.Update��Gravityǰ������newy,nyewx
	//2.

	Draw();
}
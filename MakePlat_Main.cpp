#include<SFML/Graphics.hpp>
#include"Plat.h"
#include"Player.h"
#include"Control.h"

#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)

void timecontrol(sf::RenderWindow& App, time_t& timedata) {
	while (App.isOpen()) {
		timedata = clock();
		timedata %= LLONG_MAX;
	}
}

string ToString(int num) {
	string tmp = "";
	char ch;
	while (num != 0) {
		ch = num % 10 + '0';
		tmp = ch + tmp;
		num /= 10;
	}
	return tmp;
}

void FrameControl(time_t& CurrentTime, sf::RenderWindow& App) {
	while (App.isOpen()) {
		CurrentTime = clock();
	}
	return;
}

int main() {
	const float AppW = 2000, AppH = 1500;
	RenderWindow App(VideoMode((unsigned int)AppW, (unsigned int)AppH), "WinterGame", CannotResize);
	//App.setFramerateLimit(160);

	AssetManager SourceManager;
	AssetManager::GetTexture(PlatForm);
	AssetManager::GetTexture(Player_f);

	sf::View Player_ca(Vector2f(AppW/2, AppH/2), Vector2f(AppW*1, AppH*1));
	App.setView(Player_ca);

	vector<Plat>Plats;

	Control Con1(App,Plats);

	if (!Con1.OpenPositionFile(PosFile)) {
		Con1.RandomMake();
	}

	sf::Sprite Plat_sp(AssetManager::GetTexture(PlatForm));
	Plat Plat1(Plat_sp, App, "Normal",Plats);
	Plat1.SetGravity(false);
	Plat1.SetScale({ 3.5f,3.5f });

	sf::Sprite Player_sp(AssetManager::GetTexture(Player_f));
	Player Player1(Player_sp, App, "Player1", Plats);
	Player1.SetGravity(true);
	Player1.SetScale({ 3.5f,3.5f });
	Player1.SetPosition({ AppW / 2,0 });

	time_t TimeData = 0;
	thread TimeControl(timecontrol, ref(App), ref(TimeData));

	thread MoveThread(MoverJump, ref(Player1), ref(App));


	Plat1.SetUp();
	Plat1.SetMover(true);

	Player1.SetUp();

	for (auto it = Plats.begin(); it != Plats.end(); it++) {
		it->SetUp();
	}

	sf::Font TDFont;
	TDFont.loadFromFile(_3dfont);
	sf::Text text;
	text.setFont(TDFont);
	text.setFillColor(sf::Color::Red);
	text.setPosition(50, 50);
	string textin;

	time_t StartTime = 0;
	time_t EndTime = 0;

	float Frames = 170.0f;

	long TimeDelay = (long)(1000.0f / Frames);

	StartTime = clock();

	while (App.isOpen()) {

		StartTime = clock();

		Event ev;
		while (App.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				App.close();
			}
			else if (KeyPressing and KeyEvent(Escape)) {
				App.close();
			}
		}
		App.clear(Color(0,0,0, 0));

		Plat1.Update();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			Plat tmp = Plat1;
			tmp.SetCousor(false);
			Plats.push_back(tmp);
			while (Mouse::isButtonPressed(Mouse::Left))
				;
		}
		
		if (KeyEvent(LControl)) {
			if (!Plats.empty() and KeyEvent(Z)) {
				Plats.pop_back();
				while (KeyEvent(Z))
					;
			}
		}

		for (auto it = Plats.begin(); it != Plats.end(); it++) {
			it->Update();
		}

		Player1.Update();

		Player_ca.setCenter(Player1.GetPosition());
		App.setView(Player_ca);

		App.draw(text);

		App.display();

		while (EndTime - StartTime <= TimeDelay) {
			EndTime = clock();
		}

		EndTime = clock();

		int frametmp = (int)(1000.0f / (EndTime - StartTime));
		textin = ToString(frametmp);
		textin += " fps";
		text.setString(textin);
		text.setPosition({ Player1.GetPosition().x - AppW / 2 + 50,
			Player1.GetPosition().y - AppH / 2 + 50 });
	}

	MoveThread.join();
	TimeControl.join();

	Con1.SavePositionFile();

	return 0;
}

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

int main() {
	const float AppW = 2000, AppH = 1500;
	RenderWindow App(VideoMode((unsigned int)AppW, (unsigned int)AppH), "WinterGame", CannotResize);
	App.setFramerateLimit(160);

	AssetManager SourceManager;
	AssetManager::GetTexture(PlatForm);
	AssetManager::GetTexture(Player_f);

	sf::View Player_ca(Vector2f(AppW/2, AppH/2), Vector2f(AppW, AppH));
	App.setView(Player_ca);

	vector<Plat>Plats;

	Control Con1(App,Plats);
	//Con1.RandomMake();

	Con1.OpenPositionFile(PosFile);

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

	thread MoveThread(MoverJump, ref(Player1), ref(App), ref(TimeData));


	Plat1.SetUp();
	Plat1.SetMover(true);

	Player1.SetUp();

	for (auto it = Plats.begin(); it != Plats.end(); it++) {
		it->SetUp();
	}

	while (App.isOpen()) {
		Event ev;
		while (App.pollEvent(ev)) {
			if (ev.type == Event::Closed) {
				App.close();
			}
			else if (KeyPressing and KeyEvent(Escape)) {
				App.close();
			}
		}
		App.clear(Color(180, 180, 200, 0));

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

		App.display();
	}

	MoveThread.join();
	TimeControl.join();

	Con1.SavePositionFile();

	return 0;
}

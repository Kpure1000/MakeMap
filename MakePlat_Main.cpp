#include<SFML/Graphics.hpp>
#include"Plat.h"
#include"Player.h"
#include"Control.h"

#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)

int main() {
	const float AppW = 1200, AppH = 1200;
	RenderWindow App(VideoMode((unsigned int)AppW, (unsigned int)AppH), "WinterGame", CannotResize);
	App.setFramerateLimit(120);

	sf::View Player_ca;
	App.setView(Player_ca);

	AssetManager SourceManager;
	AssetManager::GetTexture(PlatForm);
	AssetManager::GetTexture(Player_f);

	vector<Plat>Plats;

	Control Con1(App,Plats);
	//Con1.RandomMake();

	sf::Sprite Plat_sp(AssetManager::GetTexture(PlatForm));
	Plat Plat1(Plat_sp, App, "Normal");

	thread MouseControlThread(MouseControl, ref(App), ref(Plat1));
	Plat1.SetUp();

	//for (auto it = Plats.begin(); it != Plats.end(); it++) {
	//	it->SetUp();
	//}

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

		//for (auto it = Plats.begin(); it != Plats.end(); it++) {
		//	it->Update();
		//}

		Plat1.Update();

		App.display();
	}

	MouseControlThread.join();
	return 0;
}

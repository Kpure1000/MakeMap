#include<SFML/Graphics.hpp>
#include"Plat.h"
#include"Player.h"

#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)

int main() {
	const float AppW = 1200, AppH = 1200;
	RenderWindow App(VideoMode((unsigned int)AppW, (unsigned int)AppH), "WinterGame", CannotResize);
	App.setFramerateLimit(120);

	sf::View Player_ca;
	App.setView(Player_ca);

	vector<GameObject>Plats;

	AssetManager SourceManager;

	sf::Sprite Plat1_sp(AssetManager::GetTexture(PlatForm));

	sf::Sprite Player1_sp(AssetManager::GetTexture(Player_f));

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

		App.display();

	}

	return 0;
}

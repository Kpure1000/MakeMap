#include"Control.h"



void MouseControl(sf::RenderWindow& App, Plat& Plat1) {
	while (App.isOpen()) {
		Plat1.SetGravity(true);
		Plat1.SetScale({ 7,7 });

		Vector2i MousePos = Mouse::getPosition(App);
		Plat1.SetPosition(Vector2f(MousePos.x, MousePos.y));
	}
}

void Control::RandomMake() {
	srand(time(NULL));
	for (int i = 0; i < 20; i++) {
		Plat Plat1(Plat_sp, App, "Normal");
		Plat1.SetGravity(false);
		Plat1.SetScale({ 7,7 });
		float x = rand() % (int)AppW + 0.01f * (float)(rand() % (int)AppW);
		float y = rand() % (int)AppH + 0.01f * (float)(rand() % (int)AppH);
		Plat1.SetPosition({ x,y });
		Plats.push_back(Plat1);
	}

}

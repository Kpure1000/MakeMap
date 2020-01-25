#include"Control.h"



void MouseControl(Control& control, sf::RenderWindow& App, Plat& Plat1) {
	while (App.isOpen()) {
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Plat tmp = Plat1;
			tmp.SetCousor(false);
			control.Plats.push_back(tmp);
		}
	}
}

void Control::RandomMake() {
	srand(time(NULL));
	for (int i = 0; i < 20; i++) {
		Plat Plat1(Plat_sp, App, "Normal", Plats);
		Plat1.SetGravity(false);
		Plat1.SetScale({ 7,7 });
		float x = rand() % (int)AppW + 0.01f * (float)(rand() % (int)AppW);
		float y = rand() % (int)AppH + 0.01f * (float)(rand() % (int)AppH);
		Plat1.SetPosition({ x,y });
		Plats.push_back(Plat1);
	}

}

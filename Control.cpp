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
	/*srand(time(NULL));
	for (int i = 0; i < 20; i++) {
		Plat Plat1(Plat_sp, App, "Normal", Plats);
		Plat1.SetGravity(false);
		Plat1.SetScale({ 7,7 });
		float x = rand() % (int)AppW + 0.01f * (float)(rand() % (int)AppW);
		float y = rand() % (int)AppH + 0.01f * (float)(rand() % (int)AppH);
		Plat1.SetPosition({ x,y });
		Plats.push_back(Plat1);
	}*/
	const int N = 60;
	for (int i = 0; i < N; i++) {
		Plat Platn(Plat_sp, App, "Normal", Plats);
		Platn.SetGravity(false);
		Platn.SetScale({ 3.5f,3.5f });
		Platn.SetPosition({ AppW * i / N,AppH });
		Plats.push_back(Platn);
		if ((int)i % 2 == 0) {
			Plat PlatnL(Plat_sp, App, "Normal", Plats);
			PlatnL.SetGravity(false);
			PlatnL.SetScale({ 3.5f,3.5f });
			PlatnL.SetPosition({ 0,AppH * i / N });
			Plats.push_back(PlatnL);
			Plat PlatnR(Plat_sp, App, "Normal", Plats);
			PlatnR.SetGravity(false);
			PlatnR.SetScale({ 3.5f,3.5f });
			PlatnR.SetPosition({ AppW ,AppH * i / N });
			Plats.push_back(PlatnR);
		}
	}

}

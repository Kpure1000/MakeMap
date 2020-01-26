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
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 20; i++) {
		Plat Plat0(Plat_sp, App, "Normal", Plats);
		Plat0.SetGravity(false);
		Plat0.SetScale({ 3.5f,3.5f });
		float x = rand() % (int)AppW + 0.01f * (float)(rand() % (int)AppW);
		float y = rand() % (int)AppH + 0.01f * (float)(rand() % (int)AppH);
		Plat0.SetPosition({ x,y });
		Plats.push_back(Plat0);
	}
	const int N = 60;
	for (int i = 0; i < N; i++) {
		Plat Platn(Plat_sp, App, "Normal", Plats);
		Platn.SetGravity(false);
		Platn.SetScale({ 3.5f,3.5f });
		Platn.SetPosition({ AppW * i / N,AppH });
		Plats.push_back(Platn);
		if ((int)i % 3 == 0) {
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

void Control::OpenPositionFile(string const& filename) {
	PositionFileName = filename;
	ifstream InPos(filename);
	if (InPos.is_open()) {
		string objecttypename;
		bool gravity;
		Vector2f scale;
		Vector2f position;
		while (!InPos.eof()) {

			InPos >> objecttypename 
				>> gravity 
				>> scale.x >> scale.y 
				>> position.x >> position.y;

			Plat Platn(Plat_sp, App, "Normal", Plats);
			Platn.SetGravity(gravity);
			Platn.SetScale(scale);
			Platn.SetPosition(position);
			Plats.push_back(Platn);
		}
		InPos.close(); return;
	}
	InPos.close(); return;
}

void Control::SavePositionFile(string const& filename) {
	PositionFileName = filename;

	ofstream OutPos(PositionFileName);
	if (OutPos.is_open()) {
		for (auto it = Plats.begin(); it != Plats.end(); it++) {
			OutPos << it->GetName() << " "
				<< it->GetGravity() << " "
				<< it->GetScale().x << " " << it->GetScale().y << " "
				<< it->GetPosition().x << " " << it->GetPosition().y << endl;
		}
		OutPos.close();
		return;
	}
	OutPos.close();
	return;
}

void Control::SavePositionFile() {
	ofstream OutPos(PositionFileName);
	if (OutPos.is_open()) {
		for (auto it = Plats.begin(); it != Plats.end(); it++) {
			OutPos << it->GetName() << " "
				<< it->GetGravity() << " "
				<< it->GetScale().x << " " << it->GetScale().y << " "
				<< it->GetPosition().x << " " << it->GetPosition().y << endl;
		}
		OutPos.close();
		return;
	}
	OutPos.close();
	return;
}


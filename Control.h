#include"Plat.h"

class Control {
private:
	sf::RenderWindow& App;
	float AppW, AppH;

	vector<Plat>& Plats;

	sf::Sprite Plat_sp;

	string PositionFileName;

public:
	Control(sf::RenderWindow& app, vector<Plat>& plats)
		:App(app), Plats(plats) {
		Plat_sp.setTexture(AssetManager::GetTexture(PlatForm));
		AppW = (float)App.getSize().x, AppH = (float)App.getSize().y;
	}

	void OpenPositionFile(string const& filename);

	void RandomMake();

	friend void MouseControl(Control&, sf::RenderWindow&, Plat&);

	void SavePositionFile(string const& filename);

	void SavePositionFile();

};

void MouseControl(Control&, sf::RenderWindow&, Plat&);
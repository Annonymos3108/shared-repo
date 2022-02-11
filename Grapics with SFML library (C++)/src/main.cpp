#include "Menu.h"
#include "Polyhedron_Lightning\PLmenu.h"

#include <thread>
#include <iostream>
		
using namespace std;

void menuButton();
void menuButton2();

int main(void) 
{	
	sfm::Menu mainmenu;
	sfm::MenuOption opt("Polyhedron lightning", menuButton);
	mainmenu.addOption(opt);
	sfm::MenuOption opt2("Exit", menuButton2);
	mainmenu.addOption(opt2);
	mainmenu.setLayout(sfm::MenuLayout::VerticleCentered);
	mainmenu.setBackground("sfml-logo.png");
	sf::Font font;
	sf::Text text;
	font.loadFromFile("ARIAL.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color(0, 45, 109));
	mainmenu.setTemplateText(text);
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 800), "Polyhedron lightning");
	mainmenu.display(window);
	window.close();
	return EXIT_SUCCESS;
}

void menuButton() {
	std::thread(&Polyhedron_Lightning::PolyhedronLight_menu).detach();
}

void menuButton2() {
	std::cout << "\nExiting...\n";
    std::exit(EXIT_SUCCESS);
}

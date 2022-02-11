#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include "../OBJ_Loader.h"
#include <fstream>
#include "myMesh.h"
#include <string>
#include "PLmenu.h"

namespace Polyhedron_Lightning
{

int& getWinWidth()
{
	static int WINDOW_SIZE_X{900};
	return WINDOW_SIZE_X;
}

int& getWinHeight()
{
	static int WINDOW_SIZE_Y{900};
	return WINDOW_SIZE_Y;
}


void makeHint(sf::Vector2i p, sf::RenderWindow& windowHint)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error!";
	}

	windowHint.setPosition(sf::Vector2i(p.x - 70, p.y));

	sf::String angleInput;
	sf::Text angleText;
	angleText.setFont(font);
	angleText.setFillColor(sf::Color::Black);
	angleText.setString("\nLeft/Right/Up/Down arrow key - rotate poyhedron\n"
							"1,2,3,4 - switch between different polyhedrons\n");
	angleText.setPosition(20.f, 20.f);
	angleText.setCharacterSize(20);


	windowHint.clear(sf::Color::Yellow);
	windowHint.draw(angleText);
	windowHint.display();
}

void changePolyhedron(std::vector<myMesh>& entity1, std::string sPoly)
{
	entity1.clear();
	objl::Loader Loader;

	int offsetX = getWinWidth()/2;
	int offsetY = getWinHeight()/2;

	bool loadout = Loader.LoadFile(sPoly);

	if (loadout)
	{
		for (size_t i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = Loader.LoadedMeshes[i];

			entity1.push_back(myMesh(curMesh.Indices.size()/3, offsetX, offsetY));

			for (size_t j = 0; j < curMesh.Indices.size(); j += 3)
			{
				entity1[i].add(j / 3, curMesh.Vertices[curMesh.Indices[j]].Position.X, curMesh.Vertices[curMesh.Indices[j]].Position.Y,
											curMesh.Vertices[curMesh.Indices[j]].Position.Z,
										curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
											curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z,
										curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
											curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z);
			}
		}
	}
	else
	{
		throw std::runtime_error("obj file not found");
	}
}

int PolyhedronLight_menu(void)
try
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(getWinWidth(), getWinHeight()), "lightening of polyhedrons", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	sf::RenderWindow windowHint(sf::VideoMode(550, 100), "Hint", sf::Style::Titlebar);
	makeHint(window.getPosition(),windowHint);

	std::string s1("icosidodecahedron.obj"); 	
	std::string s2("octahedron.obj");			
	std::string s3("tetrahedron.obj");			
	std::string s4("cube.obj");
	std::vector<myMesh> entity1;
	changePolyhedron(entity1, s3);
	
    for (;window.isOpen();)
    {
        sf::Event event;
		for(;window.pollEvent(event);)
        {
			switch(event.type)
			{

				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{

					}
					break;

				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Left)
					{

					}
					break;

				case sf::Event::KeyPressed:
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					 {
						for (auto& it: entity1)
							it.rotateSurface(it.M_R_Y_RIGHT);
					 }
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						for (auto& it: entity1)
							it.rotateSurface(it.M_R_Y_LEFT);
					}
					 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					 {
						 for (auto& it: entity1)
						 	it.rotateSurface(it.M_R_X_UP);
					 }
					 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					 {
						 for (auto& it: entity1)
							 it.rotateSurface(it.M_R_X_DOWN);
					 }
					 switch(event.key.code)
 					{
 						case sf::Keyboard::Key::Num1:
 							changePolyhedron(entity1, s1);
 						break;

 						case sf::Keyboard::Key::Num2:
 							changePolyhedron(entity1, s2);
 						break;

 						case sf::Keyboard::Key::Num3:
 							changePolyhedron(entity1, s3);
 						break;
						
						case sf::Keyboard::Key::Num4:
 							changePolyhedron(entity1, s4);
 						break;

 						default:;
 					}
					break;

				default:

					break;

			}

		}

		window.clear(sf::Color::Black);
		for (const auto& it: entity1) window.draw(it);
		for (auto& it: entity1)	 it.lightning();
		window.display();

	}

    return EXIT_SUCCESS;

}
catch(std::exception& e) {
	std::cerr << "\nCrashed. Caught exception: " << e.what() << '\n';
	return EXIT_FAILURE;

}

}



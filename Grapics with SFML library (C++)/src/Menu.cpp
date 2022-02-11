#include "Menu.h"
using namespace sfm;

const MenuLayout MenuLayout::VerticleCentered	=	MenuLayout(50, sf::Vector2f(0.50, 0.5));
const MenuLayout MenuLayout::VerticleLeft		=	MenuLayout(50, sf::Vector2f(0.25, 0.5));
const MenuLayout MenuLayout::VerticleRight		=	MenuLayout(50, sf::Vector2f(0.75, 0.5));

MenuLayout::MenuLayout(unsigned int spacing, const sf::Vector2f &origin) {
	setSpacing(spacing);
	setOrigin(origin);
}


MenuLayout::MenuLayout(const MenuLayout &other) {
	this->spacing = other.spacing;
	this->origin = other.origin;
}


void MenuLayout::setSpacing(unsigned int spacing) {
	this->spacing = spacing;
}


void MenuLayout::setOrigin(const sf::Vector2f &origin) {
	this->origin = origin;
	if(this->origin.x > 1.0) {
		this->origin.x = 1.0;
	}
	if(this->origin.y > 1.0) {
		this->origin.y = 1.0;
	}
}


void MenuLayout::apply(std::vector<sf::Text> &options,
		sf::Vector2u windowSize) {
	if(options.size() == 0) { return; } 

	sf::Vector2f orig; 
	orig.x = windowSize.x * this->origin.x;
	orig.y = windowSize.y * this->origin.y;
	
	int n = options.size();
	auto osize = options[0].getGlobalBounds(); 
	if(n % 2) { 
		orig.y = orig.y - (int)(n / 2) * (osize.height + spacing);
	}
	else { 
		orig.y = orig.y - (spacing/2.0f) - (osize.height/2.0f) - (n/2 - 1)*(spacing+osize.height);
	}

	for(sf::Text &text : options) { 
		sf::FloatRect rect = text.getLocalBounds();
		
		text.setOrigin(rect.left + rect.width/2.0f,
				rect.top + rect.height/2.0f);
		text.setPosition(orig); 
		orig.y += osize.height + spacing; 
	}
}

void Menu::display(sf::RenderWindow &window) {
	sf::Sprite bg;
	bg.setTexture(background);
	bg.setScale(window.getSize().x / (float)background.getSize().x,
			window.getSize().y / (float)background.getSize().y);
	std::vector<sf::Text> texts;
	sf::Text t = this->templateText;
	for(const auto &o : options) {
		t.setString(o.getText());
		texts.push_back(t);
	}

	window.clear(sf::Color::White);
	window.draw(bg); 
	layout.apply(texts, window.getSize()); 
	for(auto &t : texts) { 
		window.draw(t);
	}
	window.display();

	bool finished = false;
	int i = 0;
	sf::Vector2i mousePos;
	sf::Clock clock;
	while(!finished) {
		sf::Event e;
		while(window.pollEvent(e)) {
			switch(e.type) {
				case sf::Event::Closed:
					finished = true;
					if(exitCallback) { exitCallback(); }
					break;
				case sf::Event::Resized:
				case sf::Event::GainedFocus:
					window.clear(sf::Color::White);
					window.draw(bg); 
					for(auto &t : texts) {
						window.draw(t);
					}
					window.display();
					break;
				case sf::Event::MouseButtonReleased:
					for(i = 0; i < texts.size(); i++) {
						if(texts[i].getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
							
							options[i].select();
							if (i==texts.size()-1) finished = true;
							break;
						}
					}
					break;
				default:
					break;
			}
		}
		sf::sleep(sf::milliseconds(100));
		if(timeout > sf::seconds(0.0) && clock.getElapsedTime() >= timeout) {
			
			finished = true;
			if(timeoutCallback) { timeoutCallback(); }
		}
	}
}


void Menu::addOption(const MenuOption &option) {
	options.push_back(option);
}


void Menu::clearOptions() {
	options.clear();
}


void Menu::setBackground(const std::string &path) {
	background.loadFromFile(path);
}


void Menu::setTimeout(sf::Time timeout, std::function<void(void)> callback) {
	this->timeout = timeout;
	this->timeoutCallback = callback;
}


void Menu::setExitCallback(std::function<void(void)> callback) {
	exitCallback = callback;
}


void Menu::setLayout(MenuLayout layout) {
	this->layout = layout;
}


void Menu::setTemplateText(const sf::Text &t) {
	templateText = t;
}

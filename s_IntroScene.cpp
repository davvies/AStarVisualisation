#include "s_IntroScene.h"
#include <SFML/Graphics.hpp>


s_IntroScene::s_IntroScene() {}

void s_IntroScene::SceneStart() 
{	
	sf::Texture mainHomeScreen; 

	if (!mainHomeScreen.loadFromFile("mainMenu.png")) {

		std::cerr<<"\n\ncould not load main menu\n\n";

	}

	sf::Sprite sprite;

	sprite.setTexture(mainHomeScreen);

	m_SpriteBuffer.push_back(sprite);
}

void s_IntroScene::SceneTick(float deltaT) {  }

void s_IntroScene::RenderBuffer(sf::RenderWindow& inputWindow)
{
	sf::Texture mainHomeScreen;

	if (!mainHomeScreen.loadFromFile("mainMenu.png")) {

		std::cerr << "\n\ncould not load main menu\n\n";

	}
	for (auto& textInstance : m_SpriteBuffer) {

		//drawtext window
		textInstance.setTexture(mainHomeScreen);
		inputWindow.draw(textInstance);

	}

}

void s_IntroScene::PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange)
{
	//no point in polling for any other input than mouse clicks (there's only a button in the scene)
	if (eventInstance.type != sf::Event::MouseButtonPressed) 
		return; 

	sf::Vector2i m_position = sf::Mouse::getPosition(*inputWindow);

	//if the begin button is clicked launch the visualisation
	if (BeginButtonClicked(m_position))
		triggerLevelChange = true; 
	
}

bool s_IntroScene::BeginButtonClicked(const sf::Vector2i& worldCoordinates)
{
	return worldCoordinates.x>=200 && worldCoordinates.x<=283 && worldCoordinates.y>=437&&worldCoordinates.y<=474; 
}

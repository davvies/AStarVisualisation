#include "s_IntroScene.h"
#include <SFML/Graphics.hpp>


s_IntroScene::s_IntroScene() {

	CacheTextures();

}

void s_IntroScene::SceneStart() 
{	

	m_backgroundSPRI.setTexture(m_mainHomeScreenTEX);

	m_SpriteBuffer.push_back(m_backgroundSPRI);
}

void s_IntroScene::SceneTick(float deltaT) {  }

void s_IntroScene::RenderBuffer(sf::RenderWindow& inputWindow)
{

	for (auto& textInstance : m_SpriteBuffer) {

		//drawtext window
		textInstance.setTexture(m_mainHomeScreenTEX);
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
	if (btn_beginSimulation.HasBeenClicked(inputWindow))
		triggerLevelChange = true; 
	
}

void s_IntroScene::CacheTextures()
{
	if (!m_mainHomeScreenTEX.loadFromFile("mainMenu.png")) {

		std::cerr << "\n\ncould not load main menu\n\n";

	}
}

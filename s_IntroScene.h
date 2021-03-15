#pragma once
#include "Scene.h"
#include <vector>

class s_IntroScene : public Scene {

public:
	s_IntroScene();

	//caching main menu texture
	 void SceneStart() override;

	 void SceneTick(float deltaT) override;

	 //displaying starting screen
	 void RenderBuffer(sf::RenderWindow& inputWindow) override;

	 //checking for button clicks to begin simulation
	 void PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange) override;

private: 
	//sprites needed for rendering
	std::vector<sf::Sprite> m_SpriteBuffer;

	//launch the game
	bool BeginButtonClicked(const sf::Vector2i& worldCoordinates);
};
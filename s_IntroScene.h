#pragma once
#include "Scene.h"
#include "UIButton.h"
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

	void CacheTextures() override;

	//sprites needed for rendering
	std::vector<sf::Sprite> m_SpriteBuffer;

	UIButton btn_beginSimulation{ 200, 283, 437, 474 };

	sf::Texture m_mainHomeScreenTEX;
	sf::Sprite m_backgroundSPRI;

};
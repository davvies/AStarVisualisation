#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "s_IntroScene.h"
#include "s_VisualScene.h"
#include "WindowMetaData.h"

class GameManager {

public: 
	GameManager();
	~GameManager();

	//container for starting the path finding
	int RunVisualisation();

private:
	enum class PlayState { GAMEBEGIN, GAMERUNNNING, GAMESTOPPED };

	//main game loop function
	void GlobalUpdate();

	//init levels in memory 
	void InitInstanceVars();

	void InitWindow();

	//get a reference to the active scene
	void GetActiveScene();

	//if in need update scene
	void UpdateScene();

	//current scene
	PlayState m_activeGameState;

	//render window objects often take up substantial stack memory
	sf::RenderWindow* m_windowPTR;

	//scene references
	s_IntroScene m_index;
	s_VisualScene m_visual;
	
	Scene* m_currentScenePTR;

	bool m_shouldUpdateScene;

	const sf::Color c_gray{ 210, 210, 210 };

};
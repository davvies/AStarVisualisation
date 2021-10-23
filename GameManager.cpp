#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
	InitInstanceVars();
	InitWindow();
}

GameManager::~GameManager()
{
	std::cout << "\n ENDING.. \n";

	delete m_windowPTR;
	delete m_currentScenePTR;
}

int GameManager::RunVisualisation()
{
	GlobalUpdate();

	return EXIT_SUCCESS;
}

void GameManager::GlobalUpdate()
{
	GetActiveScene();
	m_currentScenePTR->SceneStart();
	m_shouldUpdateScene = false; 

	//used in the tracking of deltaT
	sf::Clock internalClock;

	while (m_windowPTR->isOpen())
	{

		if (m_shouldUpdateScene) {
			UpdateScene();
			m_shouldUpdateScene = false; 
		}

		//Update if needed
		GetActiveScene();

		sf::Event event;

		while (m_windowPTR->pollEvent(event))
		{
			m_currentScenePTR->PollEvents(event, m_windowPTR, m_shouldUpdateScene);

			if (event.type == sf::Event::Closed)
				m_windowPTR->close();

		}

		m_currentScenePTR->SceneTick(internalClock.restart().asSeconds());

		m_windowPTR->clear(c_gray);
		m_currentScenePTR->RenderBuffer(*m_windowPTR);
		m_windowPTR->display();
	 }

	}

void GameManager::InitInstanceVars()
{
	//default level is the begin screen
	m_activeGameState = PlayState::GAMEBEGIN;

	m_windowPTR = nullptr; 
	m_currentScenePTR = nullptr;
}

void GameManager::InitWindow()
{
	this->m_windowPTR = new sf::RenderWindow(sf::VideoMode(X_RESOLUTION, Y_RESOLUTION),
		"A* Visualisation Tool", sf::Style::Titlebar | sf::Style::Close);

	s_IntroScene m_index();
}

void GameManager::GetActiveScene()
{
	//Update scene relative to active one
	switch (m_activeGameState) {

	case PlayState::GAMEBEGIN:
		m_currentScenePTR = &m_index;
		break;

	case PlayState::GAMERUNNNING:
		m_currentScenePTR = &m_visual;
		break;

	default: 
		std::cout << "\n *FATAL ERROR* - No state found \n";
		break;
	}
}

void GameManager::UpdateScene()
{
	m_activeGameState = PlayState::GAMERUNNNING;

	m_visual.SceneStart();
}


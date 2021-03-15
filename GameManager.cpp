#include "GameManager.h"
#include <iostream>

constexpr auto X_RESOULTION = 488;
constexpr auto Y_RESOULTION = 489;
const sf::Color c_gray(210, 210, 210);

GameManager::GameManager()
{
	InitInstanceVars();
	InitWindow();
}

GameManager::~GameManager()
{
	std::cout << "\n ENDING.. \n";
}

int GameManager::RunVisualisation()
{
	GlobalUpdate();

	return EXIT_SUCCESS;
}

void GameManager::GlobalUpdate()
{
	GetActiveScene();
	p_currentScene->SceneStart();
	m_shouldUpdateScene = false; 

	//used in the tracking of deltaT
	sf::Clock internalClock;

	while (p_window->isOpen())
	{
		if (m_shouldUpdateScene) {
			UpdateScene();
			m_shouldUpdateScene = false; 
		}

		//Update if needed
		GetActiveScene();

		sf::Event event;

		while (p_window->pollEvent(event))
		{
			p_currentScene->PollEvents(event, p_window, m_shouldUpdateScene);

			if (event.type == sf::Event::Closed)
				p_window->close();

		}
		p_currentScene->SceneTick(internalClock.restart().asSeconds());

		p_window->clear(c_gray);
		p_currentScene->RenderBuffer(*p_window);
		p_window->display();
	 }


	}

void GameManager::InitInstanceVars()
{
	//default level is the begin screen
	m_activeGameState = PlayState::GAMEBEGIN;

	p_window = nullptr; 
	p_currentScene = nullptr;
}

void GameManager::InitWindow()
{
	this->p_window = new sf::RenderWindow(sf::VideoMode(X_RESOULTION, Y_RESOULTION),
		"A* Visualisation Tool", sf::Style::Titlebar | sf::Style::Close);
	s_IntroScene m_index();
}

void GameManager::GetActiveScene()
{
	//Update scene realtive to active one
	switch (m_activeGameState) {

	case PlayState::GAMEBEGIN:
		p_currentScene = &m_index;
		break;

	case PlayState::GAMERUNNNING:
		p_currentScene = &m_visual;
		break;

	default: 
		std::cout << "*FATAL ERROR* - No state found";
		break;
	}
}

void GameManager::UpdateScene()
{
	m_activeGameState = PlayState::GAMERUNNNING;
	m_visual.SceneStart();
}


#include "Scene.h"
#include <iostream>

//Implementation for polymorphic scenes

void Scene::SceneTick(const float deltaT)
{
	std::cerr << "\n**ERROR** - Scene Tick not implemented\n";
}

void Scene::RenderBuffer(sf::RenderWindow& inputWindow)
{
	std::cerr << "\n**ERROR** - Render buffer not implemented\n";
}

void Scene::PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange)
{
	std::cerr << "\n**ERROR** - Poll events not specified\n";
}

void Scene::SceneStart()
{
	std::cerr << "\n**ERROR** - Scene start not specified\n";
}


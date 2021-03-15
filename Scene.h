#pragma once
#include <vector>
#include<iostream>
#include <SFML/Graphics.hpp>

//Base polymorphic class for scenes
class Scene {
public: 

	//run every frame
	virtual void SceneTick(const float deltaT);

	//draw to the screen
	virtual void RenderBuffer(sf::RenderWindow& inputWindow);

	//take input
	virtual void PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange);

	//called on first frame
	virtual void SceneStart();

};
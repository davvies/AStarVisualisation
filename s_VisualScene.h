#pragma once
#include "Scene.h"
#include "Board.h"
#include <vector>

//This scene renders the path-finding to a window
class s_VisualScene : public Scene {

public:
	s_VisualScene();

	void SceneStart() override;

	/*
	the scene tick handles the countdown behaviour
	and logic for switching between different check boxes
	*/
	void SceneTick(float deltaT) override;

	/*
	the render buffer handles all tiles and textures that relate
	to the algorithm
	*/
	void RenderBuffer(sf::RenderWindow& inputWindow) override;

	//All input during the algorithm execution is calculated within this function
	void PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange) override;


private:

	//has the algorithm started
	bool hasBeginBeenClicked(sf::RenderWindow* window);

	//check to see if mouse input is in the second checkbox
	bool inCheckBoxTwoRegion(sf::RenderWindow* window);

	//check to see if mouse input is in the first checkbox
	bool inCheckBoxOneRegion(sf::RenderWindow* window);

	std::vector<sf::Sprite> m_SpriteBuffer;

	//current active board
	Board m_gameBoard;

	/*
	when false the selection screen is shown,
	when true the grid is displayed
	*/
	bool m_showNoPathFound = false;

	//used in tracking 
	float m_timer = 0;

	bool m_hasChosenOptions = false;

	/*
	checkbox one denotes direction type 
	checkbox two denotes distance type
	*/
	bool m_checkBoxOneSelected = false;	
	bool m_checkBoxTwoSelected = false;
};
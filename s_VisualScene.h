#pragma once
#include "Scene.h"
#include "Board.h"
#include "UIButton.h"
#include "WindowMetaData.h"
#include <vector>

//This scene renders the path-finding to a window
class s_VisualScene : public Scene {

	enum class MouseHold { LEFT_CLICK, MIDDLE_CLICK, RIGHT_CLICK };


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

	void CacheTextures() override;

	std::vector<sf::Sprite> m_SpriteBuffer;

	//current active board
	Board m_gameBoard { sf::Vector2f { X_RESOLUTION, Y_RESOLUTION } };

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

	bool m_draggingMouse = false;
	
	MouseHold m_currentDragKey; 

	sf::Sprite m_tickboxOneSPR;
	sf::Sprite m_tickboxTwoSPR;
	sf::Sprite m_renderSPR;

	sf::Texture m_homeTEX;
	sf::Texture m_flagTEX;
	sf::Texture m_obstacleTEX;
	sf::Texture m_errorTEX;
	sf::Texture m_selectArgsTEX;
	sf::Texture m_tickTEX;

	//reset-screen timer
	const float m_timeToWait = 3; 

	//on screen buttons
	UIButton btn_allowDiag { 210, 243, 153, 187 };
	UIButton btn_useManhattenDistance { 210, 243, 362, 392 };
	UIButton btn_beginSimulation { 416, 464, 463, 479 };

};
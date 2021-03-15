#include "s_VisualScene.h"

s_VisualScene::s_VisualScene() {}

void s_VisualScene::SceneStart() {}

sf::Sprite tickboxOne;
sf::Sprite tickboxTwo;

sf::Texture home;
sf::Texture flag;
sf::Texture obsticle;

const float timeToWait = 3;

void s_VisualScene::SceneTick(float deltaT) {

	m_gameBoard.m_allowDiagonals = m_checkBoxOneSelected;
	m_gameBoard.m_useManhatten = m_checkBoxTwoSelected;

	/*
	if the generated path has been successful there is not point in calculating the
	time remaining to reset
	*/
	if (m_gameBoard.m_runSuccessful != false)
		return;

	if (m_timer < timeToWait) {

		m_timer += deltaT;

	}
	else {
		//allocate a new board
		Board newBoard;
		m_gameBoard = newBoard;
		m_gameBoard.m_allowDiagonals = m_checkBoxOneSelected;
		m_gameBoard.m_useManhatten = m_checkBoxTwoSelected;

		//begin reset timer
		m_timer = 0;
	}

}

bool s_VisualScene::inCheckBoxOneRegion(sf::RenderWindow* window) {
	//get mouse position relative to screen window (i.e. not desktop)
	sf::Vector2i mouseP = sf::Mouse::getPosition(*window);

	return mouseP.x > 210 && mouseP.x < 243 && mouseP.y > 153 && mouseP.y < 187;
}

bool s_VisualScene::inCheckBoxTwoRegion(sf::RenderWindow* window) {
	//get mouse position relative to screen window (i.e. not desktop)
	sf::Vector2i mouseP = sf::Mouse::getPosition(*window);

	return mouseP.x > 210 && mouseP.x < 243 && mouseP.y > 362 && mouseP.y < 392;
}

bool s_VisualScene::hasBeginBeenClicked(sf::RenderWindow* window) {

	sf::Vector2i mouseP = sf::Mouse::getPosition(*window);

	return mouseP.x > 416 && mouseP.x < 464 && mouseP.y > 463 && mouseP.y < 479;
}

void s_VisualScene::RenderBuffer(sf::RenderWindow& inputWindow)
{
	//if the user is yet to choose their algorithm arguments
	if (m_hasChosenOptions == false) {

		sf::Texture selectArgs;

		if (!selectArgs.loadFromFile("selectArgs.png")) {

			std::cerr << "\n\nArgs could not be selected\n\n";

		}

		sf::Texture tick;

		if (!tick.loadFromFile("tick.png")) {

			std::cerr << "\n\ntick could not be selected\n\n";

		}

		//sprite used in rendering
		sf::Sprite renderSprite;

		tickboxOne.setTexture(tick);
		renderSprite.setTexture(selectArgs);
		tickboxTwo.setTexture(tick);

		//Absolute position
		tickboxOne.setPosition(216, 158);
		tickboxTwo.setPosition(216, 367);

		inputWindow.draw(renderSprite);

		//Update tickbox relative to tick state
		if (m_checkBoxOneSelected) {

			inputWindow.draw(tickboxOne);

		}

		if (m_checkBoxTwoSelected) {

			inputWindow.draw(tickboxTwo);

		}

		return;

	}


	//Draw the path if the algorithm has run successfully
	if (m_gameBoard.m_runSuccessful) {

		for (auto& node : m_gameBoard.grid) {

			inputWindow.draw(node.graphic);

		}

	}
	else {

		//render 'resetting' screen if the path is not found
		sf::Texture error;

		if (!error.loadFromFile("noPathFound.png")) {

			std::cerr << "\n\ncould not load main menu\n\n";

		}

		sf::Sprite renderSprite;

		renderSprite.setTexture(error);

		inputWindow.draw(renderSprite);
	}
}

void s_VisualScene::PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange)
{
	if (eventInstance.type == sf::Event::MouseButtonPressed && m_hasChosenOptions == false) {

		//Update checkboxs if cursor has clicked one
		if (inCheckBoxOneRegion(inputWindow))
			m_checkBoxOneSelected = !m_checkBoxOneSelected;


		if (inCheckBoxTwoRegion(inputWindow))
			m_checkBoxTwoSelected = !m_checkBoxTwoSelected;


		if (hasBeginBeenClicked(inputWindow))
			m_hasChosenOptions = true;

		return;
	}

	//if the grid is active..
	if (eventInstance.type == sf::Event::MouseButtonPressed && m_hasChosenOptions == true) {

		sf::Texture nullTexture;

		float mouseRoundDownX = sf::Mouse::getPosition(*inputWindow).x - 2;
		float mouseRoundDownY = sf::Mouse::getPosition(*inputWindow).y - 2;

		//round down mouse coordinates to grid space
		int numX = (int)mouseRoundDownX / 32.47;
		int numY = (int)mouseRoundDownY / 32.47;

		//place home (starting point)
		if (eventInstance.mouseButton.button == sf::Mouse::Middle && m_gameBoard.grid[(numX * 15) + numY].isObsticle == false && &m_gameBoard.grid[(numX * 15) + numY] != m_gameBoard.endNode) {
			if (m_gameBoard.startNode == nullptr) {

				if (!home.loadFromFile("home.png")) {

					std::cerr << "failed to load home texture\n";

				}

				//set and update home point (via texture and board data)
				m_gameBoard.grid[(numX * 15) + numY].graphic.setTexture(&home);
				m_gameBoard.startNode = &m_gameBoard.grid[(numX * 15 + numY)];
			}
			else {

				//update home node and texture
				m_gameBoard.startNode->graphic.setTexture(&nullTexture);
				m_gameBoard.grid[(numX * 15) + numY].graphic.setTexture(&home);
				m_gameBoard.startNode = &m_gameBoard.grid[(numX * 15 + numY)];

			}
		}

		//place rock (obsticle) 
		if (eventInstance.mouseButton.button == sf::Mouse::Left) {

			if (!obsticle.loadFromFile("ob.png")) {
				std::cerr << "failed to load obstacle texture\n";
			}

			//update board position
			m_gameBoard.grid[(numX * 15) + numY].graphic.setTexture(&obsticle);
			m_gameBoard.grid[(numX * 15) + numY].isObsticle = true;
		}

		//set flag texture
		if (eventInstance.mouseButton.button == sf::Mouse::Right && m_gameBoard.grid[(numX * 15) + numY].isObsticle == false && &m_gameBoard.grid[(numX * 15) + numY] != m_gameBoard.startNode) {

			if (m_gameBoard.endNode == nullptr) {

				if (!flag.loadFromFile("flag.png")) {

					std::cerr << "failed to load flag\n";

				}

				//update flag texture and flag meta data within board
				m_gameBoard.grid[(numX * 15) + numY].graphic.setTexture(&flag);
				m_gameBoard.endNode = &m_gameBoard.grid[(numX * 15 + numY)];

			}
			else {

				//update flag
				m_gameBoard.endNode->graphic.setTexture(&nullTexture);
				m_gameBoard.grid[(numX * 15) + numY].graphic.setTexture(&flag);
				m_gameBoard.endNode = &m_gameBoard.grid[(numX * 15 + numY)];

			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {

		//generate
		m_gameBoard.PerformAStarSearch();
		m_gameBoard.ColourOptimalPath();

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		
		//reset
		Board newBoard; 
		m_gameBoard = newBoard;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {

		//return to argument menu
		m_hasChosenOptions = false;
		Board newBoard;
		m_gameBoard = newBoard;
	}
}

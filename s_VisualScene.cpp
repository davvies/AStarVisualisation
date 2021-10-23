#include "s_VisualScene.h"

s_VisualScene::s_VisualScene() {

	m_tickboxOneSPR.setPosition(216, 158);
	m_tickboxTwoSPR.setPosition(216, 367);

	CacheTextures();
}

void s_VisualScene::SceneStart() {}

void s_VisualScene::SceneTick(float deltaT) {

	m_gameBoard.m_allowDiagonals = m_checkBoxOneSelected;
	m_gameBoard.m_useManhatten = m_checkBoxTwoSelected;

	/*
	if the generated path has been successful there is no point in calculating the
	time remaining to reset
	*/
	if (m_gameBoard.m_runSuccessful != false)
		return;

	if (m_timer < m_timeToWait) {

		m_timer += deltaT;

	}
	else {

		m_gameBoard.Reset(m_checkBoxOneSelected, m_checkBoxTwoSelected);
		m_showNoPathFound = false;
		m_timer = 0;
	}

}

void s_VisualScene::RenderBuffer(sf::RenderWindow& inputWindow)
{
	//if the user is yet to choose their algorithm arguments
	if (m_hasChosenOptions == false) {
	
		m_tickboxOneSPR.setTexture(m_tickTEX);
		m_renderSPR.setTexture(m_selectArgsTEX);
		m_tickboxTwoSPR.setTexture(m_tickTEX);

		inputWindow.draw(m_renderSPR);

		//Update tickbox relative to tick state
		if (m_checkBoxOneSelected) {

			inputWindow.draw(m_tickboxOneSPR);

		}

		if (m_checkBoxTwoSelected) {

			inputWindow.draw(m_tickboxTwoSPR);

		}

		return;

	}


	//Draw the path if the algorithm has run successfully
	if (m_gameBoard.m_runSuccessful) {

		for (auto& node : m_gameBoard.m_gridArr) {

			inputWindow.draw(node.graphic);
		}

	}
	else {

		//render 'resetting' screen if the path is not found

		m_renderSPR.setTexture(m_errorTEX);
		inputWindow.draw(m_renderSPR);
	}
}

void s_VisualScene::PollEvents(sf::Event& eventInstance, sf::RenderWindow* inputWindow, bool& triggerLevelChange)
{
	if (eventInstance.type == sf::Event::MouseButtonPressed && m_hasChosenOptions == false) {

		//Update check boxes if cursor has clicked one
		if (btn_allowDiag.HasBeenClicked(inputWindow))
			m_checkBoxOneSelected = !m_checkBoxOneSelected;


		if (btn_useManhattenDistance.HasBeenClicked(inputWindow))
			m_checkBoxTwoSelected = !m_checkBoxTwoSelected;


		if (btn_beginSimulation.HasBeenClicked(inputWindow))
			m_hasChosenOptions = true;

		return;
	}

	if (eventInstance.type == sf::Event::MouseButtonReleased) {
		m_draggingMouse = false;
	} 

	if (eventInstance.type == sf::Event::MouseButtonPressed) {
		m_draggingMouse = true; 

		switch (eventInstance.mouseButton.button) {

		case sf::Mouse::Middle:
			
			m_currentDragKey = MouseHold::MIDDLE_CLICK;

			break;

		case sf::Mouse::Left:

			m_currentDragKey = MouseHold::LEFT_CLICK;

			break;

		case sf::Mouse::Right:

			m_currentDragKey = MouseHold::RIGHT_CLICK;

			break;

		 }
	}

	std::cout << m_draggingMouse;
	//if the grid is active..
	if (m_draggingMouse && m_hasChosenOptions == true) {

		float mouseRoundDownX = sf::Mouse::getPosition(*inputWindow).x;
		float mouseRoundDownY = sf::Mouse::getPosition(*inputWindow).y;

		//round down mouse coordinates to grid space
		int numX = (int)mouseRoundDownX / m_gameBoard.GetTileSize().x; //cell width
		int numY = (int)mouseRoundDownY / m_gameBoard.GetTileSize().y; //cell height

		//place home (starting point)
		if (m_currentDragKey == MouseHold::MIDDLE_CLICK && m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)].isObsticle == false && &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)] != m_gameBoard.m_endNodePTR) {
			if (m_gameBoard.m_startNodePTR == nullptr) {

				//set and update home point (via texture and board data)
				m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY,numX)].graphic.setTexture(&m_homeTEX);
				m_gameBoard.m_startNodePTR = &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)];
			}
			else {

				//update home node and texture
				m_gameBoard.m_startNodePTR->graphic.setTexture(nullptr);
				m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)].graphic.setTexture(&m_homeTEX);
				m_gameBoard.m_startNodePTR = &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)];

			}
		}


		//place rock (obstacle) 
		if (m_currentDragKey == MouseHold::LEFT_CLICK  ) {

			//update board position
			m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY,numX)].graphic.setTexture(&m_obstacleTEX);
			m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY,numX)].isObsticle = true;
		}

		//set flag texture
		if (m_currentDragKey == MouseHold::RIGHT_CLICK && m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)].isObsticle == false && &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)] != m_gameBoard.m_startNodePTR) {

			if (m_gameBoard.m_endNodePTR == nullptr) {

				//update flag texture and flag meta data within board
				m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)].graphic.setTexture(&m_flagTEX);
				m_gameBoard.m_endNodePTR = &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)];

			}
			else {

				//update flag
				m_gameBoard.m_endNodePTR->graphic.setTexture(nullptr);
				m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)].graphic.setTexture(&m_flagTEX);
				m_gameBoard.m_endNodePTR = &m_gameBoard.m_gridArr[m_gameBoard.Index1D(numY, numX)];

			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && m_gameBoard.m_startNodePTR && m_gameBoard.m_endNodePTR) {

		//generate
		m_gameBoard.PerformAStarSearch();
		m_gameBoard.ColourOptimalPath();

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		
		m_gameBoard.Reset(m_checkBoxOneSelected, m_checkBoxTwoSelected);
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {

		//return to argument menu
		m_hasChosenOptions = false;

		m_gameBoard.Reset(m_checkBoxOneSelected, m_checkBoxTwoSelected);
	}
}

void s_VisualScene::CacheTextures()
{
	if (!m_homeTEX.loadFromFile("home.png")) {

		std::cerr << "failed to load home texture\n";

	}

	if (!m_obstacleTEX.loadFromFile("ob.png")) {

		std::cerr << "failed to load obstacle texture\n";

	}

	if (!m_flagTEX.loadFromFile("flag.png")) {

		std::cerr << "failed to load flag\n";

	}

	if (!m_errorTEX.loadFromFile("noPathFound.png")) {

		std::cerr << "\n\ncould not load main menu\n\n";

	}

	if (!m_tickTEX.loadFromFile("tick.png")) {

		std::cerr << "\n\ntick could not be selected\n\n";

	}

	if (!m_selectArgsTEX.loadFromFile("selectArgs.png")) {

		std::cerr << "\n\nArgs could not be selected\n\n";

	}

	if (!m_selectArgsTEX.loadFromFile("selectArgs.png")) {

		std::cerr << "\n\nArgs could not be selected\n\n";

	}

	if (!m_tickTEX.loadFromFile("tick.png")) {

		std::cerr << "\n\ntick could not be selected\n\n";

	}
}

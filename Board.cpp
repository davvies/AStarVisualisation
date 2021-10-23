#include "Board.h"
#include <iostream>
#include <cmath>


Board::Board(sf::Vector2f windowRes)
{
	//init standard board
	for (int i = 0; i < rowsC; i++) {
		for (int y = 0; y < colsC; y++) {

			auto& givenNode = m_gridArr[i * rowsC + y];

			givenNode.x = i;
			givenNode.y = y;

			givenNode.graphic.setFillColor(m_gray);

			givenNode.graphic.setOutlineThickness(1);

			givenNode.graphic.setOutlineColor({ sf::Color::Black });

		    m_tileSize = { float(windowRes.x / rowsC), float(windowRes.y / colsC)  };

			givenNode.graphic.setSize(m_tileSize);

			givenNode.graphic.setPosition((y * givenNode.graphic.getSize().x), i* givenNode.graphic.getSize().x );
			
		}
	}

	int maxElement = (rowsC * colsC) - 1;
}

void Board::PerformAStarSearch()
{
	bool endFound = false;

	m_openNodePTRList.push_back(m_startNodePTR);

	while (!endFound && m_startNodePTR && m_endNodePTR ) {

		if (m_openNodePTRList.size() > 0) {

			int lowestIndex = 0;

			for (int i = 0; i < m_openNodePTRList.size(); i++) {

				if (m_openNodePTRList[i]->f < m_openNodePTRList[lowestIndex]->f) {

					lowestIndex = i;

				}
			}

			//get reference to current node with the last F score (best first)
			auto current = m_openNodePTRList[lowestIndex];

			if (current == m_endNodePTR) {
				//get the path
				Node* temp = current;

				while (temp->previous != nullptr) {

					//create optimal path
					m_optimalPathPTRList.push_back(current);
					m_optimalPathPTRList.push_back(temp->previous);
					temp = temp->previous;

				}

				endFound = true; 

				return;
			}

			m_openNodePTRList.erase(m_openNodePTRList.begin() + lowestIndex);
			m_closedNodePTRList.push_back(current);

			std::vector<Node*> localNodes;

			//search local nodes

			if (current->x < rowsC-1) {
				localNodes.push_back(&m_gridArr[Index1D((current->x + 1), current->y)]);
			}

			if (current->x > 0) {
				localNodes.push_back(&m_gridArr[Index1D((current->x - 1), current->y)]);
			}

			if (current->y > 0) {
				localNodes.push_back(&m_gridArr[Index1D(current->x,(current->y - 1))]);
			}

			if (current->y < colsC-1) {
				localNodes.push_back(&m_gridArr[Index1D(current->x,(current->y + 1))]);
			}

			//consider diagonals in case of argument chosen
			if (m_allowDiagonals) {
				if (current->y > 0 && current->x > 0) {
					localNodes.push_back(&m_gridArr[Index1D((current->x - 1),(current->y - 1))]);
				}

				if (current->y > 0 && current->x < (rowsC-1)) {
					localNodes.push_back(&m_gridArr[Index1D((current->x + 1),(current->y - 1))]);
				}

				if (current->x < (rowsC-1) && current->y < (colsC-1)) {
					localNodes.push_back(&m_gridArr[Index1D((current->x + 1), (current->y + 1))]);
				}

				if (current->x > 0 && current->y < (colsC-1)) {
					localNodes.push_back(&m_gridArr[Index1D((current->x - 1),(current->y + 1))]);
				}

			}

			for (auto& neighbour : localNodes) {

				//if not visited the neighbour and its not an obstacle...
				if (neighbour->isObsticle==false && std::count(m_closedNodePTRList.begin(), m_closedNodePTRList.end(), neighbour) == 0) {

					//may be slightly problematic for full precision as diagonals are usually longer away
					int tentativeG = neighbour->g + 1;

					bool goingOnNewPath = false; 

					if (std::count(m_openNodePTRList.begin(), m_openNodePTRList.end(), neighbour) > 0) {

						//using the neighbours g to decide to trek through a path
						if (tentativeG < neighbour->g) {

							neighbour->g = tentativeG;
							goingOnNewPath = true;

						}

					}
					else {

						neighbour->g = tentativeG;
						goingOnNewPath = true;
						m_openNodePTRList.push_back(neighbour);

					}
					if (goingOnNewPath) {

						//update the node f(n) for the seen node 
						neighbour->h = OptimalNodeHeuristic(neighbour, m_endNodePTR);
						neighbour->f = neighbour->g + neighbour->h;
						neighbour->previous = current;
					}

				}
			}
		}
		else {
			
			//NO PATH HAS BEEN FOUND
			m_runSuccessful = false;
			std::cout << "stopped";
			//freeze algorithm
			endFound = true;

			return;
		}
	}
}

void Board::ColourOptimalPath()
{
	//colour different lists

	for (auto& node : m_closedNodePTRList) {

		if(node != m_startNodePTR || node != m_endNodePTR)
			node->graphic.setFillColor(sf::Color::Yellow);

	}

	for (auto& node : m_openNodePTRList) {

		if (node != m_startNodePTR || node != m_endNodePTR)
			node->graphic.setFillColor(sf::Color::Cyan);

	}

	for (auto& node : m_optimalPathPTRList) {

		if (node != m_startNodePTR || node != m_endNodePTR)
			node->graphic.setFillColor(sf::Color::Red);

	}

}

float Board::OptimalNodeHeuristic(Node* n_One, Node* n_Two)
{
	//if using Manhattan return absolute difference
	if(m_useManhatten) 
		return float(abs(n_One->x - n_Two->x) + abs(n_One->y - n_Two->y));

	//else return euclidean distance
	return sqrt(pow(n_Two->x - n_One->x, 2) + pow(n_Two->y - n_One->y, 2) * 1.0);

}

void Board::Reset(bool allowDiagonals, bool useManhattenDistance)
{
	m_allowDiagonals = allowDiagonals;
	m_useManhatten = useManhattenDistance;

	sf::Texture defaultTexture;

	for (auto& n : m_gridArr) {

		n.graphic.setFillColor(m_gray);
		n.graphic.setTexture(nullptr);
		n.isObsticle = false; 
		n.h = 0;
		n.g = 0; 
		n.f = 0;
		n.previous = nullptr;
	}
	
	m_startNodePTR = nullptr; 
	m_endNodePTR = nullptr;

	m_openNodePTRList.clear();
	m_closedNodePTRList.clear();
	m_optimalPathPTRList.clear();

	m_runSuccessful = true;
}

sf::Vector2f Board::GetTileSize() const
{
	return m_tileSize;
}

int Board::Index1D(int x, int y) const
{
	return x * rowsC + y;
}






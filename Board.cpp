#include "Board.h"
#include <iostream>
#include <cmath>

constexpr auto ROWS = 15;
constexpr auto COLS =  15;

const sf::Color Cgray(210, 210, 210);

//X RES CHANGED BY ONE IN GAME MANAGER, TO FIX - CHANGE X RES IN GAME MANAGER BY ONE
Board::Board()
{
	//init standard board
	for (int i = 0; i < ROWS; i++) {
		for (int y = 0; y < ROWS; y++) {
		 auto& givenNode = grid[i * ROWS + y];
			givenNode.x = i;
			givenNode.y = y;
			givenNode.graphic.setFillColor(Cgray);
			givenNode.graphic.setOutlineThickness(1);
			givenNode.graphic.setOutlineColor({ sf::Color::Black });
			givenNode.graphic.setSize({ 32.47,32.47});
			givenNode.graphic.setPosition(i * 32.47+1, y * 32.47+2 );
			
		}
	}

	int maxElement = (ROWS * COLS) - 1;
}

void Board::PerformAStarSearch()
{
	bool endFound = false;

	//open nodes always start with first one
	openNodeList.push_back(startNode);

	while (endFound == false && startNode !=nullptr && endNode != nullptr) {

		if (openNodeList.size() > 0) {

			int lowestIndex = 0;

			for (int i = 0; i < openNodeList.size(); i++) {

				if (openNodeList[i]->f < openNodeList[lowestIndex]->f) {

					lowestIndex = i;

				}
			}

			//get reference to current node with the lost F score (best first)
			auto current = openNodeList[lowestIndex];

			if (current == endNode) {
				//get the path
				Node* temp = current;

				while (temp->previous != nullptr) {

					//create optimal path
					optimalPath.push_back(current);
					optimalPath.push_back(temp->previous);
					temp = temp->previous;

				}

				endFound = true; 

				return;
			}
			openNodeList.erase(openNodeList.begin() + lowestIndex);
			closedNodeList.push_back(current);

			std::vector<Node*> localNodes;

			//search local nodes

			if (current->x < 14) {
				localNodes.push_back(&grid[(current->x + 1) * ROWS + current->y]);
			}

			if (current->x > 0) {
				localNodes.push_back(&grid[(current->x - 1) * ROWS + current->y]);
			}

			if (current->y > 0) {
				localNodes.push_back(&grid[current->x * ROWS + (current->y - 1)]);
			}

			if (current->y < 14) {
				localNodes.push_back(&grid[current->x * ROWS + (current->y + 1)]);
			}

			//consider diagonals in case of argument chosen
			if (m_allowDiagonals) {
				if (current->y > 0 && current->x > 0) {
					localNodes.push_back(&grid[(current->x - 1) * ROWS + (current->y - 1)]);
				}

				if (current->y > 0 && current->x < 14) {
					localNodes.push_back(&grid[(current->x + 1) * ROWS + (current->y - 1)]);
				}

				if (current->x < 14 && current->y < 14) {
					localNodes.push_back(&grid[(current->x + 1) * ROWS + (current->y + 1)]);
				}

				if (current->x > 0 && current->y < 14) {
					localNodes.push_back(&grid[(current->x - 1) * ROWS + (current->y + 1)]);
				}

			}

			for (auto& neighbour : localNodes) {

				//if not visited the neighbour and its not an obstacle...
				if (neighbour->isObsticle==false && std::count(closedNodeList.begin(), closedNodeList.end(), neighbour) == 0) {

					//may be slightly problematic for full precision as diagonals are usually longer away
					int tentativeG = neighbour->g + 1;

					bool goingOnNewPath = false; 

					if (std::count(openNodeList.begin(), openNodeList.end(), neighbour) > 0) {

						if (tentativeG < neighbour->g) {

							neighbour->g = tentativeG;
							goingOnNewPath = true;

						}

					}
					else {

						neighbour->g = tentativeG;
						goingOnNewPath = true;
						openNodeList.push_back(neighbour);

					}
					if (goingOnNewPath) {

						//update the node f(n) for the seen node 
						neighbour->h = OptimalNodeHeuristic(neighbour, endNode);
						neighbour->f = neighbour->g + neighbour->h;
						neighbour->previous = current;
					}

				}
			}
		}
		else {
			
			//NO PATH HAS BEEN FOUND
			
			m_runSuccessful = false;

			endFound = true;

			return;
		}
	}
}

void Board::ColourOptimalPath()
{
	//colour different lists

	for (auto& node : closedNodeList) {

		if(node != startNode || node != endNode)
			node->graphic.setFillColor(sf::Color::Yellow);

	}

	for (auto& node : openNodeList) {

		if (node != startNode || node != endNode)
			node->graphic.setFillColor(sf::Color::Cyan);

	}

	for (auto& node : optimalPath) {

		if (node != startNode || node != endNode)
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




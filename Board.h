#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

const auto rowsC = 15;
const auto colsC = 15;

//Conceptual RxC container holding sprites, positions and features of path finding
class Board {

	struct Node {
		//coordinates
		int x = 0;

		int y = 0; 

		//g + h
		int f = 0;

		//distance from start
		int g = 0; 

		//distance to go (heuristic) 
		int h = 0; 

		//node instance graphic (bomb texture etc.) 
		sf::RectangleShape graphic; 

		//used when tracking the final path
		Node* previous = nullptr; 

		bool isObsticle = false; 
	};

public:
	Board(sf::Vector2f windowRes);

	//primary container for running the algorithm
	void PerformAStarSearch();

	//set fill colours for rendering after search
	void ColourOptimalPath();

	//return distance measure relative to given heuristic
	float OptimalNodeHeuristic(Node* n_One, Node* n_Two);

	//node tracking
	Node m_gridArr[rowsC*colsC];

	//To avoid stack allocation and copy assignments the board is cleared internally
	void Reset(bool allowDiagonals, bool useManhattenDistance);

	int Index1D(int x, int y) const;

	sf::Vector2f GetTileSize() const;

	//parent -> child tracking for backtracking
	Node* m_startNodePTR = nullptr;
	Node* m_endNodePTR = nullptr;

	//meta deta
	bool m_runSuccessful = true;
	bool m_allowDiagonals = false; 
	bool m_useManhatten = false;

private:

	const sf::Color m_gray { 210, 210, 210 };

	sf::Vector2f m_tileSize;

	//node tracking
	std::vector<Node*> m_openNodePTRList; //active fringe
	std::vector<Node*> m_closedNodePTRList; //visited nodes
	std::vector<Node*> m_optimalPathPTRList; //completed final path

};

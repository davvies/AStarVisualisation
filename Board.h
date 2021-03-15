#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Board {

	struct Node {
		//coordinates
		int x;
		int y; 

		//g + h
		int f = 0;

		//distance from start
		int g = 0; 

		//distance to go (heuristic) 
		int h = 0; 

		sf::RectangleShape graphic; 

		//used when tracking the final path
		Node* previous = nullptr; 

		bool isObsticle = false; 
	};

public:
	Board();

	//primary container for running the algorithm
	void PerformAStarSearch();

	//set fill colours for rendering after search
	void ColourOptimalPath();

	//return distance measure realtive to given heuristic
	float OptimalNodeHeuristic(Node* n_One, Node* n_Two);

	//grid size
	Node grid[15 * 15]; 

	//node tracking
	std::vector<Node*> openNodeList;
	std::vector<Node*> closedNodeList;
	std::vector<Node*> optimalPath;

	//parent -> child tracking for backtracking
	Node* startNode = nullptr;
	Node* endNode = nullptr;

	//meta deta
	bool m_runSuccessful = true;
	bool m_allowDiagonals = false; 
	bool m_useManhatten = false;
};
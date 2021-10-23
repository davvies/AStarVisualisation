#pragma once

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
/*
*	Note:
	Due to project time constraints buttons do not include sprites,
	As such all buttons in the project are apart of the background textures.
*/
class UIButton {

private:

	//Should the class be extended to have sprites, one coordinate integer v2 will suffice
	sf::Vector2<int> m_rangeCoordinatesX;
	sf::Vector2<int> m_rangeCoordinatesY;

public:

	UIButton(int xLeft, int xRight, int yLeft, int yRight);

	bool HasBeenClicked(sf::RenderWindow* window) const;

};

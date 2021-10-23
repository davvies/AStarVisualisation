#include "UIButton.h"

UIButton::UIButton(int xLeft, int xRight, int yLeft, int yRight)
{
	m_rangeCoordinatesX.x = xLeft;
	m_rangeCoordinatesX.y = xRight;

	m_rangeCoordinatesY.x = yLeft; 
	m_rangeCoordinatesY.y = yRight;

}

bool UIButton::HasBeenClicked(sf::RenderWindow* window) const
{
	auto mouseP = sf::Mouse::getPosition(*window);

	return mouseP.x > m_rangeCoordinatesX.x && mouseP.x < m_rangeCoordinatesX.y
		&& mouseP.y > m_rangeCoordinatesY.x && mouseP.y < m_rangeCoordinatesY.y;
}

#include <iostream>
#include "GameManager.h"

//Launch the visualisation
int main()
{
	//Heap is used due to having high memory footprint (72 Kilobytes) from the stack size of SFML rendering windows
	GameManager* p_gm = new GameManager; 

	p_gm->RunVisualisation();

	delete p_gm;


	return EXIT_SUCCESS;
}
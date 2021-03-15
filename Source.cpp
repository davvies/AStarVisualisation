#include <iostream>
#include "GameManager.h"

//Launch the visualisation
int main()
{
	//Heap is used due to algorithm having high memory footprint
	GameManager* p_gm = new GameManager; 
	p_gm->RunVisualisation();
	delete p_gm;

	return EXIT_SUCCESS;
}
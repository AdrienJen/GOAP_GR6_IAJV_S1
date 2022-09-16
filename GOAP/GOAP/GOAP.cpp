#include "GameMaster.h"

int main()
{
	GameMaster gm{};

	//initialize
	gm.StartGame();

	//main prog
	gm.UdapteGame();

	//destruction of all elements
	gm.DeleteGame();

	return EXIT_SUCCESS;
}
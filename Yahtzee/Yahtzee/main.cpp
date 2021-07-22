
#include "Game.h"

int main()
{
	srand(time(NULL));
	Game g;
	while (g.game_over())
	{
		g.turn();
	}
	g.finish();
}


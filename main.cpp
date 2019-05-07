#include <iostream>
#include <cstdint>
#include <vector>



#include "game_session.h"
#include "my_virus.h"

int main(int argc, char** argv) {

	int epoches = 15;
	if (argc > 1) {
		epoches = atoi(argv[1]);
	}

	auto v = new MyVirus(1);
	GameSession gs(10,10);
	gs.add_player(new MyVirus(1), std::make_pair(0,0));
	gs.add_player(new MyVirus(2), std::make_pair(9,9));

	for (int i = 0; i < epoches; i++) {
		gs.tick();
	}
	gs.print();
	return 0;
}

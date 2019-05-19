#include <iostream>
#include <cstdint>
#include <vector>



#include "game_session.h"
#include "my_virus.h"

int main(int argc, char** argv) {

	int epoches = -1;
	if (argc > 1) {
		epoches = atoi(argv[1]);
	}

	// Создаём здесь свой вирус
	auto v = new MyVirus(1);
	// Создаём игровое поле
	GameSession gs(10,10);
	// Добавляем на поле вирусы
	gs.add_player(new MyVirus(1), std::make_pair(0,0));
	gs.add_player(new MyVirus(2), std::make_pair(9,9));

	if (epoches == -1) {
		while (!gs.is_finished())
			gs.tick();
	}
	else {
		for (int i = 0; i < epoches; i++) {
			gs.tick();
		}
	}
	gs.print();
	
	std::cout << "Winner is " << gs.winner()+1 << std::endl;

	return 0;
}

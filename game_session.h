#ifndef GAME_SESSION
#define GAME_SESSION

#include <vector>
#include <map>
#include <algorithm>

#include "base_virus.h"

class GameSession {
public:
	GameSession(int32_t height, int32_t width) :
 		m_height(height),
		m_width(width)
	{
		m_gamefield = new BaseVirus**[m_height];

		for (int i = 0; i < m_height; i++)
			m_gamefield[i] = new BaseVirus*[m_width];
	}
	void add_player(BaseVirus* player_virus, std::pair<int32_t, int32_t> coordinate) {
		if (m_gamefield[coordinate.first][coordinate.second] == nullptr) {
			players_board[player_virus->get_id()] = std::vector<std::pair<int32_t, int32_t>>(1, coordinate);
			m_gamefield[coordinate.first][coordinate.second] = player_virus;
		}
	}

	int32_t get_height() {
		return m_height;
	}
	int32_t get_width() {
		return m_width;
	}	

	void tick() {
		for (auto players_viruses : players_board)
			for (auto virus_coordinate : players_viruses.second)
				make_step(virus_coordinate);
	}
	
	void make_step(std::pair<int32_t, int32_t> coordinate) {
		
		int32_t x = coordinate.first;
		int32_t y = coordinate.second;
		typedef std::pair<int32_t, int32_t> coord;

		std::vector<BaseVirus*> env;

		BaseVirus padding(BaseVirus::PADDING_ID);
		for (int32_t i = -1; i <= 1; i++) {
			for (int32_t j = -1; j <= 1; j++) {
				if (is_correct(y+i,x+j))
					env.push_back(m_gamefield[y+i][x+j]);
				else
					env.push_back(&padding);
			}
		}

		std::pair<int, int> action=m_gamefield[coordinate.first][coordinate.second]->get_action(env);
		if (action.first == BaseVirus::Actions::None)
			return;

		y += action.second/(3) - 1;
		x += action.second%(3) - 1;

		if (m_gamefield[y][x] == nullptr) {
			m_gamefield[y][x] = m_gamefield[coordinate.first][coordinate.second];
			auto p_y = coordinate.first;
			auto p_x = coordinate.second;
			players_board[m_gamefield[p_y][p_x]->get_id()].push_back(std::make_pair(y,x));
		}
	}

	void print() {
		for (int32_t i = 0; i < m_height; i++) {
			for (int32_t j = 0; j < m_width; j++) {
				if (m_gamefield[i][j] == nullptr)
				 std::cout << "0";
				else	
					std::cout << m_gamefield[i][j]->get_id();
				std::cout	<< " ";
			}
			std::cout << std::endl;
		}
	}

	bool is_finished() {
		for (uint32_t i = 0; i < m_height; i++)
			for (uint32_t j = 0; j < m_width; j++)
				if (m_gamefield[i][j] == nullptr)
					return false;
		return true;
	}

	int32_t winner() {
		auto res = std::max_element(players_board.begin(), players_board.end(),
															  [] (auto const& lhs, auto const& rhs) {
															 		return lhs.second.size() > rhs.second.size();
															  });
		return res->first;
	}

private:
	bool is_correct(int32_t y, int32_t x) {
		return y >= 0 && y < m_height && x >= 0 && x < m_width;
	}
	
	std::map<int32_t, std::vector<std::pair<int32_t, int32_t>>> players_board;

	BaseVirus*** m_gamefield;

	int32_t m_height;
	int32_t m_width;
};


#endif //GAME_SESSION

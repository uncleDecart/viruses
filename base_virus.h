#ifndef BASE_VIRUS
#define BASE_VIRUS

#include <vector>

class BaseVirus {
public:
	enum Actions : int {
		None,
		Conqure
	};

	static const int32_t PADDING_ID = -1;

	BaseVirus(int32_t id) :
		m_id(id)
	{}

	virtual std::pair<int, int> get_action(std::vector<BaseVirus*> env) { 
		std::cout << "WE HAVE SLICE HERE!" << std::endl;
		return std::make_pair(BaseVirus::Actions::None, 0);
	}

	int32_t get_id() {
		return m_id;
	}

protected:
	int32_t m_id;
};

#endif //BASE_VIRUS

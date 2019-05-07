#ifndef MY_VIRUS
#define MY_VIRUS

#include "base_virus.h"

class MyVirus : public BaseVirus {
public:
	MyVirus(int32_t id) :
		BaseVirus(id)
	{}

	virtual std::pair<int, int> get_action(std::vector<BaseVirus*> env) { 
		auto len = env.size();
		for (auto i = 0; i < len; i++) 
			if (env[i] == nullptr)
				return std::make_pair(BaseVirus::Actions::Conqure, i);
		return std::make_pair(BaseVirus::Actions::None, 0);
	}
};

#endif //MY_VIRUS

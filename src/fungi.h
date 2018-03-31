#include "state.h"
#include <string>
class Fungi
{
	State state;
	bool debug;
	public:
	Fungi(const std::string& code);
	void run();
	void setDebug();
	State& getState();
};

#include "state.h"
#include <string>
class Fungi
{
	State state;
	public:
	Fungi(const std::string& code);
	void run();
};

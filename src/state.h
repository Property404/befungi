#include <stack>
#include <vector>
#include <string>
#define BEFUNGE_ROWS 25
#define BEFUNGE_COLUMNS 80

// Represents the state of the program
// Both its stack and its program memory can be interacted with
class State{
		// Program counters for each axis
		int pcx, pcy;
		// And directional
		enum Direction {UP, DOWN, LEFT, RIGHT};
		Direction direction;

		std::stack<int> stack;
		char program[BEFUNGE_ROWS][BEFUNGE_COLUMNS];

	public:
		
		State();
		State(const std::string& code);
		void setCode(const std::string&);
		// PC movement
		void right();
		void left();
		void up();
		void down();
		// Moves not only m spaces in <<direction>>, but skips any following
		// nulls
		void move(int m=1);

		// Stack manipulation
		void push(int);
		int pop();
		int swap(); // Swap top stacks
		int peek() const;

		// Program manipulation
		char get() const;
		char get(int x, int y) const;
		void set(int x, int y, char v);

		// Debugging functions
		void displayProgram() const;
		void displayStack() const;
};
	



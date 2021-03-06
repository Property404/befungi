#include "catch.hpp"
#include <iostream>
#include <stdio.h>
#include "state.h"

TEST_CASE("State class works correctly"){
	std::string code = "Anything\nElse\nBut\nLove!";
	State state(code);
	SECTION("Check if stack works correctly")
	{
		REQUIRE(state.peek() == 0);
		REQUIRE(state.pop() == 0);
		REQUIRE(state.pop() == 0);
		state.push(5);
		REQUIRE(state.peek() == 5);
		REQUIRE(state.pop() == 5);
		REQUIRE(state.pop() == 0);
		state.push(9);
		state.push(3);
		state.push(2);
		state.push(1);
		state.push(8);
		REQUIRE(state.pop() == 8);
		REQUIRE(state.pop() == 1);
		REQUIRE(state.peek() == 2);
		REQUIRE(state.pop() == 2);
		REQUIRE(state.pop() == 3);
		REQUIRE(state.pop() == 9);
		REQUIRE(state.pop() == 0);
		REQUIRE(state.pop() == 0);
		REQUIRE(state.pop() == 0);
		state.push(4);
		state.push(5);
		REQUIRE(state.peek() == 5);
		state.swap();
		REQUIRE(state.peek() == 4);
		state.swap();
	}

	SECTION("Check if PC counter moves correctly"){
		REQUIRE(state.get() == 'A');
		REQUIRE(state.get() == 'A');
		state.move(0);
		REQUIRE(state.get() == 'A');
		state.move(2);
		REQUIRE(state.get() == 'y');
		state.down();
		state.move();
		REQUIRE(state.get() == 's');
		state.move();
		REQUIRE(state.get() == 't');
		state.right();
		state.move();
		REQUIRE(state.get() == 'B');
		state.left();
		REQUIRE(state.get() == 'B');
		state.move();
		REQUIRE(state.get() == 't');
		state.move();
		REQUIRE(state.get() == 'u');
		state.move();
		REQUIRE(state.get() == 'B');
		state.move();
		REQUIRE(state.get() == 't');
	}

	SECTION("Check if code is copied correctly"){
		REQUIRE(state.get(0,0) == 'A');
		REQUIRE(state.get(1,0) == 'n');
		REQUIRE(state.get(2,0) == 'y');
		REQUIRE(state.get(3,0) == 't');
		REQUIRE(state.get(4,0) == 'h');
		REQUIRE(state.get(5,0) == 'i');
		REQUIRE(state.get(6,0) == 'n');
		REQUIRE(state.get(7,0) == 'g');
		REQUIRE(state.get(8,0) == '\0');
		REQUIRE(state.get(0,1) == 'E');
		REQUIRE(state.get(4,3) == '!');
		REQUIRE(state.get(5,3) == '\0');
		// Make sure to wrap around
		REQUIRE(state.get(80,0) == 'A');
		REQUIRE(state.get(0,25) == 'A');
	}
	SECTION("Check Setting program memory dynamically")
	{
		REQUIRE(state.get(0,0) == 'A');
		state.set(0,0,'!');
		REQUIRE(state.get(0,0) == '!');
		state.set(5,3,'!');
		REQUIRE(state.get(5,3) == '!');
		state.set(80,0,'B');
		REQUIRE(state.get(0,0) == 'B');
		state.set(0,25,'C');
		REQUIRE(state.get(0,0) == 'C');
	}
}

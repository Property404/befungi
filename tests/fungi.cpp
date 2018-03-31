#include "catch.hpp"
#include <iostream>
#include <stdio.h>
#include "../src/fungi.h"

TEST_CASE("Check fungi")
{
	SECTION("Check for expected interpreter state change")
	{
		{
			Fungi fungi("59+:@");
			fungi.run();
			REQUIRE(fungi.getState().pop() == 14);
			REQUIRE(fungi.getState().pop() == 14);
			REQUIRE(fungi.getState().pop() == 0);
		}
		{
			Fungi fungi("510p@");
			fungi.run();
			REQUIRE(fungi.getState().peek() == 0);
			REQUIRE(fungi.getState().get(1, 0) == 5);
		}
		{
			Fungi fungi("2v\n <@9738#");
			fungi.run();
			REQUIRE(fungi.getState().pop() == 9);
			REQUIRE(fungi.getState().pop() == 7);
			REQUIRE(fungi.getState().pop() == 3);
			REQUIRE(fungi.getState().pop() == 2);
			REQUIRE(fungi.getState().pop() == 0);
		}
		{
			Fungi fungi("1v\n\"<@\"wee");
			fungi.run();
			REQUIRE(fungi.getState().pop() == 'w');
			REQUIRE(fungi.getState().pop() == 'e');
			REQUIRE(fungi.getState().pop() == 'e');
			REQUIRE(fungi.getState().pop() == 1);
			REQUIRE(fungi.getState().pop() == 0);
		}
	}
}



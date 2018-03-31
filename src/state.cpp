#include "state.h"
#include <iostream>
#include <cstring>

State::State()
{
	pcx = 0;
	pcy = 0;
	direction = RIGHT;
}

State::State(const std::string& code)
{
	pcx = 0;
	pcy = 0;
	direction = RIGHT;
	setCode(code);
}

void State::right()
{
	direction = RIGHT;
}
void State::left()
{
	direction = LEFT;
}
void State::up()
{
	direction = UP;
}
void State::down()
{
	direction = DOWN;
}

void State::move(int m)
{
	switch(direction)
	{
		case UP:
			pcy-=m;
			pcy%=BEFUNGE_ROWS;
			break;
		case DOWN:
			pcy+=m;
			pcy%=BEFUNGE_ROWS;
			break;
		case LEFT:
			pcx-=m;
			pcx%=BEFUNGE_COLUMNS;
			break;
		case RIGHT:
			pcx+=m;
			pcx%=BEFUNGE_COLUMNS;
			break;
	}
	if(this->get() == '\0')
		move(1);
}

void State::setCode(const std::string& code)
{

	// Zero out
	memset(program, 0, sizeof(program));

	int n=0;
	for(int i = 0; code[i] != '\0'; i++)
	{
		const int row = n/BEFUNGE_COLUMNS;
		const int column = n%BEFUNGE_COLUMNS;
		if(code[i] == '\n'){
			// Finish the row
			n+=BEFUNGE_COLUMNS - n%BEFUNGE_COLUMNS - 1;
		}else{
			program[row][column] = code[i];
		}
		n++;
	}
}

void State::push(int s)
{
	stack.push(s);
}

int State::pop()
{
	// If stack is empty, just give 0
	if(stack.empty())
		return 0;
	int p = stack.top();
	stack.pop();
	return p;
}

int State::peek() const
{
	if(stack.empty())
		return 0;
	return stack.top();
}


char State::get() const
{
	return program[pcy%BEFUNGE_ROWS][pcx%BEFUNGE_COLUMNS];
}

char State::get(int x, int y) const
{
	return program[y%BEFUNGE_ROWS][x%BEFUNGE_COLUMNS];
}

void State::set(int x, int y, char v)
{
	program[y%BEFUNGE_ROWS][x%BEFUNGE_COLUMNS] = v;
}

void State::displayProgram() const
{
	for(int r=0;r<BEFUNGE_ROWS;r++)
	{
		for(int c=0;c<BEFUNGE_COLUMNS;c++)
		{
			char a = program[r][c];
			a = a==0?'-':a;
			std::cout<<a;
		}
		std::cout<<"\n";
	}
}

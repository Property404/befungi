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
			while(pcy<0)pcy = BEFUNGE_ROWS+pcy;
			break;
		case DOWN:
			pcy+=m;
			pcy%=BEFUNGE_ROWS;
			break;
		case LEFT:
			pcx-=m;
			while(pcx<0)pcx = BEFUNGE_COLUMNS+pcx;
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

void State::push(long int s)
{
	stack.push(s);
}

long int State::pop()
{
	// If stack is empty, just give 0
	if(stack.empty())
		return 0;
	long int p = stack.top();
	stack.pop();
	return p;
}

long int State::swap()
{
	long int a = pop();
	long int b = pop();
	push(a);
	push(b);
}

long int State::peek() const
{
	if(stack.empty())
		return 0;
	return stack.top();
}


char State::get() const
{
	return get(pcx, pcy);
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
void State::displayLocation() const
{
	std::cout<<"("<<pcx<<","<<pcy<<")\n";
}


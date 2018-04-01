#include "fungi.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

Fungi::Fungi(const std::string& code)
{
	debug = false;
	state.setCode(code);
}
State& Fungi::getState()
{
	return state;
}

void Fungi::setDebug()
{
	debug = true;
}

void Fungi::run()
{
	bool stringmode = false;
	bool end = false;
	while(true)
	{
		if(debug)
			std::cout<<state.get();
		// During string mode, we're just recording until we reach a quote
		// symbol
		if(stringmode)
		{
			if(state.get() == '"')
			{
				stringmode = false;
			}
			else
			{
				state.push((long int)state.get());
			}
			state.move();
			continue;
		}

		// Directly execute commands
		switch(state.get())
		{
			// Begin string mode
			case '"':
				stringmode = true;
				break;
				// Pop from stack and display as ASCII
			case ',':
				std::cout<<(char)state.pop();
				break;
				// Pop from stack and display as integer
			case '.':
				std::cout<<state.pop();
				break;
				// Change direction
			case '<':
				state.left();
				break;
			case '>':
				state.right();
				break;
			case '^':
				state.up();
				break;
			case 'v':
				state.down();
				break;
				// Random direction
			case '?':
				switch(rand()%4)
				{
					case 0:
						state.left();
						break;
					case 1:
						state.right();
						break;
					case 2:
						state.up();
						break;
					case 3:
						state.down();
						break;
				}
				break;
				// Push numeric literal onto stack
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				state.push(state.get() - '0');
				break;
				// Math
			case '+':
				{
					long int a = state.pop();
					long int b = state.pop();
					state.push(a+b);
					break;
				}
			case '*':
				{
					long int a = state.pop();
					long int b = state.pop();
					state.push(a*b);
					break;
				}
			case '/':
				{
					long int a = state.pop();
					long int b = state.pop();
					if(a==0)
					{
						std::cout<<"What is the result of "<<a<<"/0? ";
						std::cin>>b;
						state.push(b);
					}
					else
					{
						state.push(b/a);
					}
					break;
				}
			case '-':
				{
					long int a = state.pop();
					long int b = state.pop();
					state.push(b-a);
					break;
				}
			case '%':
				{
					long int a = state.pop();
					long int b = state.pop();
					state.push(b%a);
					break;
				}
				// Logical not:
			case '!':
				state.push(!state.pop());
				break;
				// Greater than
			case '`':
				{
					long int a = state.pop();
					long int b = state.pop();
					state.push(b>a);
					break;
				}
				// Bridge
			case '#':
				state.move();
				break;
				// Duplicate top of stack
			case ':':
				state.push(state.peek());
				break;
				// Conditional:
				// Pop top:
				// 	Move right if 0, left otherwise
			case '_':
				if(state.pop() == 0)
				{
					state.right();
				}
				else
				{
					state.left();
				}
				break;
				// Vertical conditional
			case '|':
				if(state.pop() == 0)
				{
					state.down();
				}
				else
				{
					state.up();
				}
				// Discard
			case '$':
				state.pop();
				break;
				// Swap top stack values
			case '\\':
				state.swap();
				break;
				// Get integer
			case '&':
				{
					int i;
					std::cin >> i;
					state.push(i);
				}
				break;
				// Get char
			case '~':
				state.push(getchar());
				break;
				// End:
			case 'g':
				{
					int x, y;
					y = state.pop();
					x = state.pop();
					if(x<0 || x>=BEFUNGE_COLUMNS || y<0 || y>=BEFUNGE_ROWS)
						state.push(0);
					state.push(state.get(x,y));
					break;
				}
			case 'p':
				{
					int x, y, v;
					y = state.pop();
					x = state.pop();
					v = state.pop();
					state.set(x,y, v);
					break;
				}
			case '@':
				end = true;
				break;
			default:
				break;
		}
		if(end == true)break;
		state.move();
	}
}

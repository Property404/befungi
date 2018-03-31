#include "fungi.h"
#include <iostream>

Fungi::Fungi(const std::string& code)
{
	state.setCode(code);
}

void Fungi::run()
{
	bool stringmode = false;
	bool end = false;
	while(true)
	{
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
				state.push(state.get());
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
				int a = state.pop();
				int b = state.pop();
				state.push(a+b);
				break;
				}
			case '*':
				{
				int a = state.pop();
				int b = state.pop();
				state.push(a*b);
				break;
				}
			case '/':
				{
				int a = state.pop();
				int b = state.pop();
				state.push(a/b);
				break;
				}
			case '-':
				{
				int a = state.pop();
				int b = state.pop();
				state.push(a-b);
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
			// End:
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

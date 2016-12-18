#pragma once

#include <iostream>
#include <map>
#include <cctype>
#include <stack>
#include <string>
/*
// 如何表示不同操作符的优先级？
// 使用一个map
*/
namespace my
{
	void in_to_post()
	{
		std::map<char, int> m;
		std::stack<char> cstack;
		m.insert(std::pair<char, int>('+', 1));
		m.insert(std::pair<char, int>('-', 1));
		m.insert(std::pair<char, int>('*', 2));
		m.insert(std::pair<char, int>('/', 2));
		m.insert(std::pair<char, int>('^', 3));
		m.insert(std::pair<char, int>('(', 5));
		m.insert(std::pair<char, int>(')', 5));

		char c;
		while (std::cin >> c)
		{
			if (!ispunct(c))
				std::cout << c << " ";
			else
			{
				if (c == ')')
				{
					while (!cstack.empty() && cstack.top() != '(')
					{
						std::cout << cstack.top() << " ";
						cstack.pop();
					}
					cstack.pop();
				}
				else
				{
					while (!cstack.empty() && cstack.top() != '(' && m.at(c) <= m.at(cstack.top()))
					{
						std::cout << cstack.top() << " ";
						cstack.pop();
					}
					cstack.push(c);
				}
			}		
		}
		while (!cstack.empty())
		{
			std::cout << cstack.top() << " ";
			cstack.pop();
		}
		std::cout << std::endl;
	}

	void post_to_in()
	{
		// errors
		char c;
		char old;
		int token = 0;
		std::map<char, int> m;
		std::stack<char> cstack;
		m.insert(std::pair<char, int>('+', 1));
		m.insert(std::pair<char, int>('-', 1));
		m.insert(std::pair<char, int>('*', 2));
		m.insert(std::pair<char, int>('/', 2));
		while(std::cin >> c)
		{
			if (!ispunct(c))
				cstack.push(c);
			else
			{
				if ( token == 0)
				{
					//std::cout << "( " << cstack.top() << " " << c << " ";
					std::cout << cstack.top() << " " << c << " ";
					cstack.pop();
					//std::cout << cstack.top() << " ) ";
					std::cout << cstack.top() << " ";
					cstack.pop();
					token = 1;
					old = c;
				}
				else
				{
					//std::cout << c << " " << cstack.top() << " " ;
					std::cout << c << " " << cstack.top() << " ";
					cstack.pop();
					old = c;
				}
				
			}
		}
	}
	void postToInfix()
	{
		// reference: https://www.codeproject.com/articles/405361/converting-postfix-expressions-to-infix
		struct expr
		{
			expr(std::string && s1, char s2) : content(s1), oper(s2) {}
			expr(std::string &s1, char s2) : content(s1), oper(s2) {}
			expr(char s1, char s2) : content(std::string(1,s1)), oper(s2) {}
			// convert char into string use string(1, c) 
			std::string content;	// store the result of combination of left operand and right operand
			char oper;
		};
		std::stack<expr> sta;
		char c;
		while(std::cin >> c)
		{
			if (!ispunct(c))
				sta.push(expr(c, ' '));
			else
			{
				if (c == '+' || c == '-')
				{
					auto rPart = sta.top();
					sta.pop();
					auto lPart = sta.top();
					sta.pop();
					std::string res = lPart.content + std::string(1, c) + rPart.content;
					sta.push(expr(res,c));
				}
				if (c == '*' || c == '/')
				{
					auto rPart = sta.top();
					sta.pop();
					auto lPart = sta.top();
					sta.pop();
					// add parentheses only when they are needed!
					std::string rStr = (rPart.oper == '+' || rPart.oper == '-') ? "(" + rPart.content + ")" : rPart.content;
					std::string lStr = (lPart.oper == '+' || lPart.oper == '-') ? "(" + lPart.content + ")" : lPart.content;
					std::string res = lStr + std::string(1,c) + rStr;
					sta.push(expr(res, c));
				}
					
			}
		}
		std::cout << sta.top().content << std::endl;
	}
}

namespace ans
{
	void inToPostfix()
	{
		std::stack<char> s;
		char token;
		std::cin >> token;
		while (token != '=')
		{
			if (token >= 'a' && token <= 'z')
				std::cout << token << " ";
			else
			{
				switch(token)
				{
				case ')':
					while(!s.empty() && s.top() != '(')
					{
						std::cout << s.top() << " ";
						s.pop();
					}
					s.pop();
					break;
				case '(':
					s.push(token);
					break;
				case '^':
					while (!s.empty() && !(s.top() == '^' || s.top() == '('))
					{
						std::cout << s.top();
						s.pop();
					}
					s.push(token);
					break;
				case '*':
				case '/':
					while(!s.empty() && s.top() != '+' && s.top() != '-' && s.top() != '(')
					{
						std::cout << s.top();
						s.pop();
					}
					s.push(token);
					break;
				case '+':
				case '-':
					while(!s.empty() && s.top() != '(')
					{
						std::cout << s.top() << " ";
						s.pop();
					}
					s.push(token);
					break;
				}
			}
		}
		while(!s.empty())
		{
			std::cout << s.top() << " ";
			s.pop();
		}
		std::cout << ' = \n';
	}

	std::string postToInfix()
	{
		std::stack<std::string> s;
		std::string token, a, b;
		std::cin >> token;
		while(token[0] != '=')
		{
			if (token[0] >= 'a' && token[0] <= 'z')
				s.push(token);
			else
			{
				switch(token[0])
				{
				case '+':
					a = s.top(); s.pop(); b = s.top(); s.pop();
					s.push("(" + a + " + " + b + ")"); break;
				case '-':
					a = s.top(); s.pop(); b = s.top(); s.pop();
					s.push("(" + a + " - " + b + ")"); break;
				case '*':
					a = s.top(); s.pop(); b = s.top(); s.pop();
					s.push("(" + a + " * " + b + ")"); break;
				case '/':
					a = s.top(); s.pop(); b = s.top(); s.pop();
					s.push("(" + a + " / " + b + ")"); break;
				case '^':
					a = s.top(); s.pop(); b = s.top(); s.pop();
					s.push("(" + a + " ^ " + b + ")"); break;
				}
			}
			std::cin >> token;
		}
		return s.top();
	}
}
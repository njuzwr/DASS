#pragma once
#include <stack>
#include <cctype>
#include <iostream>
#include <string>
namespace my
{
	void postfix_evaluation(std::istream &in)
	{
		char c;
		std::stack<int> istack;
		while (in >> c)
		{
			if (isdigit(c))
				istack.push(c - '0');
			else
			{
				int ia = istack.top();
				istack.pop();
				int ib = istack.top();
				istack.pop();
				switch (c)
				{
				case '+':
					istack.push(ib + ia);
					break;
				case '-':
					istack.push(ib - ia);
					break;
				case '*':
					istack.push(ib * ia);
					break;
				case '/':
					istack.push(ib / ia);
					break;
				default:
					throw std::runtime_error("unsupported operation");
				}
			}
		}
		std::cout << "The evaluation result is : " << istack.top() << std::endl;
		istack.pop();
	}

}
// 答案有问题
namespace ans
{
	double evalPosFix()
	{
		std::stack<double> s;
		std::string token;
		double a, b, result;
		std::cin >> token;
		while (token[0] != '=')
		{
			result = atof(token.c_str());
			if (result != 0.0)
				s.push(result);
			else if (token == "0.0")
				s.push(result);
			else
			{
				auto a = s.top();
				s.pop();
				auto b = s.top();
				s.pop();
				switch (token[0])
				{
				case '+': 
					s.push(a + b);
					break;
				case '-':
					s.push(b - a);
					break;
				case '*':
					s.push(b * a);
					break;
				case '/':
					s.push(b / a);
					break;
				}
				std::cin >> token;
			}
		}
		return s.top();
	}
}
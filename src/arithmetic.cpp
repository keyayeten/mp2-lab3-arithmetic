#include "..\include\arithmetic.h"

// реализация функций и классов для вычисления арифметических выражений

Arithmetic::Arithmetic(string str)
{
	input = str;
	if (str.empty())
		status = -1;
	else
		status = 0;
}

vector<lexema> Arithmetic::get_input_lex()
{
	if (status == 1)
		return inp_lex;
	else
		throw exception("not split");
}

vector<lexema> Arithmetic::get_polish_lex()
{
	if (status == 2)
		return pol_lex;
	else
		throw exception("not converted");
}

double Arithmetic::get_result()
{
	if (status == 4)
		return result;
	else
		throw exception("not calculated");
}

void Arithmetic::enter()
{
	do
	{
		cout << "Enter arithmetic expression:" << endl;
		getline(cin, input);
	} while (input.empty());
	status = 0;
}

void Arithmetic::split()
{
	for (size_t i = 0; i < input.length(); i++)
	{
		string abc = "abcdefghijklmnopqrstuvwxyz";
		string num = ".0123456789";
		size_t p_abc = abc.find(input[i]);
		size_t p_num = num.find(input[i]);

		lexema tmp(input[i]);

		if (input[i] != ' ')
		{
			if (input[i] == '(' || input[i] == '[' || input[i] == '{')
				tmp.type = 0;
			else if (input[i] == ')' || input[i] == ']' || input[i] == '}')
				tmp.type = -1;
			else if (input[i] == '+')
				tmp.type = 1;
			else if (input[i] == '*' || input[i] == '/')
				tmp.type = 2;
			else if (input[i] == '^')
				tmp.type = 3;
			else if (input[i] == '-')
			{
				if (inp_lex.empty() || (inp_lex.back().type > -1 && inp_lex.back().type < 5))
				{
					tmp.val = "--";
					tmp.type = 4;
				}
				else
					tmp.type = 1;
			}
			else if (p_abc != abc.npos)
			{
				if (input[i] == 's' && input[i + 1] == 'i' && input[i + 2] == 'n' && input[i + 3] == '(')
				{
					tmp.type = 5;
					tmp.val = "sin";
					i = i + 2;
				}
				else if (input[i] == 'c' && input[i + 1] == 'o' && input[i + 2] == 's' && input[i + 3] == '(')
				{
					tmp.type = 5;
					tmp.val = "cos";
					i = i + 2;
				}
				else if (input[i] == 'e' && input[i + 1] == 'x' && input[i + 2] == 'p' && input[i + 3] == '(')
				{
					tmp.type = 5;
					tmp.val = "exp";
					i = i + 2;
				}
				else if (input[i] == 'l' && input[i + 1] == 'n' && input[i + 2] == '(')
				{
					tmp.type = 5;
					tmp.val = "ln";
					i = i + 1;
				}
				else
				{
					tmp.type = -2;
					for (size_t j = i + 1; j < input.length(); j++)
					{
						p_abc = abc.find(input[j]);
						if (p_abc != abc.npos)
						{
							tmp.val.push_back(input[j]);
							i++;
						}
						else
							j = input.length();
					}
				}
			}
			else if (p_num != num.npos)
			{
				tmp.type = -3;
				for (size_t j = i + 1; j < input.length(); j++)
				{
					p_num = num.find(input[j]);
					if (p_num != num.npos)
					{
						tmp.val.push_back(input[j]);
						i++;
					}
					else
						j = input.length();
				}
			}
			inp_lex.push_back(tmp);
		}
	}

	status = 1;
}

bool Arithmetic::check_bkt()
{
	Stack<char> T;
	for (size_t i = 0; i < inp_lex.size(); i++)
	{
		if (inp_lex[i].type == 0)
			T.Put('(');
		if (inp_lex[i].type == -1)
		{
			if (T.IsEmpty())
				return false;
			else
				T.Get();
		}
	}
	return T.IsEmpty();
}

vector<int> Arithmetic::check_symbols()
{
	vector<int> err;

	for (size_t i = 0; i < inp_lex.size(); i++)
	{
		if (inp_lex[i].type == -100)
			err.push_back(i + 1);
	}

	return err;
}

bool Arithmetic::check_points()
{
	for (size_t i = 0; i < inp_lex.size(); i++)
	{
		if (inp_lex[i].type == -3)
		{
			size_t p = inp_lex[i].val.find_first_of('.');
			p = inp_lex[i].val.find_first_of('.', p + 1);
			if (p != inp_lex[i].val.npos)
				return false;
		}
	}
	return true;
}

bool Arithmetic::oper()
{
	if (inp_lex[0].type > 0 && inp_lex[0].type < 4)
	{
		return false;
	}
	if (inp_lex.back().type > 0 && inp_lex.back().type < 4)
	{
		return false;
	}

	for (size_t i = 0; i < inp_lex.size(); i++)
	{
		if ((inp_lex[i].type > 0 && inp_lex[i].type < 4) && (inp_lex[i + 1].type > 0 && inp_lex[i + 1].type < 4))
		{
			return false;
		}
		if (inp_lex[i].type == 4 && inp_lex[i + 1].type == 4)
		{
			return false;
		}
		if (i != inp_lex.size() - 1)
			if (inp_lex[i].type == -1 && (inp_lex[i + 1].type == -3 || inp_lex[i + 1].type == -2 || inp_lex[i + 1].type == 0 || inp_lex[i + 1].type == 5))
			{
				return false;
			}
	}
	return true;
}

bool Arithmetic::isCorrect()
{
	bool F = true;

	if (!check_points())
	{
		cout << "Input error: extra point in number" << endl;
		F = false;
	}

	if (!check_bkt())
	{
		cout << "Input error: brackets" << endl;
		F = false;
	}

	if (!oper())
	{
		cout << "Input error: operations" << endl;
		F = false;
	}

	vector<int> err = check_symbols();
	if (!err.empty())
	{
		F = false;
		cout << "Input error: prohibited symbols in ";
		cout << err[0] << "th";
		for (size_t i = 1; i < err.size(); i++)
			cout << ", " << err[i] << "th";
		cout << " places!\n";
	}

	if (!F)
		status = -1;
	return F;
}

void Arithmetic::converter()
{
	Stack<lexema> T;
	for (size_t i = 0; i < inp_lex.size(); i++)
	{
		if (inp_lex[i].type < -1)
			pol_lex.push_back(inp_lex[i]);
		else if (inp_lex[i].type == -1)
		{
			while (T.View().type != 0)
				pol_lex.push_back(T.Get());

			T.Get();
		}
		else if (inp_lex[i].type == 0)
		{
			T.Put(inp_lex[i]);
		}
		else
		{
			while (!T.IsEmpty() && T.View().type >= inp_lex[i].type)
				pol_lex.push_back(T.Get());

			T.Put(inp_lex[i]);
		}
	}
	while (!T.IsEmpty())
	{
		pol_lex.push_back(T.Get());
	}

	status = 2;
}

void Arithmetic::set_values()
{
	for (size_t i = 0; i < pol_lex.size(); i++)
	{
		if (pol_lex[i].type == -3)
			pol_lex[i].x = stod(pol_lex[i].val);

		if (pol_lex[i].type == -2)
		{
			cout << "Enter the value of the variable '" << pol_lex[i].val << "': ";
			cin >> pol_lex[i].x;
		}
	}

	status = 3;
}

void Arithmetic::calculate()
{
	Stack<double> T;
	for (size_t i = 0; i < pol_lex.size(); i++)
	{
		if (pol_lex[i].type < -1)
			T.Put(pol_lex[i].x);
		else
		{
			double x = T.Get();
			if (pol_lex[i].val == "sin")
				T.Put(sin(x));
			else if (pol_lex[i].val == "cos")
				T.Put(cos(x));
			else if (pol_lex[i].val == "exp")
				T.Put(exp(x));
			else if (pol_lex[i].val == "ln")
				T.Put(log(x));
			else if (pol_lex[i].val == "--")
				T.Put(-x);
			else
			{
				double y = T.Get();
				if (pol_lex[i].val == "+")
					T.Put(x + y);
				else if (pol_lex[i].val == "-")
					T.Put(y - x);
				else if (pol_lex[i].val == "*")
					T.Put(x * y);
				else if (pol_lex[i].val == "/")
					T.Put(y / x);
				else if (pol_lex[i].val == "^")
					T.Put(pow(y, x));
			}
		}
	}

	result = T.Get();
	status = 4;
}

void Arithmetic::launch()
{
	if (status == -1)
		enter();
	if (status == 0)
		split();
	if (status == 1 && isCorrect())
		converter();
	if (status == 2)
		set_values();
	if (status == 3)
		calculate();
	if (status == 4)
		cout << "RESULT: " << result << endl;
}
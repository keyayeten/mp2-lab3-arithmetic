// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#include "stack.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct lexema
{
	string val;
	int type;
	double x;
	lexema()
	{
		x = 0.0;
		val = "\0";
		type = -100;
	}
	lexema(string s, int t = -100)
	{
		x = 0.0;
		val = s;
		type = t;
	}
	lexema(char s, int t = -100)
	{
		x = 0.0;
		val = s;
		type = t;
	}
	int operator==(const lexema& l)
	{
		return ((val == l.val) && (type == l.type));
	}
};

class Arithmetic
{
	string input;
	double result;
	vector<lexema> inp_lex;
	vector<lexema> pol_lex;
	int status;

public:
	void enter();
	void split();
	bool check_bkt();
	vector<int> check_symbols();
	bool check_points();
	bool oper();
	bool isCorrect();
	void converter();
	void set_values();
	void calculate();
	void launch();
	Arithmetic(string str = "");
	vector<lexema> get_input_lex();
	vector<lexema> get_polish_lex();
	double get_result();
};
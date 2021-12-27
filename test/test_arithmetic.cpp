// тесты дл€ вычислени€ арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(arithmetic, can_create_arithmetic)
{
	ASSERT_NO_THROW(Arithmetic A("5 + 5"));
}

TEST(arithmetic, split_correct1)
{
	Arithmetic A("(sin(2*exp(log - 10)) + cos(2^2)) / -ln(a)");
	A.split();
	vector<lexema> inp = A.get_input_lex();
	vector<lexema> v;
	v.push_back(lexema("(", 0));
	v.push_back(lexema("sin", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("2", -3));
	v.push_back(lexema("*", 2));
	v.push_back(lexema("exp", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("log", -2));
	v.push_back(lexema("-", 1));
	v.push_back(lexema("10", -3));
	v.push_back(lexema(")", -1));
	v.push_back(lexema(")", -1));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("cos", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("2", -3));
	v.push_back(lexema("^", 3));
	v.push_back(lexema("2", -3));
	v.push_back(lexema(")", -1));
	v.push_back(lexema(")", -1));
	v.push_back(lexema("/", 2));
	v.push_back(lexema("--", 4));
	v.push_back(lexema("ln", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("a", -2));
	v.push_back(lexema(")", -1));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, split_correct2)
{
	Arithmetic A("-(3*3)^sin(1)*ln(10)");
	A.split();
	vector<lexema> inp = A.get_input_lex();
	vector<lexema> v;
	v.push_back(lexema("--", 4));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("3", -3));
	v.push_back(lexema("*", 2));
	v.push_back(lexema("3", -3));
	v.push_back(lexema(")", -1));
	v.push_back(lexema("^", 3));
	v.push_back(lexema("sin", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("1", -3));
	v.push_back(lexema(")", -1));
	v.push_back(lexema("*", 2));
	v.push_back(lexema("ln", 5));
	v.push_back(lexema("(", 0));
	v.push_back(lexema("10", -3));
	v.push_back(lexema(")", -1));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, split_correct3)
{
	Arithmetic A("5 + si");
	A.split();
	vector<lexema> inp = A.get_input_lex();
	vector<lexema> v;
	v.push_back(lexema("5", -3));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("si", -2));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, split_correct4)
{
	Arithmetic A("ln + exp + sin + cos");
	A.split();
	vector<lexema> inp = A.get_input_lex();
	vector<lexema> v;
	v.push_back(lexema("ln", -2));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("exp", -2));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("sin", -2));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("cos", -2));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, check_incorrect_bkt1)
{
	Arithmetic A("4 + ( 4 - 1 ) )");
	A.split();
	EXPECT_FALSE(A.check_bkt());
}

TEST(arithmetic, check_incorrect_bkt2)
{
	Arithmetic A("((( 1 + 2) * (2 - 3) ) / ) (3 Ц 5) + 7 ) * 5");
	A.split();
	EXPECT_FALSE(A.check_bkt());
}

TEST(arithmetic, check_incorrect_bkt3)
{
	Arithmetic A("{4 - 5 * [(3 + 5)}");
	A.split();
	EXPECT_FALSE(A.check_bkt());
}

TEST(arithmetic, check_correct_bkt1)
{
	Arithmetic A("{5 - [4 * 4] + sin(4)}");
	A.split();
	EXPECT_TRUE(A.check_bkt());
}

TEST(arithmetic, check_correct_bkt2)
{
	Arithmetic A("(5 + 5)^ln(5) - [4 + 5]");
	A.split();
	EXPECT_TRUE(A.check_bkt());
}

TEST(arithmetic, check_symbols)
{
	Arithmetic A("(5 + 5) & 4");
	A.split();
	EXPECT_EQ(6, A.check_symbols().front());
}

TEST(arithmetic, check_points)
{
	Arithmetic A("5.0001.1 + 1");
	A.split();
	EXPECT_FALSE(A.check_points());
}

TEST(arithmetic, check_operation1)
{
	Arithmetic A("5 + + 1");
	A.split();
	EXPECT_FALSE(A.check_operations());
}

TEST(arithmetic, check_operation2)
{
	Arithmetic A("[4 + ) 5 * 5 ( - 6]");
	A.split();
	//EXPECT_FALSE(A.check_bkt());
	EXPECT_FALSE(A.check_operations());
}

TEST(arithmetic, check_operation3)
{
	Arithmetic A("- - 5");
	A.split();
	EXPECT_FALSE(A.check_operations());
}

TEST(arithmetic, converter_correct1)
{
	Arithmetic A("(sin(2*exp(log - 10)) + cos(2^2)) / -ln(a)");
	A.split();
	A.converter();
	vector<lexema> inp = A.get_polish_lex();
	vector<lexema> v;
	v.push_back(lexema("2", -3));
	v.push_back(lexema("log", -2));
	v.push_back(lexema("10", -3));
	v.push_back(lexema("-", 1));
	v.push_back(lexema("exp", 5));
	v.push_back(lexema("*", 2));
	v.push_back(lexema("sin", 5));
	v.push_back(lexema("2", -3));
	v.push_back(lexema("2", -3));
	v.push_back(lexema("^", 3));
	v.push_back(lexema("cos", 5));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("a", -2));
	v.push_back(lexema("ln", 5));
	v.push_back(lexema("--", 4));
	v.push_back(lexema("/", 2));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, converter_correct2)
{
	Arithmetic A("-sin(1.7)^5");
	A.split();
	A.converter();
	vector<lexema> inp = A.get_polish_lex();
	vector<lexema> v;
	v.push_back(lexema("1.7", -3));
	v.push_back(lexema("sin", 5));
	v.push_back(lexema("--", 4));
	v.push_back(lexema("5", -3));
	v.push_back(lexema("^", 3));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, converter_correct3)
{
	Arithmetic A("-5*(5+5)^-1");
	A.split();
	A.converter();
	vector<lexema> inp = A.get_polish_lex();
	vector<lexema> v;
	v.push_back(lexema("5", -3));
	v.push_back(lexema("--", 4));
	v.push_back(lexema("5", -3));
	v.push_back(lexema("5", -3));
	v.push_back(lexema("+", 1));
	v.push_back(lexema("1", -3));
	v.push_back(lexema("--", 4));
	v.push_back(lexema("^", 3));
	v.push_back(lexema("*", 2));

	bool F = true;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (!(inp[i] == v[i]))
			F = false;
	}

	EXPECT_TRUE(F);
}

TEST(arithmetic, calculate_correct1)
{
	Arithmetic A("(sin(2*exp(11 - 10)) + cos(2^2)) / -ln(2.71)");
	A.split();
	A.converter();
	A.set_values();
	A.calculate();
	EXPECT_FLOAT_EQ(1.406983, A.get_result());
}

TEST(arithmetic, calculate_correct2)
{
	Arithmetic A("-(3*3)^3*ln(7)");
	A.split();
	A.converter();
	A.set_values();
	A.calculate();
	EXPECT_FLOAT_EQ(-1418.56849866, A.get_result());
}

TEST(arithmetic, calculate_correct3)
{
	Arithmetic A("sin(-4.21*5^ln(5.78)/cos(1.45 + 3.54))");
	A.split();
	A.converter();
	A.set_values();
	A.calculate();
	EXPECT_FLOAT_EQ(-0.86246998, A.get_result());
}
// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_pisitive_lenght)
{
	ASSERT_NO_THROW(Stack<int> T(5));
}

TEST(Stack, throws_when_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(Stack<int> T(-5));
}

TEST(Stack, new_stack_is_empty)
{
	Stack<int> T(5);
	EXPECT_TRUE(T.IsEmpty());
}

TEST(Stack, can_put_and_view)
{
	Stack<int> T(5);
	T.Put(1);
	EXPECT_EQ(1, T.View());
}

TEST(Stack, get_deletes_element)
{
	Stack<int> T(5);
	T.Put(1);
	int tmp = T.Get();
	EXPECT_TRUE(T.IsEmpty());
}

TEST(Stack, can_clear)
{
	Stack<int> T(5);
	T.Put(1);
	T.Put(2);
	T.Put(3);
	T.Clear();
	EXPECT_TRUE(T.IsEmpty());
}
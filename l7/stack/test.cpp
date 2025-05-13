#include <gtest/gtest.h>
#include "CMyStack.cpp"

TEST(CMyStackTest, PushAndTopInt)
{
  CMyStack<int> stack;
  stack.Push(10);
  EXPECT_EQ(stack.Top(), 10);

  stack.Push(20);
  EXPECT_EQ(stack.Top(), 20);
}

TEST(CMyStackTest, PushAndTopString)
{
  CMyStack<std::string> stack;
  stack.Push("hello");
  EXPECT_EQ(stack.Top(), "hello");

  stack.Push("world");
  EXPECT_EQ(stack.Top(), "world");
}

TEST(CMyStackTest, PopWorks)
{
  CMyStack<int> stack;
  stack.Push(5);
  stack.Push(15);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 5);

  stack.Pop();
  EXPECT_TRUE(stack.Empty());
}

TEST(CMyStackTest, PopThrowsOnEmpty)
{
  CMyStack<int> stack;
  EXPECT_THROW(stack.Pop(), std::runtime_error);

  stack.Push(100);
  stack.Pop();
  EXPECT_THROW(stack.Pop(), std::runtime_error);
}

TEST(CMyStackTest, TopThrowsOnEmpty)
{
  CMyStack<std::string> stack;
  EXPECT_THROW(stack.Top(), std::runtime_error);

  stack.Push("test");
  stack.Pop();
  EXPECT_THROW(stack.Top(), std::runtime_error);
}

TEST(CMyStackTest, EmptyCheck)
{
  CMyStack<int> stack;
  EXPECT_TRUE(stack.Empty());

  stack.Push(1);
  EXPECT_FALSE(stack.Empty());
}

TEST(CMyStackTest, ClearWorks)
{
  CMyStack<int> stack;
  stack.Push(1);
  stack.Push(2);
  stack.Clear();
  EXPECT_TRUE(stack.Empty());

  stack.Push(3);
  EXPECT_EQ(stack.Top(), 3);
}

TEST(CMyStackTest, CopyConstructor)
{
  CMyStack<int> stack;
  stack.Push(1);
  stack.Push(2);

  CMyStack<int> copy(stack);
  EXPECT_EQ(copy.Top(), 2);
  copy.Pop();
  EXPECT_EQ(copy.Top(), 1);
}

TEST(CMyStackTest, CopyAssignment)
{
  CMyStack<std::string> stack1;
  stack1.Push("first");
  stack1.Push("second");

  CMyStack<std::string> stack2;
  stack2 = stack1;
  EXPECT_EQ(stack2.Top(), "second");
  stack2.Pop();
  EXPECT_EQ(stack2.Top(), "first");
}

TEST(CMyStackTest, MoveConstructor)
{
  CMyStack<int> stack;
  stack.Push(7);
  stack.Push(8);

  CMyStack<int> moved(std::move(stack));
  EXPECT_EQ(moved.Top(), 8);
  moved.Pop();
  EXPECT_EQ(moved.Top(), 7);
  EXPECT_TRUE(stack.Empty());
}

TEST(CMyStackTest, MoveAssignment)
{
  CMyStack<int> stack1;
  stack1.Push(42);
  stack1.Push(43);

  CMyStack<int> stack2;
  stack2 = std::move(stack1);

  EXPECT_EQ(stack2.Top(), 43);
  stack2.Pop();
  EXPECT_EQ(stack2.Top(), 42);
  EXPECT_TRUE(stack1.Empty());
}

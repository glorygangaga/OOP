#include <iostream>
#include <stdexcept>

template <typename T>
class CMyStack
{
public:
  CMyStack() : m_size(0), m_head(nullptr) {};
  CMyStack(const CMyStack &stack) : m_size(0), m_head(nullptr)
  {
    if (!stack.Empty())
    {
      m_head = new Node<T>(stack.m_head->data);
      Node<T> *current = m_head;
      Node<T> *currentStack = stack.m_head->next;

      while (currentStack != nullptr)
      {
        current->next = new Node<T>(currentStack->data);
        current = current->next;
        currentStack = currentStack->next;
      }
      m_size = stack.m_size;
    }
  };
  CMyStack(CMyStack &&stack) : m_size(stack.m_size), m_head(stack.m_head)
  {
    stack.m_head = nullptr;
    stack.m_size = 0;
  };

  ~CMyStack() { Clear(); };

  void Push(const T &value);
  void Pop();
  bool Empty() const { return m_size == 0; };
  void Clear() noexcept;
  T &Top() const;

  CMyStack &operator=(const CMyStack &stack)
  {
    if (&stack != this)
    {
      CMyStack temp(stack);
      std::swap(m_head, temp.m_head);
      std::swap(m_size, temp.m_size);
    }

    return *this;
  }

  CMyStack &operator=(CMyStack &&stack)
  {
    if (&stack != this)
    {
      Clear();
      m_size = stack.m_size;
      m_head = stack.m_head;

      stack.m_head = nullptr;
      stack.m_size = 0;
    }

    return *this;
  }

private:
  template <typename T1>
  class Node
  {
  public:
    Node(const T1 value, Node<T1> *nextVal = nullptr) : data(value), next(nextVal) {};

    T1 data;
    Node<T1> *next;
  };

  size_t m_size;
  Node<T> *m_head;
};

template <typename T>
void CMyStack<T>::Push(const T &value)
{
  m_head = new Node<T>(value, m_head);
  m_size++;
}

template <typename T>
void CMyStack<T>::Pop()
{
  if (Empty())
    throw std::runtime_error("Empty stack");

  Node<T> *temp = m_head;
  m_head = m_head->next;
  delete temp;
  m_size--;
}

template <typename T>
void CMyStack<T>::Clear() noexcept
{
  while (m_head != nullptr)
  {
    Node<T> *temp = m_head;
    m_head = m_head->next;
    delete temp;
  }
  m_size = 0;
}

template <typename T>
T &CMyStack<T>::Top() const
{
  if (Empty())
    throw std::runtime_error("Empty stack");

  return m_head->data;
}

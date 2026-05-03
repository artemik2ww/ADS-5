// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool is_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> stack;
  std::string post;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (c == ' ') {
      continue;
    }

    if (std::isdigit(c)) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        post += inf[i];
        ++i;
      }
      post += ' ';
      --i;
    } else if (c == '(') {
      stack.push(c);
    } else if (c == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        post += stack.top();
        post += ' ';
        stack.pop();
      }
      stack.pop();
    } else if (is_operator(c)) {
      while (!stack.isEmpty() &&
             is_operator(stack.top()) &&
             priority(stack.top()) >= priority(c)) {
        post += stack.top();
        post += ' ';
        stack.pop();
      }
      stack.push(c);
    }
  }

  while (!stack.isEmpty()) {
    post += stack.top();
    post += ' ';
    stack.pop();
  }

  if (!post.empty() && post.back() == ' ') {
    post.pop_back();
  }

  return post;
}

int eval(const std::string& post) {
  TStack<int, 100> stack;

  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];

    if (c == ' ') {
      continue;
    }

    if (std::isdigit(c)) {
      int num = 0;

      while (i < post.size() && std::isdigit(post[i])) {
        num = num * 10 + (post[i] - '0');
        ++i;
      }

      stack.push(num);
      --i;
    } else if (is_operator(c)) {
      int b = stack.top();
      stack.pop();

      int a = stack.top();
      stack.pop();

      int result = 0;

      switch (c) {
        case '+':
          result = a + b;
          break;
        case '-':
          result = a - b;
          break;
        case '*':
          result = a * b;
          break;
        case '/':
          result = a / b;
          break;
      }

      stack.push(result);
    }
  }

  return stack.top();
}

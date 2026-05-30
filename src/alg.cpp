// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
    std::string post = "";
    TStack<char, 100> stack;
    bool lastWasDigit = false;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];
        if (c == ' ') {
            continue;
        }
        if (std::isdigit(c)) {
            post += c;
            lastWasDigit = true;
        } else {
            if (lastWasDigit) {
                post += ' ';
                lastWasDigit = false;
            }
            if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.get() != '(') {
                    post += stack.get();
                    post += ' ';
                    stack.pop();
                }
                stack.pop();
            } else {
                int pCurr = (c == '*' || c == '/') ? 2 : 1;
                while (!stack.isEmpty()) {
                    char top = stack.get();
                    int pTop = (top == '*' || top == '/') ? 2 :
                               (top == '+' || top == '-') ? 1 : 0;
                    if (pTop >= pCurr) {
                        post += top;
                        post += ' ';
                        stack.pop();
                    } else {
                        break;
                    }
                }
                stack.push(c);
            }
        }
    }
    if (lastWasDigit) {
        post += ' ';
    }
    while (!stack.isEmpty()) {
        post += stack.get();
        post += ' ';
        stack.pop();
    }
    if (!post.empty() && post.back() == ' ') {
        post.pop_back();
    }
    return post;
}

int eval(const std::string& pref) {
    TStack<int, 100> stack;
    int currentNum = 0;
    bool hasNum = false;

    for (size_t i = 0; i < pref.length(); ++i) {
        char c = pref[i];
        if (std::isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
            hasNum = true;
        } else {
            if (hasNum) {
                stack.push(currentNum);
                currentNum = 0;
                hasNum = false;
            }
            if (c != ' ') {
                int val2 = stack.get(); stack.pop();
                int val1 = stack.get(); stack.pop();
                int out = 0;
                if (c == '+') out = val1 + val2;
                if (c == '-') out = val1 - val2;
                if (c == '*') out = val1 * val2;
                if (c == '/') out = (val2 != 0) ? (val1 / val2) : 0;
                stack.push(out);
            }
        }
    }
    if (hasNum) {
        stack.push(currentNum);
    }
    return stack.get();
}

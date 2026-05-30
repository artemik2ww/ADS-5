// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
    enum { kMaxSize = size };
    T data[kMaxSize];
    int count;

 public:
    TStack() : count(0) {}

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == kMaxSize;
    }

    void push(const T& value) {
        if (count < kMaxSize) {
            data[count++] = value;
        }
    }

    void pop() {
        if (count > 0) {
            count--;
        }
    }

    T get() const {
        if (count > 0) {
            return data[count - 1];
        }
        return T();
    }
};

#endif  // INCLUDE_TSTACK_H_

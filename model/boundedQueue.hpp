#ifndef BOUNDEDQUEUE_H
#define BOUNDEDQUEUE_H

#include <iostream>
#include <stdexcept>
#include <queue>

template <typename T>
class BoundedQueue
{
private:
    myQueue<T> myQueue;
    size_t maxSize;
    int currSize;

public:
    BoundedQueue(size_t size);

    void push(const T &value);

    void pop();

    T front() const;

    bool empty() const;

    size_t size() const;
};

#endif
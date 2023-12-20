#include <iostream>
#include <stdexcept> // for std::out_of_range
#include <queue>
using namespace std;

template <typename T>
class BoundedQueue
{
private:
    queue<T> myQueue; // Renamed to avoid conflict with std::queue
    size_t maxSize;
    int currSize;

public:
    BoundedQueue(size_t size) : maxSize(size), currSize(0) {}

    void push(const T &value)
    {
        if (currSize < maxSize)
        {
            myQueue.push(value);
            currSize++;
        }
        else
        {
            throw out_of_range("Queue is full. Cannot push.");
        }
    }

    void pop()
    {
        if (!myQueue.empty())
        {
            myQueue.pop();
            currSize--;
        }
        else
        {
            throw out_of_range("Queue is empty. Cannot pop.");
        }
    }

    T front() const
    {
        if (!myQueue.empty())
        {
            return myQueue.front();
        }
        else
        {
            throw out_of_range("Queue is empty. Cannot access front element.");
        }
    }

    bool empty() const
    {
        return myQueue.empty();
    }

    size_t size() const
    {
        return myQueue.size();
    }
};

#ifndef BOUNDEDQUEUE_H
#define BOUNDEDQUEUE_H

#include <iostream>
#include <stdexcept>
#include <queue>
using namespace std;

/**
 * @brief A template class representing a bounded queue.
 *
 * This class provides a fixed-size queue implementation with a maximum capacity.
 * The elements are stored in a queue data structure.
 *
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class BoundedQueue
{
private:
    queue<T> myQueue; /**< The underlying queue data structure. */
    size_t maxSize;   /**< The maximum capacity of the queue. */
    int currSize;     /**< The current number of elements in the queue. */

public:
    /**
     * @brief Constructs a new BoundedQueue object with the specified size.
     *
     * @param size The maximum capacity of the queue.
     */
    BoundedQueue(size_t size);

    /**
     * @brief Adds an element to the back of the queue.
     *
     * @param value The value to be added to the queue.
     */
    void enqueue(const T &value);

    /**
     * @brief Removes the element at the front of the queue.
     */
    void dequeue();

    /**
     * @brief Returns the element at the front of the queue without removing it.
     *
     * @return The element at the front of the queue.
     */
    T front() const;

    /**
     * @brief Checks if the queue is empty.
     *
     * @return True if the queue is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Returns the current number of elements in the queue.
     *
     * @return The number of elements in the queue.
     */
    size_t size() const;
};

#endif
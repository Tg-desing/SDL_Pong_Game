#ifndef QUEUE_H
#include <stdio.h>

template <typename t>
class Queue
{
public:
    t *arr;
    int front;
    int rear;
    int size;

    Queue(int size)
    {
        arr = new t[size];
        front = -1;
        rear = -1;
        this->size = size;
    }
    ~Queue()
    {
        delete[] arr;
    }

public:
    void enqueue(t data)
    {
        if ((rear + 1) % size == front)
        {
            printf("Queue is Full\n");
            return;
        }
        rear = (rear + 1) % size;
        arr[rear] = data;
    }

    t dequeue()
    {
        if (front == rear)
        {
            printf("Queue is Empty\n");
            return SDLK_SPACE;
        }
        front = (front + 1) % size;
        printf("%d\n", arr[front]);
        return arr[front];
    }

    int isEmpty()
    {
        if (front == rear)
        {
            return 1;
        }
        return 0;
    }
};

#endif
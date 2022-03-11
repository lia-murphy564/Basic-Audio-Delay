#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

class RingBuffer {
private:
    int* arr;
    int head, tail, num, size;

public:
    RingBuffer(int buffer_size) {
        size = buffer_size;
        arr = (int*)malloc(sizeof(int) * size);
        num = 0;
        head = 0;
        tail = 0;
    }

    ~RingBuffer() {
        free(arr);
    }

    bool empty() {
        return (num == 0);
    }

    bool full() {
        return (num == size);
    }

    void setOffset(int offset) {
        head = head;
        tail = tail + offset;
    }

    bool enqueue(int value) {
        if (full())
            return false;

        arr[tail] = value;

        num++;
        tail++;

        // wrap tail back to start
        if (tail >= size)
            tail = 0;

        return true;
    }

    int dequeue() {
        if (empty())
            return 0;

        int value = arr[head];
        num--;
        head++;

        if (head >= size)
            head = 0;

        return value;
    }
};

class AudioDelay {
private:
    RingBuffer* b;

public:
    AudioDelay(int buffer_size) {
        b = new RingBuffer(buffer_size);
    };

    ~AudioDelay() {
        delete b;
    };

    int processAudioSample(int xn, int delay_time, int fb_amt) {

        int yn, fb;

        b->setOffset(delay_time);

        yn = b->dequeue();

        fb = yn * fb_amt;

        xn += fb;

        b->enqueue(xn);

        return yn;
    }
};

/*
int main() {

    int buffer_size = 100;
    RingBuffer b(buffer_size);
    AudioDelay delay(buffer_size);

    while (true) {

        // read in buffer
        for (int i = 0; i < buffer_size; i++) {
            b.enqueue(i);
        }


        for (int i = 0; i < buffer_size; i++) {
            int xn = b.dequeue();
            int yn = delay.processAudioSample(xn, 4, 0.7);

            if (yn > 0)
                yn = yn;
            else
                yn = 0;
            std::cout << yn << "  ";
        }

    }
}
*/

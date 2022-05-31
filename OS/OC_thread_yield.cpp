#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string.h>

static bool KEEP_GOING = true;
static bool Next_Thread = false;

struct Point {
    long x;
    long y;
};

template<class T, size_t arraySize>
class SharedArray {
public:
    void get(size_t index, T* out) const {
        
        *out = _items[index];
    }

    void set(size_t index, const T& value) {
        
        _items[index] = value;
    }

    void clean() { memset(_items, 0, sizeof(_items)); }
private:
    T _items[arraySize];
    
};

#define SHARED_ARRAY_SIZE 10
static SharedArray<Point, SHARED_ARRAY_SIZE> SHARED_ARRAY;

void doWrites()
{
    Point p;
    p.x = 0;
    p.y = 0;
    while (true) {
        if (!KEEP_GOING)
            break;
        while (Next_Thread == true)
        {
            std::this_thread::yield();
        }
        for (size_t i = 0; i < SHARED_ARRAY_SIZE; ++i) 
        {
            SHARED_ARRAY.set(i, p);
            ++p.x;
            ++p.y;
        }
        Next_Thread = true;
       
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void doReads()
{
    while (true) 
    {
        while (Next_Thread == false)
        {
            std::this_thread::yield();
        }

        if (!KEEP_GOING)
            break;
        
        for (size_t k = 0; k < SHARED_ARRAY_SIZE; ++k) 
        {
            Point r;
            SHARED_ARRAY.get(k, &r);
            std::cout << "x=" << r.x << " y=" << r.y << "\n";
        }
        
        Next_Thread = false;
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    SHARED_ARRAY.clean();
    std::thread writer(&doWrites);
    std::thread reader(&doReads);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    KEEP_GOING = false;
    writer.join();
    reader.join();
}
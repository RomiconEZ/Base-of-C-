#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string.h>


static bool KEEP_GOING = true;
//HANDLE mainThread;

struct Point {
    long x;
    long y;
};

template<class T, size_t arraySize>
class SharedArray {
public:
    void get(size_t index, T* out) const {
        std::lock_guard<std::mutex> lockit(_mtx);
        *out = _items[index];
    }

    void set(size_t index, const T& value) {
        std::lock_guard<std::mutex> lockit(_mtx);
        _items[index] = value;
    }

    void clean() { memset(_items, 0, sizeof(_items)); }
private:
    T _items[arraySize];
    mutable std::mutex _mtx;
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
        for (size_t i = 0; i < SHARED_ARRAY_SIZE; ++i) {
            SHARED_ARRAY.set(i, p);
            ++p.x;
            ++p.y;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void doReads()
{
    while (true) {
        if (!KEEP_GOING)
            break;
        for (size_t k = 0; k < SHARED_ARRAY_SIZE; ++k) {
            Point r;
            SHARED_ARRAY.get(k, &r);
            std::cout << "x=" << r.x << " y=" << r.y << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {

    //auto mainThread = GetCurrentThread();
    //int core = 1;
    //auto mask = (static_cast<DWORD_PTR>(1) << core);//core number starts from 0
    //SetThreadAffinityMask(mainThread, mask);

    SHARED_ARRAY.clean();
    std::thread writer(&doWrites);
    std::thread reader(&doReads);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    KEEP_GOING = false;
    writer.join();
    reader.join();
}
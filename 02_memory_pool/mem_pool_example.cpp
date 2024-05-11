#include "mem_pool.h"


struct MyObject {
    int data[10];
};


int main() {
    using namespace Common;
    MemPool<double> pool1(50);
    MemPool<MyObject> pool2(50);

    for (int i = 0; i < 50; ++i) {
        auto p1 = pool1.allocate(i);
        auto p2 = pool2.allocate(MyObject{i, i + 10, i + 20});

        if (i % 10 == 0) {
            std::cout << "Deallocate prim elem: " << *p1 << " allocated in " << p1 << std::endl;
            pool1.deallocate(p1);

            std::cout << "Deallocate prim elem: " << p2->data[0] << " allocated in " << p2 << std::endl;
            pool2.deallocate(p2);
        }

    }
}
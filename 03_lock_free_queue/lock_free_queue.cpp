#include "lock_free_queue.h"
#include "../01_thread_affinity/thread_utils.h"


struct MyStruct {
    int data[3];
};

using namespace Common;


auto consumeFoo(LFQueue<MyStruct>* lfq) {
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(5s);

    while (lfq->size()) {
        const auto d = lfq->getNextToRead();
        lfq->updateReadIndex();

        std::cout << "Read " << d->data[0] << " " << d->data[1] << " " << d->data[2] << " queue size " << lfq->size() << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main() {
    LFQueue<MyStruct> lfq(100);
    auto ct = createAndStartThread(-1, "", consumeFoo, &lfq);
    for (int i = 0; i < 100; ++i) {
        const MyStruct d{i, i + 1, i + 2};
        *(lfq.getNextToWrite()) = d;
        lfq.updateWriteIndex();

        std::cout << "Write " << d.data[0] << " " << d.data[1] << " " << d.data[2] << lfq.size() << std::endl;
        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
    }
    ct->join();
    std::cout << "Finish" << std::endl;
    return 0;
}
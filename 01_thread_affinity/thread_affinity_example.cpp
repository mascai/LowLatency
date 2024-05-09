#include "thread_utils.h"

#include <format>



auto Foo(int a, int b, bool sleep) {
    std::cout << std::format("{} + {} = {}", a, b, a + b) << std::endl;
    if (sleep) {
        std::cout << "Sleeping..." << std::endl;

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(3s);

    }
}


int main() {
    using namespace Common;

    auto* t1 = createAndStartThread(-1, "noAffinity", Foo, 12, 21, false);
    auto* t2 = createAndStartThread(1, "Core1Affinity", Foo, 123, 21, true);

    std::cout << "Waiting for threads" << std::endl;
    t1->join();
    t2->join();
    std::cout << "Finish main thread" << std::endl;
    return 0;
}
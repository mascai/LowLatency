#pragma once

#include <sys/syscall.h>

#include <iostream>
#include <thread>

namespace Common {
    inline bool setAffinity(int coreId) noexcept {
        // Set current thread for CPU coreId
        cpu_set_t cpuSet;
        CPU_ZERO(&cpuSet);
        CPU_SET(coreId, &cpuSet);
        return (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuSet) == 0);
    }

    template<class T, class... Args>
    inline auto createAndStartThread(int coreId, const std::string& name, T&& func, Args&&... args) noexcept {
        auto t = new std::thread([&]() {
            if (coreId >= 0 and !setAffinity(coreId)) {
                std::cerr << "Failed to set affinity for << " << name << ' ' << pthread_self() << " to core " << coreId << std::endl;
            }
            std::cout << "Set affinity for << " << name << ' ' << pthread_self() << " to core " << coreId << std::endl;
            std::forward<T>(func)((std::forward<Args>(args))...);
        });

        using namespace std::literals::chrono_literals;
        std::this_thread::sleep_for(1s);
        return t;
    }
}
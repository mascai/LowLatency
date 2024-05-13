#pragma once

#include <atomic>
#include <vector>
#include <iostream>

#include "../macros.h"


namespace Common {
    template<class T>
    class LFQueue final {
    public:
        LFQueue(size_t size) : store_(size, T()) {}
        auto getNextToWrite() noexcept {
            return &store_[next_write_index_];
        }

        void updateWriteIndex() noexcept {
            next_write_index_ = (next_write_index_ + 1) % store_.size();
            cur_size_++;
        }

        auto getNextToRead() const noexcept -> const T* {
            if (size()) {
                return &store_[next_read_index_];
            }
            return nullptr;
        }

        void updateReadIndex() noexcept {
            next_read_index_ = (next_read_index_ + 1) % store_.size();
            ASSERT(cur_size_ != 0, "Read an invalid element");
            cur_size_--;
        }

        auto size() const noexcept {
            return cur_size_.load();
        }

        LFQueue() = delete;
        LFQueue(const LFQueue&) = delete;
        LFQueue(const LFQueue&&) = delete;
        LFQueue& operator=(const LFQueue&) = delete;
        LFQueue& operator=(LFQueue&&) = delete;


    private:
        std::vector<T> store_;
        std::atomic<size_t> next_write_index_ = {0};
        std::atomic<size_t> next_read_index_ = {0};
        std::atomic<size_t> cur_size_ = {0};
    };
}
#pragma once

#include <vector>
#include <string>

#include "macros.h"


namespace Common {
    template<class T>
    class MemPool final {
    public:
        explicit MemPool(std::size_t pool_size) : store_(pool_size, {T(), true}) {
            ASSERT(reinterpret_cast<const Block*>(&(store_[0].object_)) == &(store_[0]), "T object should be the first member of Block.");
        }

        template<class... Args>
        T* allocate(Args... args) noexcept {
            auto block = &(store_[next_free_index_]);
            ASSERT(block->is_free_, "Expected free Block at index: " + std::to_string(next_free_index_));
            T* ret = &(block->object_);
            ret = new(ret) T(args...);
            block->is_free_ = false;

            updateNextFreeIndex();
            return ret;
        }

        auto deallocate(const T* elem) noexcept {
            const auto elem_index = reinterpret_cast<const Block*>(elem) - &store_[0];
            ASSERT(elem_index >= 0 and static_cast<size_t>(elem_index) < store_.size(), "Invali element " + std::to_string(elem_index));
            ASSERT(!store_[elem_index].is_free_, "Block expected to bee in-use " + std::to_string(elem_index));
            store_[elem_index].is_free_ = true;
        }

        MemPool() = delete;
        MemPool(const MemPool&) = delete;
        MemPool(const MemPool&&) = delete;


        MemPool& operator=(const MemPool&) = delete;
        MemPool& operator=(const MemPool&&) = delete;
    private:
        auto updateNextFreeIndex() noexcept {
            const auto initial_free_index = next_free_index_;
            while (not store_[next_free_index_].is_free_) {
                next_free_index_++;
                if (next_free_index_ == store_.size()) [[unlikelly]] {
                    next_free_index_ = 0;
                }
                if (initial_free_index == next_free_index_) [[unlikelly]] {
                    ASSERT(initial_free_index != next_free_index_, "Memory pool out of space");
                }
            }
        }
    
    private:
        struct Block {
            T object_;
            bool is_free_ = true;
        };

        size_t next_free_index_ = 0;
        std::vector<Block> store_;
    };
}
//
// Made by Egor
// 11 11 2025
//
#ifndef FIXED_BLOCK_MEMORY_RESOURCE_H
#define FIXED_BLOCK_MEMORY_RESOURCE_H

#include <memory_resource>
#include <vector>
#include <cstddef>

class FixedBlockMemoryResource : public std::pmr::memory_resource {
private:
    static constexpr size_t BLOCK_SIZE = 64;
    void* buffer_;
    size_t block_count_;
    std::vector<size_t> free_blocks_;
    std::vector<bool> allocated_blocks_;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    explicit FixedBlockMemoryResource(size_t num_blocks = 100);
    ~FixedBlockMemoryResource();
    size_t capacity() const;
    size_t free_count() const;
};

#endif
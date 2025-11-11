//
// Made by Egor
// 11 11 2025
//


#include "FixedBlockMemoryResource.h"
#include <stdexcept>



void* FixedBlockMemoryResource::do_allocate(size_t bytes, size_t alignment) {
    if (bytes > BLOCK_SIZE) {
        throw std::bad_alloc();
    }
    
    if (!free_blocks_.empty()) {
        size_t block_index = free_blocks_.back();
        free_blocks_.pop_back();
        allocated_blocks_[block_index] = true;
        return static_cast<char*>(buffer_) + block_index * BLOCK_SIZE;
    }
    
    throw std::bad_alloc();
}

void FixedBlockMemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    size_t offset = static_cast<char*>(ptr) - static_cast<char*>(buffer_);
    size_t block_index = offset / BLOCK_SIZE;
    
    if (block_index < block_count_ && allocated_blocks_[block_index]) {
        allocated_blocks_[block_index] = false;
        free_blocks_.push_back(block_index);
    }
}

bool FixedBlockMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

FixedBlockMemoryResource::FixedBlockMemoryResource(size_t num_blocks) 
    : block_count_(num_blocks) {
    buffer_ = ::operator new(num_blocks * BLOCK_SIZE);
    free_blocks_.reserve(num_blocks);
    allocated_blocks_.assign(num_blocks, false);
    
    for (size_t i = 0; i < num_blocks; ++i) {
        free_blocks_.push_back(i);
    }
}

FixedBlockMemoryResource::~FixedBlockMemoryResource() {
    ::operator delete(buffer_);
}

size_t FixedBlockMemoryResource::capacity() const { 
    return block_count_ * BLOCK_SIZE; 
}

size_t FixedBlockMemoryResource::free_count() const { 
    return free_blocks_.size(); 
}
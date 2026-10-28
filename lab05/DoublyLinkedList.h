//
// Made by Egor
// 11 11 2025
//
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


#include <memory_resource>
#include <iterator>



template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };
    
    using Allocator = std::pmr::polymorphic_allocator<Node>;
    
    Node* head_;
    Node* tail_;
    size_t size_;
    Allocator allocator_;
    
public:
    class Iterator {
    private:
        Node* current_;
        
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        explicit Iterator(Node* node = nullptr) : current_(node) {}
        
        reference operator*() const { return current_->data; }
        pointer operator->() const { return &current_->data; }
        
        Iterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }
        
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };
    
    explicit DoublyLinkedList(std::pmr::memory_resource* mr) 
        : head_(nullptr), tail_(nullptr), size_(0), allocator_(mr) {}
    
    ~DoublyLinkedList() {
        clear();
    }
    
    void push_back(const T& value) {
        Node* new_node = allocator_.allocate(1);
        allocator_.construct(new_node, Node{value, tail_, nullptr});
        
        if (!head_) {
            head_ = tail_ = new_node;
        } else {
            tail_->next = new_node;
            tail_ = new_node;
        }
        ++size_;
    }
    
    void push_front(const T& value) {
        Node* new_node = allocator_.allocate(1);
        allocator_.construct(new_node, Node{value, nullptr, head_});
        
        if (!head_) {
            head_ = tail_ = new_node;
        } else {
            head_->prev = new_node;
            head_ = new_node;
        }
        ++size_;
    }
    
    void pop_front() {
        if (!head_) return;
        
        Node* old_head = head_;
        head_ = head_->next;
        
        if (head_) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        
        allocator_.destroy(old_head);
        allocator_.deallocate(old_head, 1);
        --size_;
    }
    
    void clear() {
        while (head_) {
            pop_front();
        }
    }
    
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
    
    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
    
    Iterator begin() const { return Iterator(head_); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif
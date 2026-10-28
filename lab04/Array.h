#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>
#include <iostream>

// шаблонный динамический массив
template<typename T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void resize(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        std::cout << "--- resize: " << capacity_ << " -> " << new_capacity << " (moving " << size_ << " elements) ---\n";

        // Создаем новый массив вручную без вызова конструкторов
        T* raw_new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        auto new_data = std::shared_ptr<T[]>(raw_new_data, [](T* ptr) { ::operator delete(ptr); });

        // Перемещаем существующие элементы
        for(size_t i = 0; i < size_; ++i) {
            std::cout << "moving element [" << i << "] from old array to new array\n";
            new (&new_data[i]) T(std::move(data[i]));  // placement new + move
            data[i].~T();  // уничтожаем старый объект
        }

        data = new_data;
        capacity_ = new_capacity;
        std::cout << "--- resize completed ---\n\n";
    }

public:
    Array() = default;

    explicit Array(size_t initial_capacity) {
        if (initial_capacity > 0) {
            T* raw_data = static_cast<T*>(::operator new(initial_capacity * sizeof(T)));
            data = std::shared_ptr<T[]>(raw_data, [](T* ptr) { ::operator delete(ptr); });
            capacity_ = initial_capacity;
            std::cout << "array created with capacity: " << capacity_ << "\n";
        }
    }

    ~Array() {
        // Явно вызываем деструкторы для всех объектов
        for(size_t i = 0; i < size_; ++i) {
            data[i].~T();
        }
    }

    void push_back(const T& item) {
        if(size_ >= capacity_) {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        new (&data[size_]) T(item);  // placement new + copy
        size_++;
    }

    void push_back(T&& item) {
        if(size_ >= capacity_) {
            resize(capacity_ == 0 ? 2 : capacity_ * 2);
        }
        new (&data[size_]) T(std::move(item));  // placement new + move
        size_++;
    }

    void remove(size_t index) {
        if(index >= size_) throw std::out_of_range("Index out of range");

        data[index].~T();  // уничтожаем удаляемый элемент

        // Перемещаем остальные элементы
        for(size_t i = index; i < size_ - 1; ++i) {
            new (&data[i]) T(std::move(data[i + 1]));  // move + placement new
            data[i + 1].~T();  // уничтожаем старый
        }
        size_--;
    }

    T& operator[](size_t index) {
        if(index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if(index >= size_) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    // для проверки перемещенных элементов (только для указателей)
    bool is_moved(size_t index) const {
        if constexpr (std::is_pointer_v<T>) {
            return data[index] == nullptr;
        }
        return false;
    }
};

#endif
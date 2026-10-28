
// Сделал Егор Колосов
// Made by Egor
// 10 01 2025
#include "Five.h"
#include <iostream>
#include <stdexcept>
#include <string>

Five::Five(const std::string& str) {
    if (str.empty()) {
        digits.push_back(0);
        return;
    }

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c < '0' || c > '4') {
            throw std::invalid_argument("Wrong number in string");
        }
    }

    for (int i = str.length() - 1; i >= 0; i--) {
        digits.push_back(str[i] - '0');
    }
}

Five::Five(int decimal) {
    if (decimal < 0) {
        throw std::invalid_argument("Negative number not allowed");
    }

    if (decimal == 0) {
        digits.push_back(0);
        return;
    }

    int temp_var = decimal; // необязательная переменная, но пусть будет
    while (temp_var > 0) {
        digits.push_back(temp_var % 5);
        temp_var /= 5;
    }
}

Five Five::add(const Five& other) const {
    return addDirect(other);
}

Five Five::subtract(const Five& other) const {
    if (less(other)) {
        return Five("0");
    }
    return subDirect(other);
}

Five Five::addDirect(const Five& other) const {
    std::vector<unsigned char> result;
    int carry = 0;
    int maxsize = digits.size();
    if (other.digits.size() > maxsize) maxsize = other.digits.size();

    for (int i = 0; i < maxsize || carry; i++) {
        int sum = carry;

        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];

        result.push_back(sum % 5);
        carry = sum / 5;
    }

    Five res;
    res.digits = result;
    return res;
}

Five Five::subDirect(const Five& other) const {
    std::vector<unsigned char> result;
    int borrow = 0;

    for (int i = 0; i < digits.size(); i++) {
        int diff = digits[i] - borrow;

        if (i < other.digits.size()) {
            if (diff < other.digits[i]) {
                diff += 5;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diff -= other.digits[i];
        } else {
            borrow = 0;
        }

        result.push_back(diff);
    }

    // удаляем ведущие нули
    while (result.size() > 1 && result[result.size() - 1] == 0) {
        result.pop_back();
    }

    Five res;
    res.digits = result;
    return res;
}

Five Five::assign(const Five& other) const {
    // просто копируем
    return Five(other);
}

bool Five::equals(const Five& other) const {
    if (digits.size() != other.digits.size()) return false;

    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Five::less(const Five& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }

    for (int i = digits.size() - 1; i >= 0; i--) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}

bool Five::greater(const Five& other) const {
    if (equals(other)) return false;
    return !less(other);
}

size_t Five::size() const {
    return digits.size();
}

unsigned char Five::getDigit(size_t index) const {
    if (index >= digits.size()) {
        throw std::out_of_range("Index out of range");
    }
    return digits[index];
}

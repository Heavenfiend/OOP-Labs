#ifndef FIVE_H
#define FIVE_H

#include <vector>
#include <string>

class Five {
private:
    std::vector<unsigned char> digits;

    Five addDirect(const Five& other) const;
    Five subDirect(const Five& other) const;

public:
    Five();
    Five(const std::string& str);
    Five(int decimal);
    Five(const Five& other);

    Five& operator=(const Five& other);

    Five add(const Five& other) const;
    Five subtract(const Five& other) const;

    bool equals(const Five& other) const;
    bool less(const Five& other) const;
    bool greater(const Five& other) const;

    size_t size() const;
    unsigned char getDigit(size_t index) const;
    Five assign(const Five& other) const;

    std::string toString() const;
    void print() const;
    int toDecimal() const;
};

#endif
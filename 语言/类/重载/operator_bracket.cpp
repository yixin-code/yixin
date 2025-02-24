#include <iostream>
#include <cstring>

class Array {
public:
    Array(int size) : m_size(size), m_p(new int[size]{0}) {
        std::cout << "Array(int size) : m_size(size), m_p(new int[size]{0})" << std::endl;
    }
    Array(const Array &other) {
        std::cout << "Array(const Array &other)" << std::endl;
        if (this == &other) {
            return;
        }

        m_size = other.m_size;
        m_p = new int[other.m_size];
        memcpy(m_p, other.m_p, other.m_size * sizeof(int));
    }
    ~Array() {
        std::cout << "~Array()" << std::endl;
        delete[] m_p;
    }

public:
    Array& operator=(const Array &other) {
        std::cout << "Array& operator=(const Array &other)" << std::endl;
        if (this == &other) {
            return *this;
        }

        m_size = other.m_size;
        delete[] m_p; // 释放原空间

        if (other.m_p != nullptr) {
            m_p = new int[other.m_size];
            memcpy(m_p, other.m_p, other.m_size * sizeof(int));
        } else {
            m_p = nullptr;
        }

        return *this;
    }

    int& operator[](int index) {
        if (index >= m_size || index < 0) {
            std::cout << "array bound, return m_p[0]" << std::endl;
            return m_p[0];
        }
        return m_p[index];
    }
public:
    void display() const {
        std::cout << "m_p: " << m_p << std::endl;
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_p[i] << ' ';
        }
        std::cout << std::endl;
    }
private:
    int m_size;
    int *m_p;
};

int main(int argc, char *argv[]) {
    Array a(11);
    Array b(2);
    a.display();
    b.display();
    b = a;
    a[1] = 11;
    b[1] = 22;
    a.display();
    b.display();

    return 0;
}
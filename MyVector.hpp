#pragma once
#include <cstddef>

template <typename T>
class MyVector {
public:
    MyVector();
    MyVector(size_t size);
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    ~MyVector();

    void push_back(const T& element);
    void pop_back();
    void insertAt(size_t index, const T& element);
    void removeAt(size_t index);
    void shrink_to_fit();
    void clear();
    bool isEmpty() const;
    size_t size() const;
    size_t capacity() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

private:
    static constexpr size_t INITIAL_CAPACITY = 8;

    size_t _size;
    size_t _capacity;
    T* _data;

    void free();
    void copyFrom(const MyVector& other);
    void resize(size_t newCapacity);
    static size_t getNextPowerOfTwo(size_t number);
};

// === Implementation ===

template <typename T>
MyVector<T>::MyVector() : _size(0), _capacity(INITIAL_CAPACITY), _data(new T[_capacity]) {}

template <typename T>
MyVector<T>::MyVector(size_t size) : _size(size), _capacity(getNextPowerOfTwo(size)), _data(new T[_capacity]) {}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) {
    copyFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    free();
}

template <typename T>
void MyVector<T>::push_back(const T& element) {
    if (_size >= _capacity)
        resize(_capacity * 2);
    _data[_size++] = element;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (_size > 0)
        --_size;
}

template <typename T>
void MyVector<T>::insertAt(size_t index, const T& element) {
    if (index > _size)
        return;
    if (_size >= _capacity)
        resize(_capacity * 2);
    for (size_t i = _size; i > index; --i)
        _data[i] = _data[i - 1];
    _data[index] = element;
    ++_size;
}

template <typename T>
void MyVector<T>::removeAt(size_t index) {
    if (index >= _size)
        return;
    for (size_t i = index; i < _size - 1; ++i)
        _data[i] = _data[i + 1];
    --_size;
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
    resize(_size);
}

template <typename T>
void MyVector<T>::clear() {
    _size = 0;
}

template <typename T>
bool MyVector<T>::isEmpty() const {
    return _size == 0;
}

template <typename T>
size_t MyVector<T>::size() const {
    return _size;
}

template <typename T>
size_t MyVector<T>::capacity() const {
    return _capacity;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return _data[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return _data[index];
}

template <typename T>
void MyVector<T>::free() {
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
        _data[i] = other._data[i];
}

template <typename T>
void MyVector<T>::resize(size_t newCapacity) {
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < _size; ++i)
        newData[i] = _data[i];
    delete[] _data;
    _data = newData;
    _capacity = newCapacity;
}

template <typename T>
size_t MyVector<T>::getNextPowerOfTwo(size_t number) {
    size_t power = INITIAL_CAPACITY;
    while (power < number)
        power *= 2;
    return power;
}

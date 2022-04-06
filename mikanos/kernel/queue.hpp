#pragma once

#include <cstddef>
#include <array>

#include "error.hpp"

// #@@range_begin(class)
template <typename T>
class ArrayQueue {
public:
    template <size_t N>
    ArrayQueue(std::array<T, N>& buf);
    ArrayQueue(T* buf, size_t size);
    Error Push(const T& value);
    Error Pop();
    size_t Count() const;
    size_t Capacity() const;
    const T& Front() const;

private:
    T* m_data;
    size_t m_readPos, m_writePos, m_count;

    const size_t m_capacity;
};
// #@@range_end(class)

// #@@range_begin(constructor)
template <typename T>
template <size_t N>
ArrayQueue<T>::ArrayQueue(std::array<T, N>& buf) : ArrayQueue(buf.data(), N) {}

template <typename T>
ArrayQueue<T>::ArrayQueue(T* buf, size_t size)
    : m_data{buf}, m_readPos{0}, m_writePos{0}, m_count{0}, m_capacity{size}
{}
// #@@range_end(constructor)

// #@@range_begin(push)
template <typename T>
Error ArrayQueue<T>::Push(const T& value) {
    if (m_count == m_capacity) {
        return MAKE_ERROR(Error::kFull);
    }

    m_data[m_writePos] = value;
    ++m_count;
    ++m_writePos;
    if (m_writePos == m_capacity) {
        m_writePos = 0;
    }
    return MAKE_ERROR(Error::kSuccess);
}
// #@@range_end(push)

// #@@range_begin(pop)
template <typename T>
Error ArrayQueue<T>::Pop() {
    if (m_count == 0) {
        return MAKE_ERROR(Error::kEmpty);
    }

    --m_count;
    ++m_readPos;
    if (m_readPos == m_capacity) {
        m_readPos = 0;
    }
    return MAKE_ERROR(Error::kSuccess);
}
// #@@range_end(pop)

template <typename T>
size_t ArrayQueue<T>::Count() const {
    return m_count;
}

template <typename T>
size_t ArrayQueue<T>::Capacity() const {
    return m_capacity;
}

// #@@range_begin(front)
template <typename T>
const T& ArrayQueue<T>::Front() const {
    return m_data[m_readPos];
}
// #@@range_end(front)
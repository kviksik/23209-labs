#include "Cbuff.h"
#include <stdexcept>
#include <algorithm>

// Конструкторы и деструктор
CircularBuffer::CircularBuffer() :
        buffer(nullptr), buf_capacity(0), buf_size(0), head(0), tail(0) {}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

CircularBuffer::CircularBuffer(int capacity) :
        buffer(new value_type[capacity]), buf_capacity(capacity), buf_size(0), head(0), tail(0) {}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem) :
        buffer(new value_type[capacity]), buf_capacity(capacity), buf_size(capacity), head(0), tail(0) {
    std::fill(buffer, buffer + capacity, elem);
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb):
        buffer(new value_type[cb.buf_capacity]), buf_capacity(cb.buf_capacity), buf_size(cb.buf_size), head(cb.head), tail(cb.tail) {
    std::copy(cb.buffer, cb.buffer + buf_capacity, buffer);
}

// Оператор присваивания
CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
    if (this != &cb) {
        delete[] buffer;
        buf_capacity = cb.buf_capacity;
        buf_size = cb.buf_size;
        head = cb.head;
        tail = cb.tail;
        buffer = new value_type[buf_capacity];
        std::copy(cb.buffer, cb.buffer + buf_capacity, buffer);
    }
    return *this;
}

// Доступ по индексу (непроверяемый)
value_type& CircularBuffer::operator[](int i) {
    return buffer[(head + i) % buf_capacity];
}
const value_type& CircularBuffer::operator[](int i) const {
    return buffer[(head + i) % buf_capacity];
}

// Доступ по индексу с проверкой
value_type& CircularBuffer::at(int i) {
    if (i < 0 || i >= buf_size) throw std::out_of_range("Index out of range");
    return (*this)[i];
}
const value_type& CircularBuffer::at(int i) const {
    if (i < 0 || i >= buf_size) throw std::out_of_range("Index out of range");
    return (*this)[i];
}

// Доступ к первому и последнему элементам
value_type& CircularBuffer::front() {
    return buffer[head];
}

const value_type& CircularBuffer::front() const {
    return buffer[head];
}

value_type& CircularBuffer::back() {
    return buffer[(tail - 1 + buf_capacity) % buf_capacity];
}

const value_type& CircularBuffer::back() const {
    return buffer[(tail - 1 + buf_capacity) % buf_capacity];
}

value_type* CircularBuffer::linearize() {
    if (!is_linearized()) {
        value_type* new_buffer = new value_type[buf_capacity];
        for (int i = 0; i < buf_size; ++i) {
            new_buffer[i] = (*this)[i];
        }
        delete[] buffer;
        buffer = new_buffer;
        head = 0;
        tail = buf_size;
    }
    return buffer;
}

bool CircularBuffer::is_linearized() const {
    return head == 0;
}

// Сдвиг; element[0] == new_begin
void CircularBuffer::rotate(int new_begin) {
    if (new_begin < 0 || new_begin >= buf_size) throw std::out_of_range("Index out of range");
    head = (head + new_begin) % buf_capacity;
    tail = (head + buf_size) % buf_capacity;
}

int CircularBuffer::size() const {
    return buf_size;
}
bool CircularBuffer::empty() const {
    return buf_size == 0;
}
bool CircularBuffer::full() const {
    return buf_size == buf_capacity;
}
int CircularBuffer::reserve() const {
    return buf_capacity - buf_size;
}
int CircularBuffer::capacity() const {
    return buf_capacity;
}

void CircularBuffer::set_capacity(int new_capacity) {
    if (new_capacity < buf_size) throw std::invalid_argument("New capacity too small");
    value_type* new_buffer = new value_type[new_capacity];
    for (int i = 0; i < buf_size; ++i) {
        new_buffer[i] = (*this)[i];
    }
    delete[] buffer;
    buffer = new_buffer;
    buf_capacity = new_capacity;
    head = 0;
    tail = buf_size;
}

void CircularBuffer::resize(int new_size, const value_type& item) {
    if (new_size > buf_capacity) {
        set_capacity(new_size);
    }
    while (new_size > buf_size) {
        push_back(item);
    }
    while (new_size < buf_size) {
        pop_back();
    }
}

void CircularBuffer::push_back(const value_type& item) {
    if (full()) head = (head + 1) % buf_capacity;
    else ++buf_size;
    buffer[tail] = item;
    tail = (tail + 1) % buf_capacity;
}

void CircularBuffer::push_front(const value_type& item) {
    if (full()) tail = (tail - 1 + buf_capacity) % buf_capacity;
    else ++buf_size;
    head = (head - 1 + buf_capacity) % buf_capacity;
    buffer[head] = item;
}

void CircularBuffer::pop_back() {
    if (empty()) throw std::out_of_range("Buffer is empty");
    tail = (tail - 1 + buf_capacity) % buf_capacity;
    --buf_size;
}

void CircularBuffer::pop_front() {
    if (empty()) throw std::out_of_range("Buffer is empty");
    head = (head + 1) % buf_capacity;
    --buf_size;
}

// Вставка и удаление элементов по индексу
void CircularBuffer::insert(int pos, const value_type& item) {
    if (pos < 0 || pos > buf_size) throw std::out_of_range("Index out of range");
    push_back();
    for (int i = buf_size - 1; i > pos; --i) {
        (*this)[i] = (*this)[i - 1];
    }
    (*this)[pos] = item;
}

// Удаляет элементы из буфера в интервале
void CircularBuffer::erase(int first, int last) {
    if (first < 0 || last > buf_size || first >= last) throw std::out_of_range("Invalid range");
    for (int i = first; i < buf_size - (last - first); ++i) {
        (*this)[i] = (*this)[i + (last - first)];
    }
    buf_size -= (last - first);
    tail = (head + buf_size) % buf_capacity;
}

void CircularBuffer::clear() {
    head = 0;
    tail = 0;
    buf_size = 0;
}

void CircularBuffer::swap(CircularBuffer& cb) {
    std::swap(buffer, cb.buffer);
    std::swap(buf_capacity, cb.buf_capacity);
    std::swap(buf_size, cb.buf_size);
    std::swap(head, cb.head);
    std::swap(tail, cb.tail);
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
    return !(a == b);
}

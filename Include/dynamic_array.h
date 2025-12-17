#pragma once
template <typename T>
struct DynamicArray {
    T* data;
    int size;
    int cap;

    DynamicArray() : data(nullptr), size(0), cap(0) {}
    ~DynamicArray() { delete[] data; }

    void reserve(int newCap) {
        if (newCap <= cap) return;
        T* nd = new T[newCap];
        for (int i = 0; i < size; i++) nd[i] = data[i];
        delete[] data;
        data = nd;
        cap = newCap;
    }

    void push_back(const T& v) {
        if (size == cap) reserve(cap == 0 ? 4 : cap * 2);
        data[size++] = v;
    }

    void removeAt(int idx) {
        if (idx < 0 || idx >= size) return;
        for (int i = idx; i < size - 1; i++) data[i] = data[i + 1];
        size--;
    }

    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }
};

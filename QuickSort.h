#pragma once

#include <cstddef>
#include <cstdint>
template<typename T>
class QuickSort
{
public:
    QuickSort(T* arr, size_t size)
        : arr_(arr)
    {
        sort(0, size - 1);
    }

private:
    void sort(std::int64_t l, std::int64_t r);
    std::int64_t split(std::int64_t l, std::int64_t r);
    void swap(std::int64_t l, std::int64_t r)
    {
        auto t = arr_[r];
        arr_[r] = arr_[l];
        arr_[l] = t;
    }

    T* arr_;
};

template<typename T>
void QuickSort<T>::sort(std::int64_t l, std::int64_t r)
{
    if (l >= r)
        return;

    auto x = split(l, r);
    sort(l, x - 1);
    sort(x + 1, r);
}

template<typename T>
std::int64_t QuickSort<T>::split(std::int64_t l, std::int64_t r)
{
    auto p = arr_[r];
    auto a = l - 1;
    for (auto m = l; m <= r; ++m) {
        if (arr_[m] <= p) {
            swap(++a, m);
        }
    }

    return a;
}

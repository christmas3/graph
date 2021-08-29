#pragma once

#include <iterator>
#include <memory>

namespace graph {

struct Edge
{
    int v1, v2;
};

struct BaseGraph
{
    virtual ~BaseGraph() = default;

    virtual size_t sizeV() const = 0;
    virtual size_t sizeE() const = 0;
    virtual bool insert(const Edge&) = 0;

    struct Iterator;

    virtual Iterator begin(size_t v) = 0;
    virtual Iterator end(size_t v) = 0;

    virtual const Iterator cbegin(size_t v) const = 0;
    virtual const Iterator cend(size_t v) const = 0;

    virtual void print() const = 0;

    virtual std::unique_ptr<BaseGraph> createEmpty() const = 0;

    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = value_type*;
        using reference = value_type&;

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }
        Iterator& operator++()
        {
            ++ptr_;
            return *this;
        }
        Iterator operator++(int)
        {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& l, const Iterator& r) { return l.ptr_ == r.ptr_; }
        friend bool operator!=(const Iterator& l, const Iterator& r) { return !(l == r); }

        explicit Iterator(pointer ptr = nullptr)
            : ptr_(ptr)
        {
        }

    private:
        pointer ptr_;
    };
};

inline void reverseGraph(const BaseGraph& in, BaseGraph& out)
{
    for (size_t i = 0; i < in.sizeV(); ++i) {
        for (auto iter = in.cbegin(i); iter != in.cend(i); ++iter) {
            out.insert({ *iter, (int)i });
        }
    }
}

} // namespace graph

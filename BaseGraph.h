#pragma once

#include <iterator>
#include <memory>

namespace graph {

struct Edge
{
    int v1, v2;
};

template<typename T, typename E = Edge>
struct BaseGraph
{
    virtual ~BaseGraph() = default;

    virtual size_t sizeV() const = 0;
    virtual size_t sizeE() const = 0;
    virtual bool insert(const E&) = 0;

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
        using value_type = T;
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

template<typename T, typename E>
inline void reverseGraph(const BaseGraph<T, E>& in, BaseGraph<T, E>& out)
{
    for (size_t i = 0; i < in.sizeV(); ++i) {
        for (auto iter = in.cbegin(i); iter != in.cend(i); ++iter) {
            out.insert({ *iter, (int)i });
        }
    }
}

using BaseGraphVertex = BaseGraph<int, Edge>;

struct EdgeWeighted : public Edge
{
    int weight;
    bool from(int v) const { return v1 == v; }
};

inline std::ostream& operator<<(std::ostream& out, const EdgeWeighted& e)
{
    return out << "v1: " << e.v1 << " v2: " << e.v2 << " weight: " << e.weight << std::endl;
}

inline bool operator==(const EdgeWeighted& l, const EdgeWeighted& r)
{
    return l.v1 == r.v1 && l.v2 == r.v2 && l.weight == r.weight;
}

inline bool operator!=(const EdgeWeighted& l, const EdgeWeighted& r)
{
    return !(l == r);
}

inline bool operator<(const EdgeWeighted& l, const EdgeWeighted& r)
{
    return l.weight < r.weight;
}

inline bool operator<=(const EdgeWeighted& l, const EdgeWeighted& r)
{
    return l.weight <= r.weight;
}

using BaseGraphWeighted = BaseGraph<EdgeWeighted, EdgeWeighted>;

inline EdgeWeighted getEdge(const BaseGraphWeighted& g, int v1, int v2)
{
    for (auto iter = g.cbegin(v1); iter != g.cend(v1); ++iter) {
        auto v = iter->from(v1) ? iter->v2 : iter->v1;
        if (v == v2) {
            return *iter;
        }
    }

    return {};
}

template<typename Vec>
inline Vec edges(const BaseGraphWeighted& g)
{
    Vec result(g.sizeE());

    for (int i = 0; i < g.sizeV(); ++i) {
        for (auto iter = g.cbegin(i); iter != g.cend(i); ++iter) {
            if (iter->from(i)) {
                result.putBack(*iter);
            }
        }
    }

    return result;
}

} // namespace graph

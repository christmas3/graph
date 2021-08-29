#pragma once

#include "BaseGraph.h"

#include <cstring>

namespace graph {
class StrengthComponentsK
{
public:
    explicit StrengthComponentsK(const BaseGraph& g)
        : graph_(g)
        , id_(new int[g.sizeV()])
        , postI_(new int[g.sizeV()])
        , curId_(0)
        , curV_(0)
        , postR_(new int[g.sizeV()])
    {
        memset(id_, emptyValue_, sizeof(int) * graph_.sizeV());
        auto reverse = graph_.createEmpty();
        reverseGraph(graph_, *reverse);
        for (size_t i = 0; i < reverse->sizeV(); ++i) {
            if (id_[i] == emptyValue_) {
                dfs(*reverse, (int)i);
            }
        }
        memcpy(postR_, postI_, sizeof(int) * graph_.sizeV());
        curV_ = curId_ = 0;
        memset(id_, emptyValue_, sizeof(int) * graph_.sizeV());
        for (int i = graph_.sizeV() - 1; i >= 0; --i) {
            if (id_[postR_[i]] == emptyValue_) {
                dfs(graph_, postR_[i]);
                ++curId_;
            }
        }
    }

    virtual ~StrengthComponentsK()
    {
        delete[] id_;
        delete[] postI_;
        delete[] postR_;
    }

    int* result() { return id_; }

private:
    void dfs(const BaseGraph& g, int v)
    {
        id_[v] = curId_;
        for (auto iter = g.cbegin(v); iter != g.cend(v); ++iter) {
            if (id_[*iter] == emptyValue_) {
                dfs(g, *iter);
            }
        }
        postI_[curV_++] = v;
    }

    const BaseGraph& graph_;
    int* id_;
    int* postI_;
    int curId_;
    int curV_;
    int* postR_;

    static const int emptyValue_ = -1;
};
} // namespace graph

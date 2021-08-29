#include <gtest/gtest.h>

#include "AdjacentVectorGraph.h"
#include "StrengthComponents.h"

static std::string delim(80, '=');

TEST(GraphSuit, KosarajuTest)
{
    std::unique_ptr<graph::BaseGraph> g(new graph::AdjacentVectorGraph(8, 3));

    EXPECT_EQ(g->sizeE(), 0);
    EXPECT_EQ(g->sizeV(), 8);

    EXPECT_TRUE(g->insert({ 0, 1 }));
    EXPECT_EQ(g->sizeE(), 1);

    EXPECT_TRUE(g->insert({ 1, 4 }));
    EXPECT_TRUE(g->insert({ 1, 5 }));
    EXPECT_TRUE(g->insert({ 1, 2 }));
    EXPECT_EQ(g->sizeE(), 4);

    EXPECT_TRUE(g->insert({ 2, 3 }));
    EXPECT_TRUE(g->insert({ 2, 6 }));
    EXPECT_EQ(g->sizeE(), 6);

    EXPECT_TRUE(g->insert({ 3, 2 }));
    EXPECT_TRUE(g->insert({ 3, 7 }));
    EXPECT_EQ(g->sizeE(), 8);

    EXPECT_TRUE(g->insert({ 4, 0 }));
    EXPECT_TRUE(g->insert({ 4, 5 }));
    EXPECT_EQ(g->sizeE(), 10);

    EXPECT_TRUE(g->insert({ 5, 6 }));
    EXPECT_EQ(g->sizeE(), 11);

    EXPECT_TRUE(g->insert({ 6, 5 }));
    EXPECT_EQ(g->sizeE(), 12);

    EXPECT_TRUE(g->insert({ 7, 3 }));
    EXPECT_TRUE(g->insert({ 7, 6 }));
    EXPECT_EQ(g->sizeE(), 14);

    std::unique_ptr<graph::BaseGraph> gReverse(new graph::AdjacentVectorGraph(8, 3));

    graph::reverseGraph(*g, *gReverse);

    graph::StrengthComponentsK sc(*g);

    auto* result = sc.result();

    std::cerr << "Strength components: ";
    for (size_t i = 0; i < g->sizeV(); ++i) {
        std::cerr << result[i] << " ";
    }
    std::cerr << std::endl;

    EXPECT_TRUE(result[5] == result[6]);
    EXPECT_TRUE(result[0] == result[1] && result[0] == result[4]);
    EXPECT_TRUE(result[2] == result[3] && result[2] == result[7]);
}

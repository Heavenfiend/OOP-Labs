// Made bu Egor 24/10/25
//
//
#include <gtest/gtest.h>
#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"
#include <sstream>
#include <cmath>

TEST(PentagonTest, Center) {
    std::vector<Point> vertices = {
        {1.0, 0.0},
        {0.309017, 0.951057},
        {-0.809017, 0.587785},
        {-0.809017, -0.587785},
        {0.309017, -0.951057}
    };
    Pentagon p(vertices);
    auto center = p.center();
    EXPECT_NEAR(center.first, 0.0, 1e-5);
    EXPECT_NEAR(center.second, 0.0, 1e-5);
}

TEST(PentagonTest, Area) {
    std::vector<Point> vertices = {
        {1.0, 0.0},
        {0.309017, 0.951057},
        {-0.809017, 0.587785},
        {-0.809017, -0.587785},
        {0.309017, -0.951057}
    };
    Pentagon p(vertices);
    double area = static_cast<double>(p);
    double expected = (5.0 / 2.0) * 1 * 1 * std::sin(2 * 3.141592653589793 / 5);
    EXPECT_NEAR(area, expected, 1e-3);
}

TEST(PentagonTest, Equality) {
    std::vector<Point> v1 = {
        {1.0, 0.0},
        {0.309017, 0.951057},
        {-0.809017, 0.587785},
        {-0.809017, -0.587785},
        {0.309017, -0.951057}
    };
    std::vector<Point> v2 = {
        {1.0, 0.0},
        {0.309017, 0.951057},
        {-0.809017, 0.587785},
        {-0.809017, -0.587785},
        {0.309017, -0.951057}
    };
    Pentagon p1(v1);
    Pentagon p2(v2);
    EXPECT_TRUE(p1 == p2);
}

TEST(HexagonTest, Center) {
    std::vector<Point> vertices = {
        {1.0, 0.0},
        {0.5, 0.866025},
        {-0.5, 0.866025},
        {-1.0, 0.0},
        {-0.5, -0.866025},
        {0.5, -0.866025}
    };
    Hexagon h(vertices);
    auto center = h.center();
    EXPECT_NEAR(center.first, 0.0, 1e-5);
    EXPECT_NEAR(center.second, 0.0, 1e-5);
}

TEST(FigureStreamTest, PentagonStream) {
    std::vector<Point> vertices = {
        {1.0, 0.0},
        {0.309017, 0.951057},
        {-0.809017, 0.587785},
        {-0.809017, -0.587785},
        {0.309017, -0.951057}
    };
    Pentagon p(vertices);
    std::stringstream ss;
    ss << p;
    EXPECT_TRUE(ss.str().find("Pentagon") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
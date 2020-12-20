//
// Created by yaoyu on 12/19/20.
//

#include <array>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "TypeUtils.hpp"

static void run_simple_variables() {
    std::cout << "Simple variables. \n";

    auto a = 0;
    PRINT_TYPE_NAME("auto a = 0", a)

    auto b = 0.0;
    PRINT_TYPE_NAME("auto b = 0.0", b)

    auto c = 0.0f;
    PRINT_TYPE_NAME("auto c = 0.0f", c)

    auto d = "abc";
    PRINT_TYPE_NAME("auto d = \"abc\"", d)

    auto& ra = a;
    PRINT_TYPE_NAME("auto& ra = a", ra)

    const auto& cra = a;
    PRINT_TYPE_NAME("const auto& cra = a", cra)

    auto e = 0, f = 0;
    PRINT_TYPE_NAME("auto e = 0, f = 0", e)

    // This is an error.
//    auto g = 0, h = 0.0;

    using namespace std::string_literals;
    auto s = "abc"s;
    PRINT_TYPE_NAME("auto s = \"abc\"", s);

    std::cout << "\n";
}

static void run_simple_sequences() {
    std::cout << "Simple sequences. \n";

    auto a = {1, 2, 3};
    PRINT_TYPE_NAME("auto a = {1, 2, 3}", a)

    std::vector b {1, 2, 3};
    PRINT_TYPE_NAME("std::vector b {1, 2, 3}", b)

    std::vector c0 = a;
    PRINT_TYPE_NAME("std::vector c0 = a", c0)

    // This is not allowed.
//    std::array c1 = a;
    std::array c1 {1,2};
    PRINT_TYPE_NAME("std::array c1 {1, 2}", c1)

    // This is not allowed.
//    auto d = {0, 0.0};
    std::pair d0 {0, 0.0};
    PRINT_TYPE_NAME("std::pair d0 {0, 0.0}", d0)

    auto d1 = std::make_tuple( 0, 0.0, 0.0f );
    PRINT_TYPE_NAME("auto d1 = std::make_tuple(0, 0.0, 0.0f)", d1)

    std::tuple d2 {0, 0.0, 0.0f};
    PRINT_TYPE_NAME("std::tuple d2 {0, 0.0, 0.0f}", d2)

    std::tuple d3 = a;
    PRINT_TYPE_NAME("std::tuple d3 = a", d3)

    std::map e { std::pair{ 0, 1.0 }, std::pair{ 2, 3.0 } };
    PRINT_TYPE_NAME("std::map e { std::pair{ 0, 1.0 }, std::pair{ 2, 3.0 } }", e)

    std::cout << "\n";
}

static auto add_two( const auto& a, const auto& b) {
    return a + b;
}

// Here, the type of the return value cannot be a third template.
// But auto is OK here.
template < typename T0, typename T1>
static auto add_two_t( const T0& a, const T1& b ) {
    return a + b;
}

template < typename T0, typename T1, typename T3 >
static T3 add_two_t3( const T0& a, const T1& b ) {
    return a + b;
}

// Parameter pack + fold expression in C++17.
template < typename ...TS >
static auto add_many( const TS& ...args ) {
    return ( args + ... );
}

static void run_functions_with_auto(){
    std::cout << "Functions with auto. \n";

    auto a = add_two( 0, 1 );
    PRINT_TYPE_NAME("auto a = add_two( 0, 1 )", a)

    auto b = add_two( 0, 1.0 );
    PRINT_TYPE_NAME("auto b = add_two( 0, 1.0 )", b)

    auto c = add_two( 0, 1.0f );
    PRINT_TYPE_NAME("auto c = add_two( 0, 1.0f )", c)

    auto d0 = add_two_t( 0, 1.0f );
    PRINT_TYPE_NAME("auto d0 = add_two_t(0, 1.0f)", d0)

    // This is an error.
//    auto d1 = add_two_t3(0, 1.0);
    auto d1 = add_two_t3<int, double, double>( 0, 1.0 );

    auto e0 = add_many( 0, 1, 2 );
    std::cout << "e0 = " << e0 << "\n";
    PRINT_TYPE_NAME("auto e0 = add_many( 0, 1, 2 )", e0)

    auto e1 = add_many( 0, 1.0, 2.0f );
    std::cout << "e1 = " << e1 << "\n";
    PRINT_TYPE_NAME("auto e1 = add_many( 0, 1.0, 2.0f )", e1)

    std::cout << "\n";
}

static void run_structured_binding() {
    std::cout << "Structured binding. \n";

    std::pair a { 0, 1.0 };
    auto [ a0, a1 ] = a;
    PRINT_TYPE_NAME("auto [a0, a1] = a; a0", a0)
    PRINT_TYPE_NAME("auto [a1, a1] = a; a1", a1)

    auto& [a2, a3] = a;
    PRINT_TYPE_NAME("auto& [a2, a3] = a; a2", a2)

    const auto& [a4, a5] = a;
    PRINT_TYPE_NAME("const auto& [a4, a5] = a; a4", a4)

    auto& [a6, a7] {a};
    PRINT_TYPE_NAME("auto& [a6, a7]{a}; a6", a6)

    std::tuple b { 0, 1.0, "2.0" };
    auto [ b0, b1, b2 ] = b;
    PRINT_TYPE_NAME("auto [ b0, b1, b2 ] = b; b2", b2)

    auto& [ b3, b4, b5 ] = b;
    PRINT_TYPE_NAME("auto& [ b3, b4, b5 ] = b; b3", b3)

    auto [c0, c1] = std::make_pair( 0, 1.0 );
    PRINT_TYPE_NAME("auto [c0, c1] = std::make_pair( 0, 1.0 ); c0", c0)

    const auto& [c2, c3] = std::make_pair( 0, 1.0 );
    PRINT_TYPE_NAME("const auto& [c2, c3] = std::make_pair( 0, 1.0 ); c2", c2)

    // Pair and tuple with non-const initial variables.
    auto d0 = 0, d1 = 1;
    const auto [d2, d3] = std::make_pair( d0, d1 );
    PRINT_TYPE_NAME("const auto& [d2, d3] = std::make_pair( d0, d1 ); d2", d2)

    auto [d4, d5] = std::make_pair<int&, int&>(d0, d1);
    PRINT_TYPE_NAME("const auto [d4, d5] = std::make_pair<int&, int&>(d0, d1); d4", d4)

    d4 = 2;
    std::cout << "d4 = 2, d0 = " << d0 << "\n";

    auto e0 = 0, e1 = 1;
    const auto [e2, e3] = std::make_tuple(e0, e1);
    PRINT_TYPE_NAME("const auto [e2, e3] = std::make_tuple(e0, e1); e2", e2)

    const auto& [e4, e5] = std::make_tuple(e0, e1);
    PRINT_TYPE_NAME("const auto& [e4, e5] = std::make_tuple(e0, e1); e4", e4)

    const auto [e6, e7] = std::make_tuple<int&, int&>(e0, e1);
    PRINT_TYPE_NAME("const auto [e6, e7] = std::make_tuple<int&, int&>(e0, e1); e6", e6)

    std::pair<int&, int&> fp { e0, e1 };
    PRINT_TYPE_NAME("std::pair<int&, int&> fp { e0, e1 }", fp)
    const auto [fp0, fp1] = fp;
    PRINT_TYPE_NAME("const auto [fp0, fp1] = fp; fp0", fp0)

    const std::pair< int&, int& > cfp { e0, e1 };
    auto [cfp0, cfp1] = cfp;
    PRINT_TYPE_NAME("auto [cfp0, cfp1] = cfp; cfp0", cfp0)

    fp0 = 2;
    std::cout << "fp0 = 2, e0 = " << e0 << "\n";

    std::tuple<int&, int&> ft { e0, e1 };
    PRINT_TYPE_NAME("std::tuple<int&, int&> ft { e0, e1 }", ft)
    const auto [ft0, ft1] = ft;
    PRINT_TYPE_NAME("const auto [ft0, ft1] = ft; ft0", ft0)

    const int ec0 = 0, ec1 = 1;
    std::pair<const int&, const int&> fpc { ec0, ec1 };
    auto [ fpc0, fpc1 ] = fpc;
    PRINT_TYPE_NAME("auto [ fpc0, fpc1 ] = fpc; fpc0", fpc0)
    auto& [ fpc2, fpc3 ] = fpc;
    PRINT_TYPE_NAME("auto& [ fpc2, fpc3 ] = fpc; fpc2", fpc2)

    ft0 = 3;
    std::cout << "ft0 = 3, e0 = " << e0 << "\n";

    std::pair<int, int> gp { e0, e1 };
    gp.first = 4;
    std::cout << "gp.first = 4, e0 = " << e0 << "\n";
    auto [gp0, gp1] = gp;
    gp0 = 5;
    std::cout << "auto [gp0, gp1] = gp; gp0 = 5; gp.first = " << gp.first << "\n";

    auto& [gp2, gp3] = gp;
    gp2 = 6;
    std::cout << "auto& [gp2, gp3] = gp; gp2 = 6; gp.first = " << gp.first << "\n";

    std::tuple<int, int> gt { e0, e1};
    std::get<0>(gt) = 7;
    std::cout << "std::get<0>(gt) = 7, std::get<0>(gt) = " << std::get<0>(gt) << ", e0 = " << e0 << "\n";
    auto [gt0, gt1] = gt;
    gt0 = 8;
    std::cout << "auto [gt0, gt1] = gt; gt0 = 8; std::get<0>(gt) = " << std::get<0>(gt) << "\n";

    auto& [gt2, gt3] = gt;
    gt2 = 9;
    std::cout << "auto& [gt2, gt3] = gt; gt2 = 9; std::get<0>(gt) = " << std::get<0>(gt) << "\n";

    // std::tie().
    int x = 0, y = 1;
    const auto& [x0, y0] = std::tie(x, y);
    PRINT_TYPE_NAME("const auto& [x0, y0] = std::tie(x, y)", x0)

    x0 = 1;
    std::cout << "x0 = 1, x = " << x << "\n";

    auto [x1, y1] = std::tie(x, y);
    PRINT_TYPE_NAME("auto [x1, y1] = std::tie(x, y)", x1)

    x1 = 2;
    std::cout << "x1 = 2, x = " << x << "\n";

    const int w = 0, z = 1;
    PRINT_TYPE_NAME("const int w = 0, z = 0; w", w)
    PRINT_TYPE_NAME("const int w = 0, z = 0; z", z)

    const auto& [w0, z0] = std::tie( w, z );
    PRINT_TYPE_NAME("const auto& [w0, z0] = std::tie( w, z ); w0", w0)

    // This is an error.
//    auto& [ w1, z1 ] = std::tie( w, z );

    std::cout << "\n";
}

template < typename T0, typename T1, typename TF >
static auto apply( const T0& x, const T1& y, const TF& f) {
    PRINT_TYPE_NAME("TF& f", f)
    return f(x, y);
}

static auto apply_auto( const auto& x, const auto& y, const auto& f ) {
    return f(x, y);
}

template < typename TF >
static void apply_add_one( auto& x, const TF& f ) {
    f(x);
}

static void apply_add_one_auto( auto& x, auto& f ) {
    f(x);
}

static void run_lambda_expressions() {
    std::cout << "Lambda expressions. \n";

    auto f = [](auto a, auto b) {
        return a + b;
    };
    PRINT_TYPE_NAME("[](auto a, auto b){}", f)

    auto a = f(0, 1.0);
    std::cout << "a = " << a << "\n";
    PRINT_TYPE_NAME("auto a = f(0, 1.0)", a)

    auto g = [](const auto& a, const auto& b) {
        return a + b;
    };
    PRINT_TYPE_NAME("[](const auto& a, const auto& b)", g)

    auto g1 = [](const auto& a, const auto& b) -> auto {
        return a + b;
    };
    PRINT_TYPE_NAME("[](const auto& a, const auto& b) -> auto", g1)

    auto b = g( 2.0, 3.0f );
    std::cout << "b = " << b << "\n";
    PRINT_TYPE_NAME("auto b = g(2.0, 3.0f)", b)

    auto b1 = g1( 2.0, 3.0f );
    std::cout << "b1 = " << b1 << "\n";
    PRINT_TYPE_NAME("auto b1 = g1(2.0, 3.0f)", b1)

    auto c = apply( 2.0, 3.0f, g );
    auto c1 = apply_auto( 4, 5.0f, g1 );
    std::cout << "c = " << c << "\n";
    std::cout << "c1 = " << c1 << "\n";

    auto h = [](auto& x){ x += 1; };
    auto d = 0;
    apply_add_one(d, h);
    std::cout << "d = " << d << "\n";

    apply_add_one_auto(d, h);
    std::cout << "d = " << d << "\n";
}

int main( int argc, char** argv) {
    std::cout << "Hello, Auto! \n";

    // Simple variable.
    run_simple_variables();

    // Simple sequence.
    run_simple_sequences();

    // Function with auto.
    run_functions_with_auto();

    // Structured bounding.
    run_structured_binding();

    // Lambda.
    run_lambda_expressions();

    return 0;
}
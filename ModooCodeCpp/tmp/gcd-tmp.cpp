#include <iostream>

template <int X, int Y>
struct GCD
{
    static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0>
{
    static const int value = X;
};

int gcdFunction(int a, int b)
{
    return b == 0 ? a : gcdFunction(b, a % b);
}

int main()
{
    std::cout << GCD<36, 24>::value << std::endl;
    std::cout << gcdFunction(36, 24) << std::endl;

    return 0;
}
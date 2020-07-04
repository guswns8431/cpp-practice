#include <iostream>
#include <typeinfo>

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

template <int N, int D = 1>
struct Ratio
{
private:
    static const int _gcd = GCD<N, D>::value;

public:
    using type = Ratio<N / _gcd, D / _gcd>;
    static const int num = N / _gcd;
    static const int den = D / _gcd;
};

template <typename R1, typename R2>
struct _Ratio_Add
{
    using type = Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den>;
};

template <typename R1, typename R2>
struct Ratio_Add : _Ratio_Add<R1, R2>::type
{
};

template <typename R1, typename R2>
struct _Ratio_Subtract
{
    using type = Ratio<R1::num * R2::den - R2::num * R1::den, R1::den * R2::den>;
};

template <typename R1, typename R2>
struct Ratio_Subtract : _Ratio_Subtract<R1, R2>::type
{
};

template <typename R1, typename R2>
struct _Ratio_Multiply
{
    using type = Ratio<R1::num * R2::num, R1::den * R2::den>;
};

template <typename R1, typename R2>
struct Ratio_Multiply : _Ratio_Multiply<R1, R2>::type
{
};

template <typename R1, typename R2>
struct _Ratio_Divide
{
    using type = Ratio<R1::num * R2::den, R2::num * R1::den>;
};

template <typename R1, typename R2>
struct Ratio_Divide : _Ratio_Divide<R1, R2>::type
{
};

int main()
{
    using ratio1 = Ratio<6, 3>;
    using ratio2 = Ratio<4, 2>;
    using ratio3 = Ratio<2, 3>;
    using ratio4 = Ratio<4, 3>;
    using ratio5 = _Ratio_Add<ratio3, ratio4>::type;
    using ratio6 = _Ratio_Add<ratio3, ratio4>::type::type;
    using ratio7 = Ratio_Add<ratio3, ratio4>::type;
    using ratio8 = Ratio_Subtract<ratio1, ratio3>::type;
    using ratio9 = Ratio_Multiply<ratio2, ratio3>::type;

    std::cout << ((typeid(Ratio<6, 3>)) == (typeid(Ratio<4, 2>)));   // 0
    std::cout << ((typeid(ratio1::type)) == (typeid(ratio2::type))); // 1
    std::cout << ((typeid(ratio5)) == typeid(Ratio<18, 9>));         // 1
    std::cout << ((typeid(ratio6) == typeid(Ratio<2, 1>)));          // 1
    std::cout << ((typeid(ratio7)) == typeid(Ratio<2, 1>));          // 1
    std::cout << std::endl;

    std::cout << (typeid(ratio8) == typeid(Ratio<4, 3>));
    std::cout << (typeid(ratio9) == typeid(Ratio<4, 3>));
    std::cout << std::endl;

    std::cout << ratio8::num << "/" << ratio8::den << std::endl;
    std::cout << ratio9::num << "/" << ratio9::den << std::endl;
}
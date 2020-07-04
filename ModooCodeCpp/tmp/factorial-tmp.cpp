#include <iostream>

template <long long N>
struct Factorial
{
    static const long long result = N * Factorial<N - 1>::result;
};

template <>
struct Factorial<1>
{
    static const long long result = 1;
};

long long factorialFunction(long long number)
{
    if (number == 1)
    {
        return number;
    }

    return number * factorialFunction(number - 1);
}

int main()
{

    std::cout << Factorial<20>::result << std::endl;

    std::cout << factorialFunction(20) << std::endl;

    return 0;
}
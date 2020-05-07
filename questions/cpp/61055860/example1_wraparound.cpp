#include <iostream>
#include <limits>

void func( const std::size_t s )
{
    std::cout << "In func(): " << s << '\n';
}

int main()
{
    const auto s_min = std::numeric_limits<std::size_t>::min();
    const auto s_max = std::numeric_limits<std::size_t>::max();
    
    std::cout << "std::size_t (min): " << s_min << '\n';
    std::cout << "std::size_t (max): " << s_max << '\n';

    std::cout << '\n';

    std::cout << "s_min - 2: " << s_min - 2 << '\n';

    std::cout << "func(-2) : " << -2 << '\n';

    func( -2 );

    return 0;
}

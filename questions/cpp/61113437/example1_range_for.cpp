#include <iostream>
#include <vector>

int main()
{
    std::size_t rows {0};
    std::size_t cols {0};
    std::cin >> rows >> cols;

    std::vector<std::vector<int>> matrix( rows );
    for ( auto& r : matrix )
    {
        r.resize( cols );
        for ( auto& c : r )
        {
            std::cin >> c;
        }
    }

    for ( const auto& r : matrix )
    {
        for ( const auto& c : r )
        {
            std::cout << c << ' ';
        }

        std::cout << '\n';
    }

    return 0;
}

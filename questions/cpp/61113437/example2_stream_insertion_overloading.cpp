#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

std::ostream& operator<<( std::ostream& os, const Matrix& m )
{
    for ( const auto& r : m )
    {
        for ( const auto& c : r )
        {
            os << c << ' ';
        }
        os << '\n';
    }

    return os;
}

int main()
{
    const Matrix m
    {
        { 1, 2 },
        { 3, 4 }
    };

    std::cout << m;

    return 0;
}

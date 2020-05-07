#include <iostream>
#include <array>
using namespace std;

int main()
{
    array<int, 5> a = {1, 2, 3, 4, 5};
    a.at(-2) = 100;
    cout << a[-2] << endl;
    return 0;
}

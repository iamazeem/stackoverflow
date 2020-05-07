## C++: std::array: Why is there no warning or error on `at(-2)`?

### [std::array](https://en.cppreference.com/w/cpp/container/array): Element access and out-of-bounds validation

Link: https://stackoverflow.com/questions/61055860/

### Prerequisites

- C++11 compliant compiler (at least)

## Questions

The book says that `std::array` is safer and simpler than other methods of the assignment.

Here's my code:

```
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
```

Why is there no warning or error in this code?

---

## Answer

[`std::array::at()`][1] accepts an argument of `size_type` which usually is defined in terms of some `unsinged` type e.g. `std::size_t` / `unsigned long`.

The actual argument `-2` is of `signed int` type which is [implicitly converted][2] to `size_type` while passing to `at()` and becomes a valid `size_type` number; but, only a wrapped-around one. See [example][3].

By default, you don't get a compiler warning/error for implicit conversion. You have to look for your compiler options like [GCC's][4] `-Wconversion`, `Wsign-conversion`, etc. to enable these settings. In your case on GCC, `-Wsign-conversion` will warn you about these conversions; and, in combination with `-Werror`, these warnings will become errors.

Observe the compiler output of your code with compiler flags `-std=c++11 -Werror -Wsign-conversion` ([live][5]):

**Compiler output:**
```
<source>: In function 'int main()':

<source>:6:10: error: unsigned conversion from 'int' to 'std::array<int, 5>::size_type' {aka 'long unsigned int'} changes value from '-2' to '18446744073709551614' [-Werror=sign-conversion]

    6 |     a.at(-2)=100;

      |          ^~

<source>:7:13: error: unsigned conversion from 'int' to 'std::array<int, 5>::size_type' {aka 'long unsigned int'} changes value from '-2' to '18446744073709551614' [-Werror=sign-conversion]

    7 |     cout<<a[-2]<<endl;

      |             ^~

cc1plus: all warnings being treated as errors
```

Here's another [example][6] that simulates the same thing.

---

And, in `at()`, the passed argument is validated against the array size. Here, you will get a runtime exception of type [std::out_of_range][7] as described by the [documentation][1]:

> If `pos` is not within the range of the container, an exception of type `std::out_of_range` is thrown.

You may look at its implementation provided by your compiler if you're so inclined to.

And, when you use an invalid index with [subscript operator `[]`][8] e.g. `a[-2]` where `-2` to `size_type` conversion returns into a wrapped-around value, the result will be an out-of-bounds access and will cause an [Undefined Behavior][9].

Hope this explanation helps!

  [1]: https://en.cppreference.com/w/cpp/container/array/at
  [2]: https://en.cppreference.com/w/cpp/language/implicit_conversion
  [3]: https://godbolt.org/z/JPAkHX
  [4]: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
  [5]: https://godbolt.org/z/kQ_DUn
  [6]: https://godbolt.org/z/HSeDFJ
  [7]: https://en.cppreference.com/w/cpp/error/out_of_range
  [8]: https://en.cppreference.com/w/cpp/container/array/operator_at
  [9]: https://en.cppreference.com/w/cpp/language/ub

  ---

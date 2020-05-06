## C++: Array creation `int *array = new int[sizeof(int)*n]`

### Memory allocation using `new` operator vs `malloc()` and `sizeof()`

Link: https://stackoverflow.com/questions/61072637/

## Question

Can you explain what is happening with this statement particularly inside the parentheses?

    int *array = new int[sizeof(int) * n];

---

## Answer

That is a complete C++ statement and parentheses `()` of `sizeof` operator contain the type `int` and [`sizeof(type)`][1] gives the size of the enclosing type in bytes:

    int *array = new int[ sizeof(int) * n ];
                                ^^^^^

I believe you meant the *expression* inside square brackets `[]` of [`new`][2] expression i.e. `sizeof(int) * n`.

Semantically, the expression might be wrong.

If you allocate 10 integers with `new` operator then `sizeof(int)` is taken care of automatically. You just have to provide the number of elements of the type you're allocating for.

For example:

    int  n = 10;                // n can be an integer entered by the user
    int* a = new int[n];        // allocate an array of 10 integers

The array elements would be [default-initialized][3] in this case and the pointer to the first element of the array is returned.

And, when you do it like this (suppose you're on a 64-bit machine i.e. `sizeof(int)` is 8):

    int  n = 10;
    int  s = sizeof(int) * n;   // 8 x 10 = 80
    int* a = new int[ s ];      // allocate an array of 80 integers

This is what I earlier referred to as *semantically wrong* because the intention might have been to allocate 10 integers, not 80.

The expression `sizeof(int) * n` is required for `malloc()` where you have to provide the exact number of bytes you want to allocate so you need to provide the exact number of elements of the type. The `malloc()` function does not initialize the allocated bytes and it returns the pointer to the first element also.

For example:

    int  n = 10;
    int  s = sizeof(int) * n;
    int* a = (int*) malloc( s );

You have to initialize the memory allocated by `malloc()`. For more information on this, refer to the above links of the `new` and `malloc()`.

---

Aside, you are allocating memory so you are responsible to release it when you're done. So, ideally, `new` and `new[]` would follow `delete` and `delete[]` respectively. And, `malloc()` would be followed by `free()`. 

Refer to smart pointers e.g. [std::unique_pointer][5] and [std::shared_ptr][6] along with `std::make_unique` and `std::make_shared` for [RAII][7]-based automatic memory management.


  [1]: https://en.cppreference.com/w/cpp/language/sizeof
  [2]: https://en.cppreference.com/w/cpp/language/new
  [3]: https://en.cppreference.com/w/cpp/language/default_initialization
  [4]: https://en.cppreference.com/w/cpp/memory/c/malloc
  [5]: https://en.cppreference.com/w/cpp/memory/unique_ptr
  [6]: https://en.cppreference.com/w/cpp/memory/shared_ptr
  [7]: https://en.cppreference.com/w/cpp/language/raii

---

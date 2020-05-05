package main

import (
    "fmt"
)

func store(x, y int) (int, int) {
    return x + y, x - y
}

func main() {
    a, _ := store(6, 4)
    fmt.Println(a)
}
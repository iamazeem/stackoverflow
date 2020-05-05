package main

import (
    "fmt"
    "strings"
)

func checkSubstrings(str string, subs ...string) (bool, int) {

    matches := 0
    isCompleteMatch := true

    fmt.Printf("String: \"%s\", Substrings: %s\n", str, subs)

    for _, sub := range subs {
        if strings.Contains(str, sub) {
            matches += 1
        } else {
            isCompleteMatch = false
        }
    }

    return isCompleteMatch, matches
}

func main() {
    isCompleteMatch1, matches1 := checkSubstrings("Hello abc, xyz, abc", "abc", "xyz")
    fmt.Printf("Test 1: { isCompleteMatch: %t, Matches: %d }\n", isCompleteMatch1, matches1)

    fmt.Println()

    isCompleteMatch2, matches2 := checkSubstrings("Hello abc, abc", "abc", "xyz")
    fmt.Printf("Test 2: { isCompleteMatch: %t, Matches: %d }\n", isCompleteMatch2, matches2)
}
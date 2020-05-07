package main

import (
    "bytes"
    "encoding/csv"
    "fmt"
    "log"
)

func main() {
    pairs := [][]string{
        {"k1", "v1"},
        {"k2", "v2"},
    }

    b := new(bytes.Buffer)
    w := csv.NewWriter(b)

    w.WriteAll(pairs)

    if err := w.Error(); err != nil {
        log.Fatal(err)
    }

    s := b.String()

    fmt.Println(s)
}

// Echo prints its command-line arguments.
package main

import (
    "fmt"
    "os"
    "strings"
    "bufio"
)

func main() {
    // var s, sep string
    fmt.Println("Hello World")
    // for i:=1; i<len(os.Args); i++ {
    //    s += sep + os.Args[i]
    //    sep = " "
    // }
    // fmt.Println(s)
    fmt.Println("Second type")
    fmt.Println(strings.Join(os.Args, " "))
    fmt.Println("3rd exercise: Find dup line")
    counts := make(map[string]int)
    files := os.Args[1:]
    if len(files) == 0 {
        countLines(os.Stdin, counts)
    } else {
        for _, arg := range files {
            f, err := os.Open(arg)
            if err != nil {
                fmt.Fprintf(os.Stderr, "dup2: %v\n", err)
                continue
            }
            countLines(f, counts)
            f.Close()
        }
    }
    for line, n := range counts {
        if n > 1 {
            fmt.Printf("%d\t%s\n", n, line)
        }
    }
}

func countLines(f *os.File, counts map[string]int) {
    input := bufio.NewScanner(f)
    for input.Scan() {
        counts[input.Text()]++
    }
}

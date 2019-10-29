package main

import "fmt"
import "strings"

func main() {
	fmt.Println("strings.EqualFold(\"Go\", \"go\")")
	fmt.Println(strings.EqualFold("Go", "go"))

	fmt.Println("HasPrefix(\"Hello\", \"Hel\")")
	fmt.Println(strings.HasPrefix("Hello", "Hel"))

	fmt.Println("HasSuffix(\"Hello\", \"Hel\")")
	fmt.Println(strings.HasSuffix("Hello", "Hel"))

	fmt.Println("strings.Contains(\"seafood\", \"foo\")")
	fmt.Println(strings.Contains("seafood", "foo"))

	fmt.Println("strings.Contains(\"seafood\", \"\")")
	fmt.Println(strings.Contains("seafood", ""))

	fmt.Println("strings.Contains(\"seafood\", \"bar\")")
	fmt.Println(strings.Contains("seafood", "bar"))

	fmt.Println("strings.Contains(\"\", \"\")")
	fmt.Println(strings.Contains("", ""))

	fmt.Println("strings.ToLower(\"Gopher\")")
	fmt.Println(strings.ToLower("Gopher"))

	fmt.Println("strings.ToUpper(\"Gopher\")")
	fmt.Println(strings.ToUpper("Gopher"))

	fmt.Println("strings.Title(\"her royal highness\")")
	fmt.Println(strings.Title("her royal highness"))

	fmt.Println("strings.ToTitle(\"her royal highness\")")
	fmt.Println(strings.ToTitle("her royal highness"))

	fmt.Println("strings.Replace(\"oink oink oink\", \"k\", \"ky\", 2)")
	fmt.Println(strings.Replace("oink oink oink", "k", "ky", 2))

	fmt.Println("strings.Replace(\"oink oink oink\", \"oink\", \"moo\", -1)")
	fmt.Println(strings.Replace("oink oink oink", "oink", "moo", -1))

	fmt.Println("[%q]", strings.Trim(" !!! Achtung! Achtung! !!! ", "! "))
	fmt.Println(strings.TrimSpace(" \t\n a lone gopher \n\t\r\n"))

	fmt.Println(strings.TrimPrefix("hello", "hel"))
	fmt.Println(strings.TrimSuffix("hello", "llo"))
	fmt.Println(strings.TrimLeft("hello", "he"))
	fmt.Println(strings.TrimRight("hello", "ho"))

	fmt.Printf("%q\n", strings.Split("a,b,c", ","))
	fmt.Printf("%q\n", strings.Split("a man a plan a canal panama", "a "))
	fmt.Printf("%q\n", strings.Split(" xyz ", ""))
	fmt.Printf("%q\n", strings.Split("", "Bernardo O'Higgins"))

	s := []string{"foo", "bar", "baz"}
	fmt.Println(strings.Join(s, ", "))
}

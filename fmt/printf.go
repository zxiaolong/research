
package main

import "fmt"

func main(){
	fmt.Printf("hello world\n")

	fmt.Printf("%%t:%t\n", true)

	fmt.Printf("%%b:15 is %b\n", 15)
	fmt.Printf("%%o:15 is %o\n", 15)
	fmt.Printf("%%x:15 is %x\n", 15)
	fmt.Printf("%%X:15 is %X\n", 15)

	fmt.Printf("%%d:15 is %d\n", 15)
	fmt.Printf("%%.2f:1.2 is %.2f\n", 1.2)

	fmt.Printf("%%s:%s\n", "string")

	fmt.Printf("%%p:%p\n", 1)
}

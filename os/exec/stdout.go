package main

import "os/exec"
import "log"
import "fmt"
import "encoding/json"

func main() {
	cmd := exec.Command("echo", "-n", `{"Name": "Bob", "Age": 32}`)
	stdout, err := cmd.StdoutPipe()
	if err != nil {
	    log.Fatal(err)
	}
	if err := cmd.Start(); err != nil {
	    log.Fatal(err)
	}
	var person struct {
	    Name string
	    Age  int
	}
	if err := json.NewDecoder(stdout).Decode(&person); err != nil {
	    log.Fatal(err)
	}
	if err := cmd.Wait(); err != nil {
	    log.Fatal(err)
	}
	fmt.Printf("%s is %d years old\n", person.Name, person.Age)
}
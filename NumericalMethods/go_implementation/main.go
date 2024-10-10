package main

import (
	"fmt"
	"github.com/saskamegaprogrammist/IU9-educational-tasks/NumericalMethods/go_implementation/matrix"
	"time"
)

func main() {
	n := 1024
	var matrixFirst matrix.Matrix
	matrixFirst.Initialize(n, n)
	var matrixSecond matrix.Matrix
	matrixSecond.Initialize(n, n)
	err := matrixFirst.Generate()
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	err = matrixSecond.Generate()
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	var matrixThird matrix.Matrix
	start := time.Now()
	matrixFirst.MultiplyStrassenParallel(matrixSecond, &matrixThird)
	parallelStrassenTime := time.Since(start)
	fmt.Printf("parallel strassen time :%s\n", parallelStrassenTime)
	start = time.Now()
	_, err = matrixFirst.MultiplyStrassen(&matrixSecond)
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	strassenTime := time.Since(start)
	fmt.Printf("strassen time :%s\n", strassenTime)
	start = time.Now()
	_, err = matrixFirst.Multiply(&matrixSecond)
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	simpleTime := time.Since(start)
	fmt.Printf("simple time :%s\n", simpleTime)
	//matrixFirst.Print()
	//matrixSecond.Print()
	//matrixThird.Print()
	//matrixFourth.Print()
	//matrixFifth.Print()

}

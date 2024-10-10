package galilley_model

import "fmt"

type Vector struct {
	X float64
	Y float64
}

func (vector *Vector) Print() {
	fmt.Printf("X: %f Y: %f \n", vector.X, vector.Y)
}

func (vector *Vector) Set(X float64, Y float64) {
	vector.X = X
	vector.Y = Y
}

func (vector *Vector) IsYLessThanZero() bool {
	return vector.Y < 0
}
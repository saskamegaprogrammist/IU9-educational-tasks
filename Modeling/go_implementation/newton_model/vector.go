package newton_model

import (
	"fmt"
	"math"
)

type Vector struct {
	X float64
	Y float64
	Vx float64
	Vy float64
}

func (vector *Vector) Print() {
	fmt.Printf("X: %f Y: %f Vx: %f Vy: %f", vector.X, vector.Y, vector.Vx, vector.Vy)
}

func (vector *Vector) PrintXY() {
	fmt.Printf("X: %f Y: %f \n", vector.X, vector.Y)
}

func (vector *Vector) Init(startAngle float64, startSpeed float64) {
	vector.X = 0
	vector.Y = 0
	vector.Vx = math.Cos(startAngle)*startSpeed
	vector.Vy = math.Sin(startAngle)*startSpeed
}

func (vector *Vector) Set(X float64, Y float64, Vx float64, Vy float64) {
	vector.X = X
	vector.Y = Y
	vector.Vx = Vx
	vector.Vy = Vy
}

func (vector *Vector) Copy(newVector Vector) {
	vector.X = newVector.X
	vector.Y = newVector.Y
	vector.Vx = newVector.Vx
	vector.Vy = newVector.Vy
}

func (vector *Vector) Add(newVector Vector) {
	vector.X += newVector.X
	vector.Y += newVector.Y
	vector.Vx += newVector.Vx
	vector.Vy += newVector.Vy
}

func (vector *Vector) Multiply(parameter float64) {
	vector.X *= parameter
	vector.Y *= parameter
	vector.Vx *= parameter
	vector.Vy *= parameter
}

func (vector *Vector) IsYLessThanZero() bool {
	return vector.Y < 0
}
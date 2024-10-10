package newton_model

import (
	"math"
)

type NewtonModel struct {
	StartAngle float64
	StartSpeed float64
	Beta float64
	Mass float64
	Vector Vector
	RKstep float64
	G float64
	flPoints [][]float64
}


func (nm *NewtonModel) Init(airDensity float64, startAngle float64, startSpeed float64, bulletDensity float64, radius float64, C float64) {
	nm.StartAngle = toRadians(startAngle)
	nm.StartSpeed = startSpeed
	nm.setMass(radius, bulletDensity)
	nm.setBeta(radius, airDensity, C)
	nm.RKstep = float64(1)/float64(60)
	nm.G = 9.8
	nm.Vector.Init(nm.StartAngle, startSpeed)
	nm.flPoints = make([][]float64, 0)

	//fmt.Printf("X: %f Y: %f", nm.Vector.X, nm.Vector.Y)
	nm.Vector.PrintXY()
}

func toRadians(angle float64) float64 {
	return angle*math.Pi/180
}

func (nm *NewtonModel) setMass(radius float64, bulletDensity float64) {
	volume := (4/3)*math.Pi*math.Pow(radius, 3)
	nm.Mass = volume*bulletDensity
}

func (nm *NewtonModel) setBeta(radius float64, airDensity float64, C float64) {
	square := math.Pi*math.Pow(radius, 2)
	nm.Beta = C*airDensity*square/2
}

func (nm *NewtonModel) solveRungeKutta() {
	v1 := Vector{
		X:  nm.getX(nm.Vector),
		Y:  nm.getY(nm.Vector),
		Vx: nm.getVx(nm.Vector),
		Vy: nm.getVy(nm.Vector),
	}
	v1.Multiply(nm.RKstep)

	var v2Help1 Vector
	v2Help1.Copy(nm.Vector)
	var v2Help Vector
	v2Help.Copy(v1)
	par := float64(1) / float64(2)
	v2Help.Multiply(par)
	v2Help1.Add(v2Help)
	v2 := Vector{
		X:  nm.getX(v2Help1),
		Y:  nm.getY(v2Help1),
		Vx: nm.getVx(v2Help1),
		Vy: nm.getVy(v2Help1),
	}
	v2.Multiply(nm.RKstep)

	var v3Help1 Vector
	v3Help1.Copy(nm.Vector)
	var v3Help Vector
	v3Help.Copy(v2)
	v3Help.Multiply(par)
	v3Help1.Add(v2Help)
	v3 := Vector{
		X:  nm.getX(v3Help1),
		Y:  nm.getY(v3Help1),
		Vx: nm.getVx(v3Help1),
		Vy: nm.getVy(v3Help1),
	}
	v3.Multiply(nm.RKstep)

	var v4Help1 Vector
	v4Help1.Copy(nm.Vector)
	var v4Help Vector
	v4Help.Copy(v3)
	v4Help1.Add(v4Help)
	v4 := Vector{
		X:  nm.getX(v4Help1),
		Y:  nm.getY(v4Help1),
		Vx: nm.getVx(v4Help1),
		Vy: nm.getVy(v4Help1),
	}
	v4.Multiply(nm.RKstep)

	var sumVector Vector
	sumVector.Copy(v1)
	var sumVector1 Vector
	sumVector1.Copy(v2)
	sumVector1.Multiply(2)
	var sumVector2 Vector
	sumVector2.Copy(v3)
	sumVector2.Multiply(2)
	sumVector.Add(sumVector1)
	sumVector.Add(sumVector2)
	sumVector.Add(v4)
	parSum := float64(1) / float64(6)
	sumVector.Multiply(parSum)
	sumVector.Add(nm.Vector)
	nm.Vector.Copy(sumVector)

	//fmt.Printf("X: %f Y: %f", nm.Vector.X, nm.Vector.Y)
	//nm.Vector.PrintXY()
}

func (nm *NewtonModel) GetPoints() [][]float64 {
	return nm.flPoints
}

func (nm *NewtonModel) Solve() {
	for {
		if nm.Vector.IsYLessThanZero() {
			break
		}
		nm.solveRungeKutta()
		nm.flPoints = append(nm.flPoints, []float64{nm.Vector.X, nm.Vector.Y})
	}
	nm.Vector.PrintXY()
}

func (nm *NewtonModel) getVx(vector Vector) float64 {
	return -nm.Beta*vector.Vx*math.Sqrt(math.Pow(vector.Vx, 2) + math.Pow(vector.Vy, 2)) / nm.Mass
}

func (nm *NewtonModel) getVy(vector Vector) float64 {
	return -nm.Beta*vector.Vy*math.Sqrt(math.Pow(vector.Vx, 2) + math.Pow(vector.Vy, 2)) / nm.Mass - nm.G
}

func (nm *NewtonModel) getX(vector Vector) float64 {
	return vector.Vx
}

func (nm *NewtonModel) getY(vector Vector) float64 {
	return vector.Vy
}
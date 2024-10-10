package galilley_model

import "math"

type GalileyModel struct {
	StartAngle float64
	StartSpeed float64
	Mass float64
	G float64
	Step float64
	Vector Vector
	flPoints [][]float64
}

func (gm *GalileyModel) Init(startAngle float64, startSpeed float64, step float64) {
	gm.StartAngle = toRadians(startAngle)
	gm.StartSpeed = startSpeed
	gm.G = 9.8
	gm.Step = step
	gm.flPoints = make([][]float64, 0)
}

func (gm *GalileyModel) GetPoints() [][]float64 {
	return gm.flPoints
}

func toRadians(angle float64) float64 {
	return angle*math.Pi/180
}

func (gm *GalileyModel) Solve() {
	for {
		if gm.Vector.IsYLessThanZero() {
			break
		}
		gm.solve()
		gm.flPoints = append(gm.flPoints, []float64{gm.Vector.X, gm.Vector.Y})
	}
	gm.Vector.Print()

}

func (gm *GalileyModel) solve() {
	gm.Vector.X += gm.Step
	gm.Vector.Y = -gm.G*math.Pow(gm.Vector.X, 2)/(2*math.Pow(gm.StartSpeed, 2)*math.Pow(math.Cos(gm.StartAngle), 2)) + math.Tan(gm.StartAngle)*gm.Vector.X
}

package drawer

import (
	"fmt"
	"github.com/Arafatk/glot"
	"gonum.org/v1/plot/plotter"
	"strconv"
)

type Drawer3D struct {
	points []plotter.XYZ
}

func (d *Drawer3D) Parse3DPoints(strPoints [][]string) error {
	var err error
	var points []plotter.XYZ
	for _, p := range strPoints {
		var x float64
		var y float64
		var z float64
		x, err = strconv.ParseFloat(p[0], 10)
		if err != nil {
			return fmt.Errorf("error parsing float: %v", err)
		}
		y, err = strconv.ParseFloat(p[1], 10)
		if err != nil {
			return fmt.Errorf("error parsing float: %v", err)
		}
		z, err = strconv.ParseFloat(p[2], 10)
		if err != nil {
			return fmt.Errorf("error parsing float: %v", err)
		}

		points = append(points, plotter.XYZ{
			X:x,
			Y:y,
			Z:z,
		})
	}
	d.points = points
	return nil
}


func (d *Drawer3D) Draw3D() error {
	var err error
	dimensions := 3
	gplot, _ := glot.NewPlot(dimensions, false, false)
	pointGroupName := "Statistic model"
	style := "points"
	var points [][]float64
	var xs [] float64
	var ys [] float64
	var zs [] float64
	for _, p := range d.points {
		xs = append(xs, p.X)
		ys = append(ys, p.Y)
		zs = append(zs, p.Z)
	}
	points = [][]float64{xs, ys, zs}
	err = gplot.AddPointGroup(pointGroupName, style, points)
	if err != nil {
		return err
	}
	// A plot type used to make points/ curves and customize and save them as an image.
	//err = gplot.SetTitle("Statistic model")
	//if err != nil {
	//	return err
	//}
	// Optional: Setting the title of the gplot
	err = gplot.SetXLabel("Количество погибших\n в ДТП")
	if err != nil {
		return err
	}
	err = gplot.SetYLabel("Количество проживающих\n в регионе")
	if err != nil {
		return err
	}
	err = gplot.SetZLabel("Уровень \nжизни \n в регионе")
	if err != nil {
		return err
	}
	//// Optional: Setting label for X and Y axis
	//err = gplot.SetXrange(-2, 18)
	//if err != nil {
	//	return err
	//}
	//err = gplot.SetYrange(-2, 18)
	//if err != nil {
	//	return err
	//}
	// Optional: Setting axis ranges
	err = gplot.SavePlot("output_1.png")
	if err != nil {
		return err
	}
	return nil
}
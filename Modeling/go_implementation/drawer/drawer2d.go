package drawer

import (
	"github.com/Arafatk/glot"
	"gonum.org/v1/plot/plotter"
)

type Drawer2D struct {
	points plotter.XYs
}

func (d *Drawer2D) ParsePoints(fltPoints [][]float64) {
	var points []plotter.XY
	for _, p := range fltPoints {
		points = append(points, plotter.XY{
			X:p[0],
			Y:p[1],
		})
	}
	d.points = points
}

func (d *Drawer2D) Draw() error {
	var err error
	dimensions := 2
	gplot, _ := glot.NewPlot(dimensions, false, false)
	pointGroupName := "Simple Points"
	style := "dots"
	var points [][]float64
	var xs [] float64
	var ys [] float64
	for _, p := range d.points {
		xs = append(xs, p.X)
		ys = append(ys, p.Y)
	}
	points = [][]float64{xs, ys}
	err = gplot.AddPointGroup(pointGroupName, style, points)
	if err != nil {
		return err
	}
	// A plot type used to make points/ curves and customize and save them as an image.
	err = gplot.SetTitle("Example gplot")
	if err != nil {
		return err
	}
	// Optional: Setting the title of the gplot
	err = gplot.SetXLabel("X-Axis")
	if err != nil {
		return err
	}
	err = gplot.SetYLabel("Y-Axis")
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
	err = gplot.SavePlot("output.png")
	if err != nil {
		return err
	}
	return nil
}

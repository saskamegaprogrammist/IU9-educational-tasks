package main

import (
	"bufio"
	"fmt"
	"github.com/saskamegaprogrammist/IU9-educational-tasks/Modeling/go_implementation/drawer"
	"github.com/saskamegaprogrammist/IU9-educational-tasks/Modeling/go_implementation/galilley_model"
	"github.com/saskamegaprogrammist/IU9-educational-tasks/Modeling/go_implementation/newton_model"
	"log"
	"os"
	"strings"
)

func handleScannerError(scanner *bufio.Scanner) error {
	var scannerErr error
	if err := scanner.Err(); err != nil {
		scannerErr = fmt.Errorf("scanner error: %v", err)
		log.Printf(scannerErr.Error())
	}
	return scannerErr
}

func scanInput(scanner *bufio.Scanner) (bool, error) {
	if !scanner.Scan() {
		return false, nil
	}
	return true, handleScannerError(scanner)
}

func first() {
	var points [][]float64
	var nm newton_model.NewtonModel
	nm.Init(1.2754, 62, 32, 11340, 0.05, 0)
	nm.Solve()
	points = nm.GetPoints()

	fmt.Println()
	var gm galilley_model.GalileyModel
	gm.Init(62, 32, 0.01)
	gm.Solve()
	points = append(points, gm.GetPoints()...)

	//var dr drawer.Drawer2D
	//dr.ParsePoints(points)
	//err := dr.Draw()
	//if err != nil {
	//	log.Printf("error drawing points: %v", err)
	//}
}

func second() {
	var err error
	coords := make([][]string, 0)
	inputFilename := "input.txt"
	inputFile, err := os.Open(inputFilename)
	if err != nil {
		log.Printf("error opening input file: %v", err)
	}
	scanner := bufio.NewScanner(inputFile)
	scanner.Split(bufio.ScanLines)
	err = handleScannerError(scanner)
	if err != nil {
		return
	}
	hasInput, err := scanInput(scanner)
	if err != nil {
		return
	}
	for hasInput {
		coord := scanner.Text()
		coordsArray := strings.Split(coord, " ")
		coords = append(coords, coordsArray)
		hasInput, err = scanInput(scanner)
		if err != nil {
			return
		}
	}
	var dr drawer.Drawer3D
	err = dr.Parse3DPoints(coords)
	if err != nil {
		log.Printf("error parsing points: %v", err)
	}
	err = dr.Draw3D()
	if err != nil {
		log.Printf("error drawing points: %v", err)
	}
}

func main() {
	//first()
	second()
}

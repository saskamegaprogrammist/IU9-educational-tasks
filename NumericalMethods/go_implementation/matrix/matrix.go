package matrix

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const diagBoost = 1

type Matrix struct {
	sizeRow     int
	sizeColumn  int
	valuesArray [][]float64
	wg          sync.WaitGroup
}

func (m *Matrix) Initialize(sizeRow int, sizeColumn int) {
	m.sizeRow = sizeRow
	m.sizeColumn = sizeColumn
	m.valuesArray = make([][]float64, m.sizeRow)
	for i := 0; i < m.sizeRow; i++ {
		m.valuesArray[i] = make([]float64, m.sizeColumn)
	}
	m.wg = sync.WaitGroup{}
}

func (m *Matrix) Generate() error {
	if m.sizeRow == 0 || m.sizeColumn == 0 {
		return fmt.Errorf("matrix sizes wasn't initialized")
	}
	randomSource := rand.NewSource(time.Now().UnixNano())
	random := rand.New(randomSource)
	for i := 0; i < m.sizeRow; i++ {
		for j := 0; j < m.sizeColumn; j++ {
			m.valuesArray[i][j] = random.Float64() * 10
			if i == j {
				m.valuesArray[i][j] *= diagBoost
			}
		}
	}
	return nil
}

func (m *Matrix) Multiply(matrix *Matrix) (Matrix, error) {
	var newMatrix Matrix
	if m.sizeColumn != matrix.sizeRow {
		return newMatrix, fmt.Errorf("matrices sizes don't match")
	}
	newMatrix.Initialize(m.sizeRow, matrix.sizeColumn)
	for k := 0; k < matrix.sizeColumn; k++ {
		for i := 0; i < m.sizeRow; i++ {
			for j := 0; j < m.sizeColumn; j++ {
				newMatrix.valuesArray[i][k] += m.valuesArray[i][j] * matrix.valuesArray[j][k]
			}
		}
	}
	return newMatrix, nil
}

func (m *Matrix) Add(matrix *Matrix) (Matrix, error) {
	var newMatrix Matrix
	if m.sizeColumn != matrix.sizeColumn || m.sizeRow != matrix.sizeRow {
		return newMatrix, fmt.Errorf("matrices sizes don't match")
	}
	newMatrix.Initialize(m.sizeRow, m.sizeColumn)
	for i := 0; i < m.sizeRow; i++ {
		for j := 0; j < m.sizeColumn; j++ {
			newMatrix.valuesArray[i][j] = m.valuesArray[i][j] + matrix.valuesArray[i][j]
		}
	}
	return newMatrix, nil
}

func (m *Matrix) Substract(matrix *Matrix) (Matrix, error) {
	var newMatrix Matrix
	if m.sizeColumn != matrix.sizeColumn || m.sizeRow != matrix.sizeRow {
		return newMatrix, fmt.Errorf("matrices sizes don't match")
	}
	newMatrix.Initialize(m.sizeRow, m.sizeColumn)
	for i := 0; i < m.sizeRow; i++ {
		for j := 0; j < m.sizeColumn; j++ {
			newMatrix.valuesArray[i][j] = m.valuesArray[i][j] - matrix.valuesArray[i][j]
		}
	}
	return newMatrix, nil
}

func (m *Matrix) Print() {
	fmt.Println("printing matrix:")
	for i := 0; i < m.sizeRow; i++ {
		for j := 0; j < m.sizeColumn; j++ {
			fmt.Printf("%f ", m.valuesArray[i][j])
		}
		fmt.Println()
	}
	fmt.Println()
}

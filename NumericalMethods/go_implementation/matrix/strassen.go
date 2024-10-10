package matrix

import "fmt"

const (
	CORNER_LEFT_U = iota
	CORNER_RIGHT_U
	CORNER_LEFT_L
	CORNER_RIGHT_L
)

func (m *Matrix) fillCorner(newMatrix *Matrix, corner int) {
	newSize := newMatrix.sizeRow
	var iBoost int
	var jBoost int
	switch corner {
	case CORNER_LEFT_U:
		iBoost = 0
		jBoost = 0
	case CORNER_RIGHT_U:
		iBoost = 0
		jBoost = newSize
	case CORNER_LEFT_L:
		iBoost = newSize
		jBoost = 0
	case CORNER_RIGHT_L:
		iBoost = newSize
		jBoost = newSize
	}
	for i := 0; i < newSize; i++ {
		for j := 0; j < newSize; j++ {
			newMatrix.valuesArray[i][j] = m.valuesArray[i+iBoost][j+jBoost]
		}
	}
}

func (m *Matrix) SplitToCorners() (*Matrix, *Matrix, *Matrix, *Matrix, error) {
	var matrixLeftU Matrix
	var matrixRightU Matrix
	var matrixLeftL Matrix
	var matrixRightL Matrix

	sizeNew := m.sizeColumn / 2

	matrixLeftU.Initialize(sizeNew, sizeNew)
	matrixRightU.Initialize(sizeNew, sizeNew)
	matrixLeftL.Initialize(sizeNew, sizeNew)
	matrixRightL.Initialize(sizeNew, sizeNew)

	m.fillCorner(&matrixLeftU, CORNER_LEFT_U)
	m.fillCorner(&matrixRightU, CORNER_RIGHT_U)
	m.fillCorner(&matrixLeftL, CORNER_LEFT_L)
	m.fillCorner(&matrixRightL, CORNER_RIGHT_L)

	return &matrixLeftU, &matrixRightU, &matrixLeftL, &matrixRightL, nil
}

func (m *Matrix) MultiplyStrassen(matrix *Matrix) (Matrix, error) {
	var newMatrix Matrix
	if m.sizeColumn != matrix.sizeRow {
		return newMatrix, fmt.Errorf("matrices sizes don't match")
	}
	if m.sizeColumn != m.sizeRow || matrix.sizeColumn != matrix.sizeRow {
		return newMatrix, fmt.Errorf("strassen algorithm uses square matrices")
	}
	size := m.sizeColumn
	if size%2 != 0 || size < 32 {
		return m.Multiply(matrix)
	}
	newMatrix.Initialize(m.sizeRow, matrix.sizeColumn)
	aLeftU, aRightU, aLeftL, aRightL, err := m.SplitToCorners()
	if err != nil {
		return newMatrix, fmt.Errorf("error splitting matrix: %s", err.Error())
	}
	bLeftU, bRightU, bLeftL, bRightL, err := matrix.SplitToCorners()
	if err != nil {
		return newMatrix, fmt.Errorf("error splitting matrix: %s", err.Error())
	}
	first, err := getFirst(aLeftU, aRightL, bLeftU, bRightL)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting first matrix: %s", err.Error())
	}
	second, err := getSecond(aLeftL, aRightL, bLeftU)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting second matrix: %s", err.Error())
	}
	third, err := getThird(aLeftU, bRightU, bRightL)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting third matrix: %s", err.Error())
	}
	fourth, err := getFourth(aRightL, bLeftU, bLeftL)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting fourth matrix: %s", err.Error())
	}
	fifth, err := getFifth(aLeftU, aRightU, bRightL)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting fifth matrix: %s", err.Error())
	}
	sixth, err := getSixth(aLeftU, aLeftL, bLeftU, bRightU)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting sixth matrix: %s", err.Error())
	}
	seventh, err := getSeventh(aRightU, aRightL, bLeftL, bRightL)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting seventh matrix: %s", err.Error())
	}
	newLeftU, err := newLeftU(&first, &fourth, &fifth, &seventh)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting new left upper matrix matrix: %s", err.Error())
	}
	newRightU, err := newRightU(&third, &fifth)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting new right upper matrix matrix: %s", err.Error())
	}
	newLeftL, err := newLeftL(&second, &fourth)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting new left lower matrix matrix: %s", err.Error())
	}
	newRightL, err := newRightL(&first, &third, &second, &sixth)
	if err != nil {
		return newMatrix, fmt.Errorf("error getting new right lower matrix matrix: %s", err.Error())
	}
	newMatrix.fillFromCorners(&newLeftU, &newRightU, &newLeftL, &newRightL)
	return newMatrix, nil
}

func getFirst(aLeftU *Matrix, aRightL *Matrix, bLeftU *Matrix, bRightL *Matrix) (Matrix, error) {
	var first Matrix
	aSum, err := aLeftU.Add(aRightL)
	if err != nil {
		return first, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	bSum, err := bLeftU.Add(bRightL)
	if err != nil {
		return first, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	first, err = aSum.MultiplyStrassen(&bSum)
	if err != nil {
		return first, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return first, nil
}

func getSecond(aLeftL *Matrix, aRightL *Matrix, bLeftU *Matrix) (Matrix, error) {
	var second Matrix
	aSum, err := aLeftL.Add(aRightL)
	if err != nil {
		return second, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	second, err = aSum.MultiplyStrassen(bLeftU)
	if err != nil {
		return second, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return second, nil
}

func getThird(aLeftU *Matrix, bRightU *Matrix, bRightL *Matrix) (Matrix, error) {
	var third Matrix
	bSub, err := bRightU.Substract(bRightL)
	if err != nil {
		return third, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	third, err = aLeftU.MultiplyStrassen(&bSub)
	if err != nil {
		return third, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return third, nil
}

func getFourth(aRightL *Matrix, bLeftU *Matrix, bLeftL *Matrix) (Matrix, error) {
	var fourth Matrix
	bSub, err := bLeftL.Substract(bLeftU)
	if err != nil {
		return fourth, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	fourth, err = aRightL.MultiplyStrassen(&bSub)
	if err != nil {
		return fourth, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return fourth, nil
}

func getFifth(aLeftU *Matrix, aRightU *Matrix, bRightL *Matrix) (Matrix, error) {
	var fifth Matrix
	aAdd, err := aLeftU.Add(aRightU)
	if err != nil {
		return fifth, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	fifth, err = aAdd.MultiplyStrassen(bRightL)
	if err != nil {
		return fifth, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return fifth, nil
}

func getSixth(aLeftU *Matrix, aLeftL *Matrix, bLeftU *Matrix, bRightU *Matrix) (Matrix, error) {
	var sixth Matrix
	aSub, err := aLeftL.Substract(aLeftU)
	if err != nil {
		return sixth, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	bSum, err := bLeftU.Add(bRightU)
	if err != nil {
		return sixth, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	sixth, err = aSub.MultiplyStrassen(&bSum)
	if err != nil {
		return sixth, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return sixth, nil
}

func getSeventh(aRightU *Matrix, aRightL *Matrix, bLeftL *Matrix, bRightL *Matrix) (Matrix, error) {
	var sixth Matrix
	aSub, err := aRightU.Substract(aRightL)
	if err != nil {
		return sixth, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	bSum, err := bRightL.Add(bLeftL)
	if err != nil {
		return sixth, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	sixth, err = aSub.MultiplyStrassen(&bSum)
	if err != nil {
		return sixth, fmt.Errorf("error during strassen multiply: %s", err.Error())
	}
	return sixth, nil
}

func newLeftU(first *Matrix, fourth *Matrix, fifth *Matrix, seventh *Matrix) (Matrix, error) {
	var leftU Matrix
	fSum, err := first.Add(fourth)
	if err != nil {
		return fSum, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	sSub, err := fSum.Substract(fifth)
	if err != nil {
		return sSub, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	leftU, err = sSub.Add(seventh)
	if err != nil {
		return leftU, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	return leftU, nil
}

func newRightU(third *Matrix, fifth *Matrix) (Matrix, error) {
	var rightU Matrix
	rightU, err := third.Add(fifth)
	if err != nil {
		return rightU, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	return rightU, nil
}

func newLeftL(second *Matrix, fourth *Matrix) (Matrix, error) {
	var leftL Matrix
	leftL, err := second.Add(fourth)
	if err != nil {
		return leftL, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	return leftL, nil
}

func newRightL(first *Matrix, third *Matrix, second *Matrix, sixth *Matrix) (Matrix, error) {
	var rightL Matrix
	fSum, err := first.Add(third)
	if err != nil {
		return fSum, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	sSub, err := fSum.Substract(second)
	if err != nil {
		return sSub, fmt.Errorf("error substracting matrices: %s", err.Error())
	}
	rightL, err = sSub.Add(sixth)
	if err != nil {
		return rightL, fmt.Errorf("error adding matrices: %s", err.Error())
	}
	return rightL, nil
}

func (m *Matrix) fillFromCorners(bLeftU *Matrix, bRightU *Matrix, bLeftL *Matrix, bRightL *Matrix) {
	oldSize := bLeftU.sizeRow
	for i := 0; i < oldSize; i++ {
		for j := 0; j < oldSize; j++ {
			m.valuesArray[i][j] = bLeftU.valuesArray[i][j]
		}
		for j := oldSize; j < 2*oldSize; j++ {
			m.valuesArray[i][j] = bRightU.valuesArray[i][j-oldSize]
		}
	}
	for i := oldSize; i < 2*oldSize; i++ {
		for j := 0; j < oldSize; j++ {
			m.valuesArray[i][j] = bLeftL.valuesArray[i-oldSize][j]
		}
		for j := oldSize; j < 2*oldSize; j++ {
			m.valuesArray[i][j] = bRightL.valuesArray[i-oldSize][j-oldSize]
		}
	}
}

package matrix

import (
	"fmt"
	"sync"
)

func (m *Matrix) fillCornerParallel(newMatrix Matrix, corner int, wg *sync.WaitGroup) {
	m.fillCorner(&newMatrix, corner)
	wg.Done()
}

func (m *Matrix) SplitToCornersParallel(matrixLeftU *Matrix, matrixRightU *Matrix, matrixLeftL *Matrix, matrixRightL *Matrix) {

	sizeNew := m.sizeColumn / 2

	matrixLeftU.Initialize(sizeNew, sizeNew)
	matrixRightU.Initialize(sizeNew, sizeNew)
	matrixLeftL.Initialize(sizeNew, sizeNew)
	matrixRightL.Initialize(sizeNew, sizeNew)

	m.wg.Add(4)

	go m.fillCornerParallel(*matrixLeftU, CORNER_LEFT_U, &m.wg)
	go m.fillCornerParallel(*matrixRightU, CORNER_RIGHT_U, &m.wg)
	go m.fillCornerParallel(*matrixLeftL, CORNER_LEFT_L, &m.wg)
	go m.fillCornerParallel(*matrixRightL, CORNER_RIGHT_L, &m.wg)

	m.wg.Wait()

}

func (m *Matrix) MultiplyStrassenParallel(matrix Matrix, newMatrix *Matrix) {
	if m.sizeColumn != matrix.sizeRow {
		fmt.Println("matrices sizes don't match")
		return
	}
	if m.sizeColumn != m.sizeRow || matrix.sizeColumn != matrix.sizeRow {
		fmt.Println("strassen algorithm uses square matrices")
		return
	}
	size := m.sizeColumn
	if size%2 != 0 || size < 32 {
		*newMatrix, _ = m.Multiply(&matrix)
		return
	}
	newMatrix.Initialize(m.sizeRow, matrix.sizeColumn)
	var aLeftU Matrix
	var aRightU Matrix
	var aLeftL Matrix
	var aRightL Matrix
	m.SplitToCornersParallel(&aLeftU, &aRightU, &aLeftL, &aRightL)
	var bLeftU Matrix
	var bRightU Matrix
	var bLeftL Matrix
	var bRightL Matrix

	matrix.SplitToCornersParallel(&bLeftU, &bRightU, &bLeftL, &bRightL)

	m.wg.Add(7)
	var first Matrix
	go getFirstParallel(aLeftU, aRightL, bLeftU, bRightL, &first, &m.wg)
	var second Matrix
	go getSecondParallel(aLeftL, aRightL, bLeftU, &second, &m.wg)
	var third Matrix
	go getThirdParallel(aLeftU, bRightU, bRightL, &third, &m.wg)
	var fourth Matrix
	go getFourthParallel(aRightL, bLeftU, bLeftL, &fourth, &m.wg)
	var fifth Matrix
	go getFifthParallel(aLeftU, aRightU, bRightL, &fifth, &m.wg)
	var sixth Matrix
	go getSixthParallel(aLeftU, aLeftL, bLeftU, bRightU, &sixth, &m.wg)
	var seventh Matrix
	go getSeventhParallel(aRightU, aRightL, bLeftL, bRightL, &seventh, &m.wg)
	m.wg.Wait()

	newLeftU, err := newLeftU(&first, &fourth, &fifth, &seventh)
	if err != nil {
		fmt.Printf("error getting newLeftU matrix: %n", err.Error())
		return
	}
	newRightU, err := newRightU(&third, &fifth)
	if err != nil {
		fmt.Printf("error getting newRightU matrix: %n", err.Error())
		return
	}
	newLeftL, err := newLeftL(&second, &fourth)
	if err != nil {
		fmt.Printf("error getting newLeftL matrix: %n", err.Error())
		return
	}
	newRightL, err := newRightL(&first, &third, &second, &sixth)
	if err != nil {
		fmt.Printf("error getting newRightL matrix: %n", err.Error())
		return
	}
	//newMatrix.fillFromCorners(newLeftU, newRightU, newLeftL, newRightL)
	newMatrix.fillFromCornersParallel(newLeftU, newRightU, newLeftL, newRightL)
}

func getFirstParallel(aLeftU Matrix, aRightL Matrix, bLeftU Matrix, bRightL Matrix, first *Matrix, wg *sync.WaitGroup) {
	aSum, err := aLeftU.Add(&aRightL)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	bSum, err := bLeftU.Add(&bRightL)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	aSum.MultiplyStrassenParallel(bSum, first)
	wg.Done()
}

func getSecondParallel(aLeftL Matrix, aRightL Matrix, bLeftU Matrix, second *Matrix, wg *sync.WaitGroup) {
	aSum, err := aLeftL.Add(&aRightL)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	aSum.MultiplyStrassenParallel(bLeftU, second)
	wg.Done()
}

func getThirdParallel(aLeftU Matrix, bRightU Matrix, bRightL Matrix, third *Matrix, wg *sync.WaitGroup) {
	bSub, err := bRightU.Substract(&bRightL)
	if err != nil {
		fmt.Printf("error substracting matrices: %s\n", err.Error())
		return
	}
	aLeftU.MultiplyStrassenParallel(bSub, third)
	wg.Done()
}

func getFourthParallel(aRightL Matrix, bLeftU Matrix, bLeftL Matrix, fourth *Matrix, wg *sync.WaitGroup) {
	bSub, err := bLeftL.Substract(&bLeftU)
	if err != nil {
		fmt.Printf("error substracting matrices: %s\n", err.Error())
		return
	}
	aRightL.MultiplyStrassenParallel(bSub, fourth)
	wg.Done()
}

func getFifthParallel(aLeftU Matrix, aRightU Matrix, bRightL Matrix, fifth *Matrix, wg *sync.WaitGroup) {
	aAdd, err := aLeftU.Add(&aRightU)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	aAdd.MultiplyStrassenParallel(bRightL, fifth)
	wg.Done()
}

func getSixthParallel(aLeftU Matrix, aLeftL Matrix, bLeftU Matrix, bRightU Matrix, sixth *Matrix, wg *sync.WaitGroup) {
	aSub, err := aLeftL.Substract(&aLeftU)
	if err != nil {
		fmt.Printf("error substracting matrices: %s\n", err.Error())
		return
	}
	bSum, err := bLeftU.Add(&bRightU)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	aSub.MultiplyStrassenParallel(bSum, sixth)
	wg.Done()
}

func getSeventhParallel(aRightU Matrix, aRightL Matrix, bLeftL Matrix, bRightL Matrix, seventh *Matrix, wg *sync.WaitGroup) {
	aSub, err := aRightU.Substract(&aRightL)
	if err != nil {
		fmt.Printf("error substracting matrices: %s\n", err.Error())
		return
	}
	bSum, err := bRightL.Add(&bLeftL)
	if err != nil {
		fmt.Printf("error adding matrices: %s\n", err.Error())
		return
	}
	aSub.MultiplyStrassenParallel(bSum, seventh)
	wg.Done()
}

func (m *Matrix) fillFromCornersParallel(bLeftU Matrix, bRightU Matrix, bLeftL Matrix, bRightL Matrix) {
	oldSize := bLeftU.sizeRow
	m.wg.Add(4)
	go func() {
		defer m.wg.Done()
		for i := 0; i < oldSize; i++ {
			for j := 0; j < oldSize; j++ {
				m.valuesArray[i][j] = bLeftU.valuesArray[i][j]
			}
		}
	}()
	go func() {
		defer m.wg.Done()
		for i := 0; i < oldSize; i++ {
			for j := oldSize; j < 2*oldSize; j++ {
				m.valuesArray[i][j] = bRightU.valuesArray[i][j-oldSize]
			}
		}
	}()
	go func() {
		defer m.wg.Done()
		for i := oldSize; i < 2*oldSize; i++ {
			for j := 0; j < oldSize; j++ {
				m.valuesArray[i][j] = bLeftL.valuesArray[i-oldSize][j]
			}
		}
	}()
	go func() {
		defer m.wg.Done()
		for i := oldSize; i < 2*oldSize; i++ {
			for j := oldSize; j < 2*oldSize; j++ {
				m.valuesArray[i][j] = bRightL.valuesArray[i-oldSize][j-oldSize]
			}
		}
	}()
	m.wg.Wait()
}

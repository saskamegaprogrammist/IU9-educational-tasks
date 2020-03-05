#include <iostream>
#include <limits>
using namespace std;


void gaussDiagonal(float** matrix, float* answer, float* variables, int size) {
    float * alphas;
    float * betas;
    alphas = new float[size];
    betas = new float[size];
    alphas[0] = -matrix[0][1] / matrix[0][0];
    betas[0] = answer[0] / matrix[0][0];
    for (int i=1; i < size; i++) {
        float koeff = matrix[i][i] + matrix[i][i-1]*alphas[i-1];
        if (i != size-1) alphas[i] = -matrix[i][i+1] / koeff;
        betas[i] = (answer[i] - matrix[i][i-1]* betas[i-1]) / koeff;
    }
    variables[size-1] = betas[size-1];
    for (int i=size-2; i>=0; i--) {
        variables[i] = alphas[i]*variables[i+1] + betas[i];
    }
    return;

}

int main() {
    cout << "Enter size of the matrix" << endl;
    int size;
    float ** matrix;
    float * answer;
    float * variables;
    cin >> size;
    matrix = new float*[size];
    answer = new float[size];
    variables = new float[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new float[size];
    }
    cout << "Enter matrix" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
    cout << "Enter answer" << endl;
    for  (int i = 0; i < size; i++) {
        cin >> answer[i];
    }
    gaussDiagonal(matrix, answer, variables, size);
    std::cout.precision(15);
    std::cout.setf( std::ios::fixed, std:: ios::floatfield);
    for (int i=0 ; i < size; i++) {
        cout << variables[i] << endl;
    }

    return 0;
}

//3 1 0 0
//1 3 1 0
//0 1 3 1
//0 0 1 3

//4 5 5 4

//1.000000000000000
//0.999999880790710
//1.000000000000000
//1.000000000000000
// отразить в отчете, что нет методологической погрешности, но нет вычислительной
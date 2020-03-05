//
// Created by alexis on 15.09.19.
//

#include <iostream>
using namespace std;

int main() {
    cout << "Enter size of the permutation" << endl;
    int size;
    int ** perm;
    cin >> size;
    perm = new int* [2];
    for (int i=0; i<2; i++){
        perm[i] = new int[size];
    }
    int checksum=0;
    int sum=0;
    for (int i=0; i<size;i++) sum+=(i+1);
    cout << "Enter permutation" << endl;
    for (int i=0; i<2; i++){
        for (int j=0; j<size; j++){
            cin >> perm[i][j];
            if (perm[i][j] > size){
                cout << "ERROR" ;
                return -1;
            }
            checksum+=perm[i][j];
        }
        if (checksum!=sum){
            cout << "ERROR" ;
            return -1;
        }
        checksum=0;
    }
    int * permNew;
    permNew = new int[size];
    for (int i = 0; i < size; i++) {
        permNew[i] = perm[1][i];
    }
    int count=0;
    for (;;) {
        for (int i = 0; i < size; i++) {
            if (perm[0][i] == permNew[i]) count++;
            for (int j = 0; j < size; j++) {
                if (perm[0][j] == permNew[i]) {
                    permNew[i] = perm[1][j];
                    break;
                }
            }
        }
        if (count == size) break;
        for (int i = 0; i < size; i++) {
            cout << perm[0][i] << " ";
        }
        cout << endl;
        for (int i = 0; i < size; i++) {
            cout << permNew[i] << " ";
        }
        cout << endl << endl;
        count=0;
    }
    delete permNew;
    for (int i=0; i<2; i++){
        delete perm[i];
    }
    delete perm;
}
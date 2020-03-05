#include <iostream>
using namespace std;

int main() {
    int table [25][25];
    table[0][0] = 0;
    for (int i=1; i<25; i++){
        table[0][i]=i-1;
        table[i][0]=i-1;
    }
    for (int i=1; i<25; i++){
        for (int j=1; j<25;j++){
            table[i][j] = table[i][0] * table[0][j] % 24;
        }
    }

    for (int i=0; i<25; i++){
        for (int j=0; j<25; j++){
            if (i==0 && j==0) cout << "*   |";
            else {
                if (table[i][j] < 10) cout << table[i][j] << "  " ;
                else  cout << table[i][j] << " ";
                cout << "| ";
            }
        }
        cout << endl;
        for (int j=0; j<125; j++) cout<<"-";
        cout << endl;
    }
}
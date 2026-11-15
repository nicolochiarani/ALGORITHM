//This file contains the most common Algorithm on Matrices.
// Input is read from a text file containing the matrix's columns and row and its elements.
// You can modify the numbers in the input file to test the algorithms.

#include <fstream>
#include <iostream>

using namespace std;

void Matrix(int **Matrix, int rows, int columns);

int main(int argc, char **argv){
    ifstream in("inputMatrix.txt");
    if(!in.is_open()){
         cout<<"The input file does not exist in your directory!!"<<endl;
    exit(1);
    }
    int columns, rows;
    in>>columns>>rows;
    int **matrix = new int*[rows];
    for(int i=0;i<rows;i++)matrix[i]=new int[columns];
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            in>>matrix[i][j];
        }
    }
    Matrix(matrix, rows, columns);
    for(int i=0;i<rows;i++)delete [] matrix[i];
    delete [] matrix;
    in.close();
    return 0;
}



int Kadane(int *array, int length){
    int res=0, sub=0;
    if(length==0)return res;                         //O(n) time complexity
    for(int i=0;i<length;i++){                  
        sub+=array[i];
        if(res<sub)res=sub;
        if(sub<0)sub=0;
    }
    return res;
}

void MaxSubMatrix(int **Matrix, int rows, int columns){
        int *tmp = new int[columns]();                          //O(r^2*c) where r are the rows and c columns
        int res=Matrix[0][0], kadaneRes,k=0;                    //Use Kadane (Array Algorithms) on Matrix (2D=>1D)
        while(k<rows){
        for(int i=k;i<rows;i++){
            for(int j=0;j<columns;j++){
                tmp[j]+=Matrix[i][j];
            }
            kadaneRes=Kadane(tmp,columns);
            if(res<kadaneRes)res=kadaneRes;
        }
        k++;
        for(int i=0;i<columns;i++)tmp[i]=0;
    }
        delete [] tmp;
        cout<<"The Maximun submatrix sum is: "<<res<<endl;
}

void PrintMatrix(int **Matrix, int rows, int columns){
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            cout<<Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}



void Matrix(int **Matrix, int rows, int columns){
    PrintMatrix(Matrix, rows, columns);
    MaxSubMatrix(Matrix, rows, columns);
}
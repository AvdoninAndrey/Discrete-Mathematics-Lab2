#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
using namespace std;

const string nameOfItems = "ABCDEFZ"; // // Название пунктов
const int countOfItems = 7; // Количество вершин
int matrixBufferResult[countOfItems][countOfItems] = {0};
int matrixShortestPaths[countOfItems][countOfItems];
int matrixRoute[countOfItems][countOfItems] = {             // Наша схема маршрутов (матрица расстояний)
    {0,4,9,0,0,0,21},
    {4,0,3,0,0,0,0},
    {9,3,0,2,0,11,20},
    {0,0,2,0,4,0,0},
    {0,0,0,4,0,0,4},
    {0,0,11,0,0,0,2},
    {21,0,20,0,4,2,0}
};

void printMatrixRoute(const int countVertices, const int matrixRoute[countOfItems][countOfItems]) // Печатает исходную матрицу расстояний
{

    cout << "Tранспортная сеть, заданная матрицей расстояний:" << endl;
    for (size_t i = 0; i < nameOfItems.size(); i++) {
        cout <<"\t" <<  setw(4) << nameOfItems[i];
    }
    cout << endl;
    for (int i = 0; i < countVertices; i++) {
        cout << nameOfItems[i] << setw(3);
        for (int j = 0; j < countVertices; j++) {
            cout << "\t" << setw(4) << matrixRoute[i][j];
        }
        cout << "\n";
    }
}

void printResult(const int & countVertices, const int matrixRoute[countOfItems][countOfItems]) // Печатает матрицу длин кратчайших путей между любыми двумя парами вершин
{
    cout << endl;
    cout << "Матрица длин кратчайших путей между любыми двумя парами вершин:" << endl;
    for (size_t i = 0; i < nameOfItems.size(); i++) {
        cout <<"\t" <<  setw(4) << nameOfItems[i];
    }
    cout << endl;
    for (int i = 0; i < countVertices; i++) {
        cout << nameOfItems[i] << setw(3);
        for (int j = 0; j < countVertices; j++) {
            cout << "\t" << setw(4) << matrixRoute[i][j];
        }
        cout << "\n";
    }
}

void restorePath(const int matrixPaths[countOfItems][countOfItems], const char startItemLetter, const char finishItemLetter) // Восстанавливает путь между двумя любыми вершинами и его длину
{
    int startNum, finishNum;
    for(size_t i = 0; i < nameOfItems.size(); i++) {
        if (startItemLetter == nameOfItems[i]) {
            startNum = i;
        }
    }
    for(size_t i = 0; i < nameOfItems.size(); i++) {
        if (finishItemLetter == nameOfItems[i]) {
            finishNum = i;
        }
    }
    int flag = startNum;
    cout << "Кратчайший путь из вершины " << startItemLetter << " в вершину " << finishItemLetter << ": <";
    cout << " " << startItemLetter;
    while (flag != finishNum) {
        flag = matrixPaths[flag][finishNum];
        cout << "-" << nameOfItems[flag];
    }
    cout << " >";
    int lenghtPath = matrixBufferResult[startNum][finishNum];
    cout <<"\nДлина пути: " << lenghtPath << endl;
}

void floydsAlgorithm(const int &countVertices, int matrixRoute[countOfItems][countOfItems]) //алгоритм Флойда
{
    for(int i=0; i < countVertices; i++) {
        for(int j=0; j < countVertices; j++) {
            matrixShortestPaths[i][j]=j;
        }
    }

    for (int i=0; i < countVertices; i++) matrixRoute[i][i]=0;
    for (int k = 0; k < countVertices; k++) {
        for (int i = 0; i < countVertices; i++) {
            for (int j = 0; j< countVertices; j++) {
                if (matrixRoute[i][k] && matrixRoute[k][j] && i!=j) {
                    if (matrixRoute[i][k] + matrixRoute[k][j] < matrixRoute[i][j] || matrixRoute[i][j] == 0) {
                        matrixRoute[i][j] = matrixRoute[i][k] + matrixRoute[k][j];
                        matrixBufferResult[i][j] = matrixRoute[i][k] + matrixRoute[k][j];
                        matrixShortestPaths[i][j] = matrixShortestPaths[i][k];
                    } else {
                        matrixBufferResult[i][j] = matrixRoute[i][j];
                    }
                }
            }

        }
    }
    printResult(countOfItems, matrixRoute);
}

int main()
{
    printMatrixRoute(countOfItems, matrixRoute);
    floydsAlgorithm(countOfItems, matrixRoute);
    restorePath(matrixShortestPaths, 'A', 'Z');
    return 0;
}

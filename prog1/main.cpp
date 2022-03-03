#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
const string nameOfItems = "ABCDEFZ"; // Название пунктов
const int countOfItems = 7; // Количество вершин
int currentPathLength[countOfItems]; // Для длин текущего путей
int matrixRoute[countOfItems][countOfItems] = { {0,4,9,0,0,0,21}, // Наша схема маршрутов (матрица расстояний)
    {4,0,3,0,0,0,0},
    {9,3,0,2,0,11,20},
    {0,0,2,0,4,0,0},
    {0,0,0,4,0,0,4},
    {0,0,11,0,0,0,2},
    {21,0,20,0,4,2,0}
};


void printMatrixRoute(int matrixRoute[countOfItems][countOfItems]) // Печатает исходную матрицу расстояний
{

    cout << "Tранспортная сеть, заданная матрицей расстояний" << endl;
    for (size_t i = 0; i < nameOfItems.size(); i++) {
        cout <<"\t" <<  setw(4) << nameOfItems[i];
    }
    cout << endl;
    for (int i = 0; i < countOfItems; i++) {
        cout << nameOfItems[i] << setw(3);
        for (int j = 0; j < countOfItems; j++) {
            cout << "\t" << setw(4) << matrixRoute[i][j];
        }
        cout << "\n";
    }
}
vector<int> algorithmDijkstra(int matrixRoute[countOfItems][countOfItems])
{
    vector<int> parent(countOfItems, -1);
    int longDistance = 1000000;

    int min = 0, indexMin =0;
    bool passedVertex[7];
    for (int i = 0; i < countOfItems; i++) {
        currentPathLength[i] = longDistance;
        passedVertex[i] = false;
    }

    currentPathLength[0] = 0;            // наш узел. Откуда начинаем идти.
    // Начальный пункт А в данном случае. (Пройденное расстояние = 0)
    cout << "\n";
    for (int i = 0; i < countOfItems-1; i++) {
        min = longDistance;
        for (int j = 0; j < countOfItems; j++) {                    // Находим пункт с которого мы начинаем идти
            if (!passedVertex[j] && currentPathLength[j] < min) {
                min = currentPathLength[j];
                indexMin = j;
            }
        }
        passedVertex[indexMin] = true; // помечаем выбранный пункт как пройденный (стоим в нём)
        for (int j = 0; j < countOfItems; j++) {
            /* условие: если какой-либо  пункт не пройден, смежен с тем, где мы находимся, и сумма веса выбранного пункта и смежного ребра
            будет меньше, чем текущая длина пройденного пути на данный момент, то  - меняем значение.*/
            if (!passedVertex[j] && matrixRoute[indexMin][j] > 0 && currentPathLength[indexMin] != longDistance &&
                currentPathLength[indexMin] + matrixRoute[indexMin][j] < currentPathLength[j]) {
                currentPathLength[j] = currentPathLength[indexMin] + matrixRoute[indexMin][j];
                parent.at(j) = indexMin;    // запоминаем предка вершины (пунтка)
            }
        }
    }

    return parent;
}
void printResult(vector<int> parent, const char finalItemLetter) // Печатаем результат (сам путь и расстояние)
{
    int finalItemNum;
    for (size_t i = 0; i < nameOfItems.size(); i++) {
        if (finalItemLetter == nameOfItems[i]) {
            finalItemNum = i;
        }
    }
    vector<int>temp;
    for (int i = finalItemNum; i != -1; i = parent.at(i)) {
        temp.push_back(i);
    }
    reverse(temp.begin(), temp.end());
    cout << "Кратчайший маршрут от Пункта А: < ";
    for (size_t i = 0; i < temp.size(); ++i) {
        if (i+1 == temp.size()) {
            cout << nameOfItems[temp.at(i)];
        } else {
            cout <<  nameOfItems[temp.at(i)] << "-";
        }
    }
    cout << " >" << endl;
    cout << "Длина пути: " << currentPathLength[finalItemNum] << "\n";

}

int main()
{

    printMatrixRoute(matrixRoute);
    vector<int> parent = algorithmDijkstra(matrixRoute);
    char finalItem;
    cout << "Укажите пункт до которого нужно найти кратчейшее расстояние: ";
    cin >> finalItem;
    printResult(parent, finalItem);
    return 0;
}

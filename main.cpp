#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<time.h>
#include<chrono>
#include<ctime>
using namespace std;
using namespace std::chrono;

int testarray[10] = {1, 3, 5, 11, 9, 2, 4, 6, 8, 10};
int testarray2[10] = {1, 3, 5, 11, 9, 2, 4, 6, 8, 10};

int Partition(int PArray[], int Pstart, int Pend) {
    int x = PArray[Pend];
    int i = Pstart - 1;
    for(int j = Pstart; j < Pend; j++) {
        if (PArray[j] <= x) {
            i = i + 1;
            int temp = PArray[i];
            PArray[i] = PArray[j];
            PArray[j] = temp;
        }
    }
    int temp = PArray[i+1];
    PArray[i+1] = PArray[Pend];
    PArray[Pend] = temp;
    return i+1;

}
int RP(int RPArray[], int RPstart, int RPend) { //RP = Random Partition
    int i = rand()%(RPend-RPstart + 1) + RPstart;
    int temp = RPArray[RPend];
    RPArray[RPend] = RPArray[i];
    RPArray[i] = temp;
    return Partition(RPArray, RPstart, RPend);
}

 int RandomizedSelect(int Array[], int start, int end, int target) {
    if (start == end) {
        return Array[start];
    }
    int pivot = RP(Array, start, end);
    int k = pivot - start+1;
    if (target == k) {
        return Array[pivot];
    } else if (target < k) {
        return RandomizedSelect(Array, start, pivot-1, target);
    } else {
        return RandomizedSelect(Array, pivot+1, end, target-k);
    }


}

void CocktailSort(int a[], int n){

bool swapped = true;
int csStart = 0;
int csEnd = n - 1;

while(swapped) {
    swapped = false;

    for (int i = csStart; i < csEnd; i++){
        if (a[i] > a[i+1]) {
            swap(a[i], a[i+1]);
            swapped = true;
        }
    }
    if(!swapped){
        break;
    }
    swapped = false;

    --csEnd;

    for(int i = csEnd - 1; i >= csStart; --i){
        if (a[i] > a[i + 1]) {
            swap(a[i], a[i+1]);
            swapped = true;
        }
    }
    ++csStart;
}
}

int main()
{

    const int dataSize = 1000;
    int dataArray[dataSize];
    int dataArray2[dataSize];
    int dataArray3[dataSize];
    int dataArray4[dataSize];
    fstream dataSet("medium.csv");
    //fstream dataSet("small.csv");
    if (dataSet.is_open()) {
        for(int i = 0; i < dataSize; i++) {
            string lineElement;
            getline(dataSet, lineElement, ',');
            dataArray[i] = stoi(lineElement);
            dataArray2[i] = stoi(lineElement);
            dataArray3[i] = stoi(lineElement);
            dataArray4[i] = stoi(lineElement);
        }
    }
    int n = sizeof(dataArray2) / sizeof(dataArray2[0]);

//    printArray(dataArray, dataSize, 20);

    cout << "---" << endl;

    int inputStart = 0;
    int inputEnd = dataSize-1;
    int inputTarget = 500;
    steady_clock::time_point randSelectStart = steady_clock::now();
    cout << RandomizedSelect(dataArray, inputStart, inputEnd, inputTarget) << endl;
    cout << RandomizedSelect(dataArray4, inputStart, inputEnd, inputTarget) << endl;
    cout << RandomizedSelect(dataArray3, inputStart, inputEnd, inputTarget) << endl;
    steady_clock::time_point randSelectStop = steady_clock::now();
    auto randSelectDuration = randSelectStop - randSelectStart;
    cout << "--- Randomized Select Running Time: " << duration <double, milli> (randSelectDuration).count() << " ms " << " ---" << endl << endl;

    steady_clock::time_point CocktailSortStart = steady_clock::now();
    CocktailSort(dataArray2, dataSize);
    cout << dataArray2[inputTarget-1];
    steady_clock::time_point CocktailSortStop = steady_clock::now();
    auto CocktailSortDuration = CocktailSortStop - CocktailSortStart;
    cout << "--- CocktailSort Running Time: " << duration <double, milli> (CocktailSortDuration).count() << " ms " << " ---" << endl << endl;
 return 0;
}



#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using vecInt = std::vector<int>;
using std::cout;
using namespace std::chrono;
using std::endl;

vecInt creatRandomArray(int coutnOfNumber) {

  vecInt resultSequence(coutnOfNumber);
  std::mt19937 gen(std::time(0));
  // Creat init sequence
  vecInt::iterator it = resultSequence.begin();
  for (int i; i < coutnOfNumber; i++) {
    *it = i;
    it++;
  }
  // Data randomization
  for (int i = 0; i < coutnOfNumber - 1; i++) {

    std::uniform_int_distribution<> uid(i, coutnOfNumber - 1);
    std::swap(resultSequence[i], resultSequence[uid(gen)]);
  }

  return resultSequence;
}

void insertSort(vecInt &input) {

  for (int i = 1; i < input.size(); i++) {
    for (int j = i; j > 0 && input[j - 1] > input[j]; j--) {
      std::swap(input[j - 1], input[j]);
    }
  }
}

void selectionSort(vecInt &input) {
  int minElementIndex = 0;
  for (int i = 0; i < input.size(); i++) {
    minElementIndex = i;
    for (int j = i; j < input.size(); j++) {
      if (input[minElementIndex] > input[j]) {
        minElementIndex = j;
      }
    }
    if (minElementIndex != i)
      std::swap(input[i], input[minElementIndex]);
  }
}

int main(int argc, char *argv[]) {

 
  time_point<high_resolution_clock> star, end, star2, end2;
 
  star = high_resolution_clock::now();
  vecInt rArray = creatRandomArray(80000);
  selectionSort(rArray);
  end = high_resolution_clock::now();

  star2 = high_resolution_clock::now();
  vecInt rArray2 = creatRandomArray(100000);
  insertSort(rArray2);
  end2 = high_resolution_clock::now();

  int elapsedTime = duration_cast<milliseconds>(end - star).count();
  int elapsedTime2 = duration_cast<milliseconds>(end2 - star2).count();

  std::time_t endTime1 = high_resolution_clock::to_time_t(end);
  std::time_t endTime2 = high_resolution_clock::to_time_t(end2);

  cout << "Время завершения выполнения selectionSort: " << ctime(&endTime1)
       << "Время выполнения selectiomSort: " << elapsedTime << " milliseconds"
       << endl
       << "Время завершения выполнения insertSort: " << ctime(&endTime2)
       << "Время выполнения insertSort: " << elapsedTime2 << " milliseconds"
       << endl;
  //----------------------
  return 0;
}
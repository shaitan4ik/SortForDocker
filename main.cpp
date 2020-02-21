#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#define ELEMENT_COUNT 10
using vecInt = std::vector<int>;
using std::cout;
using namespace std::chrono;
using std::endl;

vecInt creatRandomArray(int coutnOfNumber) {

  vecInt resultSequence(coutnOfNumber);
  std::mt19937 gen(std::time(0));
  // Creat init sequence
  vecInt::iterator it = resultSequence.begin();
  for (int i = 0; i < coutnOfNumber; i++) {
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

void mergeSort(vecInt &input, vecInt &scratch, int start, int end) {

  if (start == end)
    return;

  int midpoint = (start + end) / 2;
  mergeSort(input, scratch, start, midpoint);
  mergeSort(input, scratch, midpoint + 1, end);

  int left_index = start;
  int right_index = midpoint + 1;
  int scratch_index = left_index;
  while (left_index <= midpoint and right_index <= end) {
    if (input[left_index] < input[right_index]) {
      scratch[scratch_index] = input[left_index];
      ++left_index;
    } else {
      scratch[scratch_index] = input[right_index];
      ++right_index;
    }
    scratch_index++;
  }
  for (int i = left_index; i <= midpoint; i++) {
    scratch[scratch_index] = input[i];
    scratch_index++;
  }
  for (int i = right_index; i <= end; i++) {
    scratch[scratch_index] = input[i];
    scratch_index++;
  }
  for (int i = start; i <= end; i++) {
    input[i] = scratch[i];
  }
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
  vecInt rArray = creatRandomArray(10);

  star = high_resolution_clock::now();
  selectionSort(rArray);
  end = high_resolution_clock::now();
  vecInt rArray2 = creatRandomArray(ELEMENT_COUNT);
  star2 = high_resolution_clock::now();

  vecInt temp_array(ELEMENT_COUNT);

  mergeSort(rArray2, temp_array, 0, ELEMENT_COUNT - 1);
  // selectionSort(rArray2);
  /* for (auto m : rArray2) {
     cout << m << endl;
   }*/

  end2 = high_resolution_clock::now();

  int elapsedTime = duration_cast<nanoseconds>(end - star).count();
  int elapsedTime2 = duration_cast<nanoseconds>(end2 - star2).count();

  std::time_t endTime1 = high_resolution_clock::to_time_t(end);
  std::time_t endTime2 = high_resolution_clock::to_time_t(end2);

  cout << "Время завершения выполнения selectionSort: " << ctime(&endTime1)
       << "Время выполнения selectiomSort: " << elapsedTime << " milliseconds"
       << endl
       << "Время завершения выполнения insertSort: " << ctime(&endTime2)
       << "Время выполнения insertSort: " << elapsedTime2 << " milliseconds"
       << endl;
  //----------------------*/

  return 0;
}
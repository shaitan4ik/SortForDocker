#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>
#include <vector>
#define ELEMENT_COUNT 1000

using timerType = long long int;
using vecIntType = long long int;
using vecInt = std::vector<vecIntType>;
using std::cout;
using namespace std::chrono;
using std::endl;

std::ofstream logFile("log.log", std::ios::app);

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

vecInt mergeVecInt(const vecInt &left, const vecInt &right) {

  vecInt result;
  int left_it, right_it = 0;

  while (left_it < left.size() && right_it < right.size()) {
    if (left[left_it] < right[right_it]) {
      result.push_back(left[left_it]);
      left_it++;
    } else {
      result.push_back(right[right_it]);
      right_it++;
    }
  }
  while (left_it < left.size()) {
    result.push_back(left[left_it]);
    left_it++;
  }
  while (right_it < right.size()) {
    result.push_back(right[right_it]);
    right_it++;
  }
  return result;
}

vecInt parallelMergeSort(vecInt &input, int numThreads) {
  // Condition of end recursive call
  if (input.size() == 1) {
    return input;
  }
  // Find the middle vector

  vecInt::iterator middle = input.begin() + input.size() / 2;

  // Creat two left and right part vector

  vecInt left(input.begin(), middle);
  vecInt right(middle, input.end());
  if (numThreads > 1) {
#pragma omp parallel sections
    {
#pragma omp section
      { left = parallelMergeSort(left, numThreads / 2); }
#pragma omp section
      { right = parallelMergeSort(right, numThreads - numThreads / 2); }
    }
  } else {
    parallelMergeSort(left, numThreads);
    parallelMergeSort(right, numThreads);
  }
  return mergeVecInt(left, right);
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

  time_point<high_resolution_clock> star, end, star2, end2, start3, end3;
  vecInt rArray = creatRandomArray(ELEMENT_COUNT);

  star = high_resolution_clock::now();
  selectionSort(rArray);
  end = high_resolution_clock::now();
  vecInt rArray2 = creatRandomArray(ELEMENT_COUNT);
  star2 = high_resolution_clock::now();

  vecInt temp_array(ELEMENT_COUNT);

  mergeSort(rArray2, temp_array, 0, ELEMENT_COUNT - 1);

  end2 = high_resolution_clock::now();

  vecInt rArray3(creatRandomArray(ELEMENT_COUNT));

  start3 = high_resolution_clock::now();

  parallelMergeSort(rArray3, omp_get_max_threads());

  end3 = high_resolution_clock::now();

  timerType elapsedTime = duration_cast<nanoseconds>(end - star).count();
  timerType elapsedTime2 = duration_cast<nanoseconds>(end2 - star2).count();
  timerType elapsedTime3 = duration_cast<nanoseconds>(end3 - start3).count();

  std::time_t endTime1 = high_resolution_clock::to_time_t(end);
  std::time_t endTime2 = high_resolution_clock::to_time_t(end2);
  std::time_t endTime3 = high_resolution_clock::to_time_t(end3);

  cout << "Время завершения выполнения selectionSort: " << ctime(&endTime1)
       << "Время выполнения selectiomSort: " << elapsedTime << " nanoseconds"
       << endl
       << "Время завершения выполнения insertSort: " << ctime(&endTime2)
       << "Время выполнения insertSort: " << elapsedTime2 << " nanoseconds"
       << endl
       << "Время завершения parallelMergeSort: " << ctime(&endTime3)
       << "Время выполнения parallelMergeSort: " << elapsedTime3
       << "  nanoseconds" << std::endl;
  if (logFile.is_open()) {
    logFile << "Время завершения выполнения selectionSort: " << ctime(&endTime1)
            << "Время выполнения selectiomSort: " << elapsedTime
            << " nanoseconds" << endl
            << "Время завершения выполнения insertSort: " << ctime(&endTime2)
            << "Время выполнения insertSort: " << elapsedTime2 << " nanoseconds"
            << endl
            << "Время завершения parallelMergeSort: " << ctime(&endTime3)
            << "Время выполнения parallelMergeSort: " << elapsedTime3
            << "  nanoseconds" << std::endl;
  }

  return 0;
}
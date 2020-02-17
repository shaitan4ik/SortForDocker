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
    }
  }
}

int main(int argc, char *argv[]) {
  // Start timeCounter
  time_point<high_resolution_clock> star, end;
  star = high_resolution_clock::now();
  //---------------------
  // Main block
  vecInt rArray = creatRandomArray(1000);
  for (auto m : rArray) {
    cout << m << endl;
  }
  insertSort(rArray);
  for (auto m : rArray) {
    cout << m << endl;
  }
  // End block
  // End timeCounter
  end = high_resolution_clock::now();

  int elapsedTime = duration_cast<milliseconds>(end - star).count();
  std::time_t endTime = high_resolution_clock::to_time_t(end);

  cout << "Время завершения выполнения: " << ctime(&endTime)
       << "Время выполнения: " << elapsedTime << " milliseconds" << endl;
  //----------------------
  return 0;
}
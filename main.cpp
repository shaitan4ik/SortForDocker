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
  for (auto m : resultSequence) {
    std::cout << m << std::endl;
  }
  // Data randomization

  for (int i = 0; i < coutnOfNumber - 1; i++) {

    std::uniform_int_distribution<> uid(i, coutnOfNumber - 1);
    std::swap(resultSequence[i], resultSequence[uid(gen)]);
  }

  return resultSequence;
}

int main(int argc, char *argv[]) {

  time_point<high_resolution_clock> star, end;
  star = high_resolution_clock::now();

  std::cout << "Hello people" << std::endl;
  vecInt rArray = creatRandomArray(1000);
  for (auto m : rArray) {
    std::cout << m << std::endl;
  }
  end = high_resolution_clock::now();

  int elapsedTime = duration_cast<milliseconds>(end - star).count();
  std::time_t endTime = high_resolution_clock::to_time_t(end);

  cout << "Время завершения выполнения: " << ctime(&endTime)
       << "Время выполнения: " << elapsedTime << " milliseconds" << endl;

  return 0;
}
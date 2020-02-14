#include <iostream> 
#include <string>
#include <vector>
#include <random>
#include <ctime>
using vecInt = std::vector<int>; 

vecInt creatRandomArray(int coutnOfNumber){

vecInt resultSequence(coutnOfNumber);
std::mt19937 gen(std::time(0)); 
//Creat init sequence
vecInt::iterator it = resultSequence.begin();
for(int i; i < coutnOfNumber; i++){
    *it = i; 
    it++; 
}
for(auto m: resultSequence){
    std::cout << m << std::endl; 
}
//Data randomization 

for(int i=0; i < coutnOfNumber-1; i++){ 

std::uniform_int_distribution<>uid(i,coutnOfNumber-1);
std::swap(resultSequence[i], resultSequence[uid(gen)]);

}


return resultSequence; 

}

int main(int argc, char *argv[]){

std::cout << "Hello people" << std::endl;  


    return 0; 

}
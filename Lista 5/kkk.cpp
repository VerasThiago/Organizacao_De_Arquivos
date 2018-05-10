#include <string>
#include <bitset>
#include <iostream>
using namespace std;
int main(){
  string myString = "pica";
  bitset<8> y(std::string("01110111"));
  cout << "teste = " <<  (char)y.to_ulong() << endl;
}
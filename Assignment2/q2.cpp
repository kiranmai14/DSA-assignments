#include <iostream>
#include <cmath>
using namespace std;

int main(){
    // unordered_map<int,int> m;
    // m.insert({1,10});
    double f = 123.45;
    double f3;
    double f2 = std::modf(f, &f3);
    std::cout << "modf() makes " << f3 << " + " << f2 << '\n';
    uint64_t T[8][256];
for (int i = 0; i < 8; i++)
   for (int j = 0; j < 256; j++)
      T[i][j] = getRandomUInt64();
}
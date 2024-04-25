#include <iostream>
#include "prng.h"

double randomDouble(int ndiscard=0) {
    int seed = 13;
    static PRNG gen(seed);
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    if (ndiscard==0) {
        return dis(gen);
    } else {
        gen.discard(ndiscard);
        return -1;
    } 
}

int main()
{
    double x = randomDouble();
    double y = randomDouble();
    randomDouble(2); // skip two
    double z = randomDouble();
    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << z << "\n";
}

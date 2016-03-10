#include <bitset>
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    // Invoke the Java program with the passed arguments.
     bitset<64> black;
     bitset<64> black2;
     black.set(0);
     black2 = black;
     black2.set(1);
     cout << "black1: " << black[0] << " " << black[1] << endl;
     cout << "black2: " << black2[0] << " " << black2[1] << endl;
    return 0;
}

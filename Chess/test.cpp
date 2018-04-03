#include <iostream>
#include <string>
using namespace std;



struct Pos {
    int x;
    int y;
};

int fun(Pos p) {
    return p.x;
}

int main() {
    cout << fun(Pos{2,3}) << endl;
}

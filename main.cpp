#include <iostream>
#include "bloc.h"

using namespace std;

int main() {
    int k;
    bloc b;
    scanf("%d",&k);
    b.set_i(k);
    b.get_i();
    cout << "Hello, World!" << endl;
    return 0;
}
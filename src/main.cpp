
#include <iostream>
#include "calculator.h"

using namespace std;

int main()
{   
    Calculator calculator = Calculator();
    int val = calculator.add(1,2);
    cout << val << endl;
    return 0;
}

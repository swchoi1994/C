/*
This code determines which combination of algeraic eqaution gives the result of 29.

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() 
{
	for (int i = 1; i <= 9; i++) {
	    if (1 + 2 + i + 9 + 9 == 29) cout << "1 + 2 + " << i << " + 9 + 9 = 29" << endl;
	    if (1 + 2 + i + 9 * 9 == 29) cout << "1 + 2 + " << i << " + 9 * 9 = 29" << endl;
	    if (1 + 2 + i * 9 + 9 == 29) cout << "1 + 2 + " << i << " * 9 + 9 = 29" << endl;
	    if (1 + 2 + i * 9 * 9 == 29) cout << "1 + 2 + " << i << " * 9 * 9 = 29" << endl;
	    if (1 + 2 * i + 9 + 9 == 29) cout << "1 + 2 * " << i << " + 9 + 9 = 29" << endl;
	    if (1 + 2 * i * 9 + 9 == 29) cout << "1 + 2 * " << i << " + 9 + 9 = 29" << endl;
	    if (1 + 2 * i * 9 * 9 == 29) cout << "1 + 2 * " << i << " * 9 * 9 = 29" << endl;
	    if (1 + 2 * i + 9 * 9 == 29) cout << "1 + 2 * " << i << " + 9 * 9 = 29" << endl;
	    if (1 * 2 + i + 9 + 9 == 29) cout << "1 * 2 + " << i << " + 9 + 9 = 29" << endl;
	    if (1 * 2 + i + 9 * 9 == 29) cout << "1 * 2 + " << i << " + 9 * 9 = 29" << endl;
	    if (1 * 2 + i * 9 + 9 == 29) cout << "1 * 2 + " << i << " * 9 + 9 = 29" << endl;
	    if (1 * 2 + i * 9 * 9 == 29) cout << "1 * 2 + " << i << " * 9 * 9 = 29" << endl;
	    if (1 * 2 + i * 9 * 9 == 29) cout << "1 * 2 + " << i << " * 9 * 9 = 29" << endl;

}
return 0;
}

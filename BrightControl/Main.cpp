#include "gammasetting.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>


using namespace std;

int main()
{
	CgammaSetting GammaRamp;
	int setVal = 0;
	cout << "                -------------------------------------------" << endl;
	cout << "                          Set Screen Brightness" << endl;
	cout << "                -------------------------------------------" << endl;

	cout << "\n\n[+] press 0 to reduce\n[+] press 1 to increase\n[+] press 2 to set value yourself[Not recommended]" << endl;
	cout << "\n\n\nEnter value: ";
	cin >> setVal;
	
	if (setVal == 0)
		GammaRamp.SetBrightness(NULL, 0);
	else if (setVal==1)
		GammaRamp.SetBrightness(NULL, 128);
	else if (setVal == 2) {
		int amt;
		cout << "\n\n\nEnter amount to set [0-256]: ";
		cin >> amt;
		GammaRamp.SetBrightness(NULL, amt);
	}

	return 0;
}

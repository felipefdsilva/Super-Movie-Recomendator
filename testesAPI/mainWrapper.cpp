#define OK			0

#include <iostream>
#include <string>

#include "perlWrapper.h"

using namespace std;

int main () {
	perlWrapper perlwrapper;

	perlWrapper.runInterpreterWithPerlFile("perlMath.pl");

	cout << "Resultado: " << perlwrapper.getMathResult (5, "multiplyByTwo");
	cout << endl;
	cout << endl;

	cout << "Resultado: " << perlwrapper.getMathResult (4, "divideByTwo");
	cout << endl;
	cout << endl;

	perlwrapper.runInterpreterWithPerlFile ("perlProg.pl");

	cout << "Resultado: " << perlwrapper.getInputFileInfo ("test", "lineCounter");
	cout << endl;
	cout << endl;
	
	cout << "Resultado: " << perlwrapper.getInputFileInfo ("test", "wordCounter");
	cout << endl;

	return OK;
}

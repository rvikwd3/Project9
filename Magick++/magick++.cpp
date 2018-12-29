#include<Magick++.h>
#include<iostream>
#include<string.h>

using namespace std;
using namespace Magick;

int main(int argc, char **argv){
	InitializeMagick(*argv);

	cout << "Initialized Magick++ API" << endl;
	cout << "Enter filename:\t";
	cin >> filename;

	Image image;
	Image synthetic(filename);
	
	try{
		image.read("logo:");

		image.crop(Geometry(100,100,100,100));

		image.write("logo.png");

		cout << "Columns of '2x2.png':\t" << synthetic.columns() << endl;
		cout << "Rows of '2x2.png':\t" << synthetic.rows() << endl;
		cout << "Format of '2x2.png':\t" << synthetic.magick() << endl;

		cout << "Pixel colors:" << endl;
		for(int i=0; i<synthetic.columns(); i++){
			for(int j=0; j<synthetic.rows(); j++){
				cout << "(" << i << ", " << j << "):\t" << "R: " << synthetic.pixelColor(i,j).quantumRed() << "\tG: " << synthetic.pixelColor(i,j).quantumGreen() << "\tB: " << synthetic.pixelColor(i,j).quantumBlue() << endl;
			}
		}
	}
	catch(Exception &error_){
		cout<<"Caught exception: "<< error_.what() << endl;
		return 1;
	}
	
	return 0;
}

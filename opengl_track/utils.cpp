#include "libs.h"

using namespace std;

string read_file(string file_name) {
	string temp = "", source = "";
	ifstream input_file;
	input_file.open(file_name);
	if (input_file.is_open()) {
		while (getline(input_file, temp))
			source += temp + "\n";
	}
	else {
		cout << "Error::main.cpp::Unable to read file " << file_name << endl;
	}
	input_file.close();
	return source;
}

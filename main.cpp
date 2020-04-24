#include<iostream>
#include "lexer.cpp"
#include "parser.cpp"
#include<fstream>
#include<vector>


int main() {

    cout<< "filename: " << endl;
    string infilename;
    cin >> infilename;
    ifstream file;
    file.open(infilename);


    if(file.is_open() == false ) {
			cout << "COULD NOT OPEN " << infilename << endl;
			return 1;
		}

    vector<vector<string>> tokens = lex(file);

    for (int i =0; i<tokens.size(); i++){
        cout << tokens[i][0] <<": " << tokens[i][1] << endl;

    }
    //parse(tokens);
    return 0;
}

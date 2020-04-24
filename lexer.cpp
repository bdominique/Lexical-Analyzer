#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<vector>
using namespace std;

string _scan_string(char delimiter, ifstream& file){
    string output = "";
    char c;
    while (file.peek() != delimiter){
        c = file.get();
        if(c == '\\' && file.peek() == delimiter){
            output += delimiter;
            file.get();
            continue;
        }
        if (file.eof()){
            return "ERROR";
        }
        output += c;
    }
    file.get();
    return output;
}


string _scan(char ch, ifstream& file, int mode){
    string output = "";
    output += ch;
    switch(mode){
    case(1) :
        while (!file.eof() && (isdigit(file.peek()) || file.peek() == '.' )){
            ch = file.get();
            output += ch;
        }
    case(0) :
        while (!file.eof() && (isalnum(file.peek()) || file.peek() == '_')) {
            ch = file.get();
            output += ch;
        }

    }
    return output;
}


vector<vector<string>> lex(ifstream& file){
    char ch;
    vector<vector<string>> tokens;
    vector<string> add_to_output{"",""};
    if(!file.is_open()){
        cout<< "error while trying to open the file" << endl;
        return {{""}};
    }

    char operators[] = "+-*/";
    char specialchars[] = "(){},;=:";
    char doublequote = '"';
    string singlequote = "'";
    string errormsg_string = "ERROR";



    while(!file.eof()){

  NEXT_CH:      ch = file.get();

        if(file.eof()) break;

        //for loop to see if the character we're currently at is a +, -, *, or /
        for (int i = 0; i< 4; i++){
            if(ch == operators[i]){
                add_to_output[0] = "operation";
                add_to_output[1] = ch;
                tokens.push_back(add_to_output);
                goto NEXT_CH;
            }
        }

        //for loop to see if the character we're currently at is one of '{', '}', '(', ')', ',', ';', '=', or ':'
        for (int i = 0; i< 8; i++){
            if(ch == specialchars[i]){
                add_to_output[0] = ch;
                add_to_output[1] = "";
                tokens.push_back(add_to_output);
                goto NEXT_CH;
            }
        }


        //if we've hit a newline in the middle of a line, skip over it
        if(ch == '\\' && file.peek() == 'n'){
            file.get();
            continue;
        }


        //if we've hit whitespace or reached the end of a line or just reached a tab in the middle of a line, just move onto the next character
        if(ch == ' ' || ch == '\n'){
                goto NEXT_CH;
        }


        //if the character we're currently at is a ", run scan_string() to find the entire string.
        if (ch == doublequote){
            string result = _scan_string(ch, file);
            if(result == errormsg_string){
                cout << "ERROR: The end of the file was reached without finding a matching delimiter." << endl;
                return {{""}};
            }
            add_to_output[0] = "string";
            add_to_output[1] = result;
            tokens.push_back(add_to_output);
        }

        //if the character we're currently at is a ', run scan_string() to find the entire string.
        else if (ch == singlequote[0]){
            string result = _scan_string(ch, file);
            if(result == errormsg_string){
                cout << "ERROR: The end of the file was reached without finding a matching delimiter." << endl;
                return{{""}};
            }
            add_to_output[0] = "string";
            add_to_output[1] = result;
            tokens.push_back(add_to_output);
        }

        //if the character we're currently at is a number or a decimal, run _scan() in mode 1 to find the entire number.
        else if (isdigit(ch) || (ch == '.' && isdigit(file.peek()))){
            string result = _scan(ch, file,1);
            //double res = ::atof(result.c_str());
            add_to_output[0] = "number";
            add_to_output[1] = result;
            tokens.push_back(add_to_output);
        }

        //if the character we're currently at is a letter a-z or A-Z, run _scan() in mode 0 to find the entire symbol.
        else if(isalpha(ch) || (ch == '_' && isalnum(file.peek()))){
            string result = _scan(ch, file,0);
            add_to_output[0] = "symbol";
            add_to_output[1] = result;
            tokens.push_back(add_to_output);
        }


        //if we encounter a tab, end the program
        else if (ch == '\t' || (ch == '\\' && file.peek() == 't')){
            cout << "tab characters are not allowed in Cell." << endl;
            return {{""}};
        }

        //if we reach this branch of the if statement that means we have a character that didn't fit any of the categories above, and therefore is invalid.
        else{
            cout << "Unrecognized character: " << ch << "." << endl;
            return {{""}};
        }
    }
    return tokens;
}

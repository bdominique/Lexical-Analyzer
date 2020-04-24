#include<iostream>
#include<vector>

using namespace std;


/*
The Parser class and the parse() function are still under construction.
*/

class Parser{
    private:
    public:
        // constructor and the outline of the functions the guy has. start with the cases for number and build from there.
        string stop_at;
        vector<vector<string>> tokens;
        int max_size;

        //constructor
        Parser(vector<vector<string>> tok, string stop){
            tokens = tok;
            stop_at = stop;
            max_size = tok.size();
        }

        vector<string> peek(int index){
            if(index == this->max_size){

                //End of Tokens, similar to EOF or End of File
                return {"EOT",""};
            }
            if(index > this->max_size){

                //Error message
                return {"ERROR",""};
            }

            return this->tokens[index];
        }

        vector<string> get_token(int index){
            if(index >= this->tokens.size()+1){

                //End of Tokens, similar to EOF or End of File
                return {"EOT",""};
            }

            return this->tokens[index];
        }

        vector<string> next_expression(vector<string> prev, int ind){
            if (this->fail_if_at_end(";",ind) == true) return {""};
            vector<string> type_val = this->get_token(ind);
            string typ = type_val[0];
            string val = type_val[1];
            cout<< type_val[0] << ": " << type_val[1] << endl;

            if(typ == this->stop_at) {return prev;}

            string num_string_sym[] = {"number","string","symbol"};
            if((typ == num_string_sym[0]||typ == num_string_sym[1]||typ == num_string_sym[2]) && prev[2] == ""){
                return this->next_expression({"","",val,""},ind+1);
            }

            else if (typ == "operation"){
                vector<string> nxt = this->next_expression({"","","",""},ind+1);
                return this->next_expression({typ, val, prev[2], nxt[2]},ind+2);

            }

        }

        bool fail_if_at_end(string expected,int ind){
            if (this->peek(ind+1)[0] == "ERROR"){
                cout<< "------" << "ERROR: Hit the end of the file without finding a '" << expected << "' -------" << endl;
                return true;
            }
            return false;
        }
};


vector<vector<string>> parse(vector<vector<string>> tokens){
    Parser parser(tokens, ";");
    vector<vector<string>> output;
    int i = 0;
    cout << i << endl;
    cout << parser.max_size << endl;
    while (true){
        //i is the index of the token stream that we're starting at
        if(output.size() == 0){
            i = 0;
        }
        else {
        i = i + output[output.size()-1].size();
        }
        if(i >= parser.max_size) break;
        vector<string> p = parser.next_expression({"","","",""},i);
        if(p[0] != "") output.push_back(p);
        if (p[0] == "") {cout << "Exiting Without Finishing" << endl; return {{""}};}
    }
    cout<< parser.max_size << " tokens were grouped into " << output.size() << " statements."<< endl;
    return output;

}

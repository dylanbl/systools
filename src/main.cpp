#include "../include/io.hpp"
using namespace std; 

int main(int argc, char **argv) {
    string command, filename, key;
    Input i;  

    // Program needs at least 2 arguments 
    if(argc < 2) {
        cout << "usage: $(command) $(filename)" << endl; 
        return -1; 
    }

    command = argv[1]; 

    /* "sort" will sort files in the given directory by either name or size */
    if(command == "sort") {
        if(argc != 4) {
            cout << "usage: sort -$(key) $(filename)" << endl; 
            return -1;
        }

        key = argv[2]; 
        filename = argv[3]; 

        i.Read(filename, command); 
        i.Sort(key); 
        i.Print(); 
    }
    else if(command == "add") {
        if(argc != 4) {
            cout << "usage: add $(filename1) $(filename2) $(destination)";
        }
        i.Read(filename, command); 
        i.Print(); 
    }
    else {
        cout << "command not valid." << endl; 
        return -1; 
    }

    return 0; 
}

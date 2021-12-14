#include "../include/tools.hpp"
#include "../lib/cxxopts.hpp"
using namespace std; 

int main(int argc, char **argv) {
    string command, filename, flag;
    Tools tools; 

    // Variables for cxxopts library  
    cxxopts::ParseResult result; 
    cxxopts::Options options("systools, library of command line tools"); 

    // Add options to cxxopts
    options.add_options() 
        ("s,size", "sort by size", cxxopts::value<string>()->default_value(""))
        ("n,name", "sort by name", cxxopts::value<string>()->default_value(""))
    ; 

    options.allow_unrecognised_options(); 

    // Program needs at least 2 arguments 
    if(argc < 2) {
        cout << "usage: $(command) -$(flags) $(filename)" << endl; 
        return -1; 
    }

    // Parse with cxxopts 
    result = options.parse(argc, argv); 

    command = argv[1]; 

    try {
        /* "sort" will sort files in the given directory by either name or size */
        if(command == "list") {
            if(argc != 4) {
                cout << "usage: sort -$(key) $(filename)" << endl; 
                return -1;
            }

            if(!(result.count("size")) && !(result.count("name"))) {
                cout << "invalid sort flag." << endl; 
                return -1; 
            }

            flag = (result.count("size")) ? "size" : "name"; 
            filename = result[flag].as<string>(); 
            
            tools.List(filename, flag); 
        }
        /*
        else if(command == "add") {
            if(argc != 4) {
                cout << "usage: add $(filename1) $(filename2) $(destination)";
            }
            tools.i->Read(filename, command); 
            tools.o->Standard_Print(); 
        }
        */
        else {
            cout << "command not valid." << endl; 
            return -1; 
        }
    }
    catch(const string s) {
        cout << s << endl; 
    }

    return 0; 
}
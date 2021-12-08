#include "../include/tools.hpp"
#include "../lib/cxxopts.hpp"
using namespace std; 

int main(int argc, char **argv) {
    string command, filename; 
    Input i; 

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

    /* "sort" will sort files in the given directory by either name or size */
    if(command == "list") {
        if(argc != 4) {
            cout << "usage: sort -$(key) $(filename)" << endl; 
            return -1;
        }

        if(result.count("size")) {
            filename = result["size"].as<string>(); 
            i.Read(filename, command); 
            i.Sort("size"); 
        }
        else if(result.count("name")) {
            filename = result["name"].as<string>(); 
            i.Read(filename, command); 
            i.Sort("name"); 
        }
        else if(result.unmatched().size() > 0) {
            cout << "invalid sort flag." << endl; 
            return -1; 
        }
        else {
            cout << "invalid sort flag." << endl;
            return -1;  
        }
        
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

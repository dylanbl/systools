#include "../include/tools.hpp"
#include <map>
#include <fstream>
using namespace std;  

// Constructor 
Tools::Tools() {

}

// Destructor 
Tools::~Tools() {
    for(size_t i = 0; i < files.size(); i++) {
        delete files[i]; 
    }
}

/* - - - - - - - - - - - - - - Tools public method implementations - - - - - - - - - - - - - - */

// systools list function
void Tools::List(const string &filename, const string &flag) {
    string filetype; 

    filetype = get_filetype(filename);

    if(filetype != "directory") {
        throw (string) "file is not a directory.";
    }

    // Runs 'ls -l' and saves information about each file
    read_directory(filename);

    if(flag == "size") {
        sort_size(); 
    }
    else {
        sort_names(); 
    }
}

/* - - - - - - - - - - - - - - General helper method implementations - - - - - - - - - - - - - - */

// Returns a string holding the path to the systools/txt directory 
string Tools::get_path() const {
    string rv; 

    rv = (string) getenv("HOME");
    rv += "/systools/txt/"; 
    return rv; 
}

// Runs 'file' command to determine type of file 
string Tools::get_filetype(const string &filename) const {
    string temp, linux, path, rv; 
    ifstream input_file; 

    path = get_path();  

    // Pass command to OS and write outupt to filetype.txt 
    linux = "file " + filename + " > " + path + "filetype.txt";
    system(linux.c_str());

    // Read output of 'file' command 
    input_file.open((path + "filetype.txt").c_str()); 
    getline(input_file, temp); 
    input_file.close();

    if(temp == (filename + ": cannot open `" + filename + "' (No such file or directory)")) {
        throw (string) "cannot find file.";
    }

    rv = temp.substr(temp.find(':') + 2);
    return rv; 
}

// Reads a directory and saves information about each file 
void Tools::read_directory(const string &filename) {
    string filetype, size_adjusted, time, permissions, owner; 
    string group, name, size, hard_links, month, day; 
    string temp, linux, path; 
    File_Data* f; 
    ifstream input_file; 
    istringstream ss;

    path = get_path(); 
    path += "file_properties.txt";

    linux = "ls -l " + filename + " > " + path;
    system(linux.c_str()); 

    input_file.open(path);

    getline(input_file, temp);

    // For each file, certain information from its 'ls -l' description is saved in a File_Data class 
    while(getline(input_file, temp)) {
        ss.clear(); 
        ss.str(temp); 
        name.clear(); 
        
        ss >> permissions >> hard_links >> owner >> group >> size >> month >> day >> time;

        while (ss >> temp) {
            name += temp + " ";
            temp.clear(); 
        }
        
        f = new File_Data; 

        f->size = atof(size.c_str()); 
        f->time = time; 
        f->name = name; 

        files.push_back(f);  

        permissions.clear(); 
        hard_links.clear(); 
        owner.clear(); 
        group.clear();
        size.clear(); 
        month.clear();
        day.clear(); 
        time.clear();
    }

    input_file.close(); 
}

/* - - - - - - - - - - - - - - List helper method implementations - - - - - - - - - - - - - - */

// Prints files sorted by size 
void Tools::sort_size() {
    multimap<int, File_Data*> size_name; 
    multimap<int, File_Data*>::const_iterator snit; 
    int size;  

    // Sorts sizes by inserting File_Data* into a map keyed on the file's size 
    for(size_t i = 0; i < files.size(); i++) {
        size = files[i]->size; 
        
        size_name.insert(make_pair(size, files[i])); 
    }

    // Prints files in order  
    for(snit = size_name.begin(); snit != size_name.end(); snit++) {
        cout << snit->second->name << endl;
    }
}

// Prints files sorted by name 
void Tools::sort_names() {
    multimap<string, File_Data*> name_size; 
    multimap<string, File_Data*>::const_iterator nsit; 
    string name; 

    // Sorts names lexographically by inserting File_Data* into a map keyed on the file's name 
    for(size_t i = 0; i < files.size(); i++) {
        name = files[i]->name; 

        // Needed to sort without being case sensitive 
        name[0] = tolower(name[0]);

        name_size.insert(make_pair(name, files[i])); 
    }

    // Prints files in order 
    for(nsit = name_size.begin(); nsit != name_size.end(); nsit++) {
        cout << nsit->first << endl; 
    }
}
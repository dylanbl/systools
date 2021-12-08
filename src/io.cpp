#include "../include/io.hpp"
#include <stdlib.h>
#include <fstream>
#include <cctype>
#include <map>
#include <ctype.h>
using namespace std; 

/* - - - - - - - - - - File_Data implementations - - - - - - - - - - */

int File_Data::Size() {
    return size; 
}

string File_Data::Name() {
    return name; 
}

string File_Data::Filetype() {
    return filetype; 
}

/* - - - - - - - - - - Input publicmethod implementations - - - - - - - - - - */

// Destructor 
Input::~Input() {
    for(size_t i = 0; i < files.size(); i++) {
        delete files[i]; 
    }
}

// Reads information about file(s), information will be stored in files vector when done 
void Input::Read(const string &filename, const string &command) {    
    string filetype, size_adjusted, time, permissions, owner; 
    string group, name, size, hard_links, month, day; 
    string temp, linux, path; 
    ifstream input_file; 
    istringstream ss; 
    const char *home_dir;

    // Set path variable to be sysinfo directory in user's home directory 
    home_dir = getenv("HOME");
    temp = (string) home_dir; 
    path = temp + "/sysinfo/txt/file_properties.txt";  

    // Pass command to OS and write outupt to file_properties.txt 
    linux = "file " + filename + " > " + path; 
    system(linux.c_str());

    /* Open file and read contents into varables that correspond to output of ls -l 
       From these varables, a vector of pointers to File_Data classes is created. This
       vector contains the Input class' information about the files. */

    input_file.open(path.c_str()); 

    while(cin >> temp) {
        temp = temp; 
    }

    if(command == "sort") {
        if(temp == "directory") {
            read_directory(input_file, filename);
        } 
        else {
            cout << "file is not a directory." << endl;
            return; 
        }
    } 
}

// Prints the name of each element in the files vector 
void Input::Print() {
    
    for(size_t i = 0; i < files.size(); i++) {
        cout << files[i]->name << endl;
    }
}

// Calls appropriate sort function on files vector 
void Input::Sort(const string &key) {
    if(key == "-size") {
        sort_size(files); 
    }
    else if(key == "-name") {
        sort_names(files); 
    }
}

/* - - - - - - - - - - Input private helper method implementations - - - - - - - - - - */

void Input::read_directory(ifstream &input_file, const string &filename) {
    string filetype, size_adjusted, time, permissions, owner; 
    string group, name, size, hard_links, month, day; 
    string temp, linux, path; 
    File_Data* f; 
    istringstream ss; 

    if(temp == "ls: " + filename + ": No such file or directory") {
        cout << "file cannot be found." << endl; 
        return; 
    }
    getline(input_file, temp); 

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

        f->permissions = permissions; 
        f->hard_links = atoi(hard_links.c_str()); 
        f->owner = owner; 
        f->group = group; 
        f->size = atof(size.c_str()); 
        f->time = time; 
        f->name = name; 

        files.push_back(f);  
    }

    input_file.close(); 
}

// Sorts files vector by the files' sizes 
void Input::sort_size(vector<File_Data*> &files) {
    multimap<int, File_Data*> size_name; 
    multimap<int, File_Data*>::const_iterator snit; 
    int size, iter;  

    // Sorts sizes by inserting File_Data* into a map keyed on the file's size 
    for(size_t i = 0; i < files.size(); i++) {
        size = files[i]->Size(); 
        
        size_name.insert(make_pair(size, files[i])); 
    }

    // Makes files vector sorted by copying order of map 
    iter = 0; 
    for(snit = size_name.begin(); snit != size_name.end(); snit++) {
        files[iter] = snit->second; 
        iter++; 
    }
}

// Sorts files vector by the files' names 
void Input::sort_names(vector<File_Data*> &files) {
    multimap<string, File_Data*> name_size; 
    multimap<string, File_Data*>::const_iterator nsit; 
    int iter;  
    string name; 

    // Sorts name lexographically by inserting File_Data* into a map keyed on the file's name 
    for(size_t i = 0; i < files.size(); i++) {
        name = files[i]->Name(); 

        // Needed to sort without being case sensitive 
        name[0] = tolower(name[0]);

        name_size.insert(make_pair(name, files[i])); 
    }

    // Makes files vector sorted by copying order of map 
    iter = 0; 
    for(nsit = name_size.begin(); nsit != name_size.end(); nsit++) {
        files[iter] = nsit->second; 
        iter++; 
    }
}
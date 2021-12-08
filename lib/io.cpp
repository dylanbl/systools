#include "io.hpp"
#include <stdlib.h>
#include <fstream>
#include <cctype>
#include <map>
#include <ctype.h>
#include <string>
using namespace std; 

/* - - - - - - - - - - Input publicmethod implementations - - - - - - - - - - */

// Destructor 
Input::~Input() {
    for(size_t i = 0; i < files.size(); i++) {
        delete files[i]; 
    }
}

// Reads information about file(s), information will be stored in files vector when done 
void Input::Read(const string &filename, const string &command) {     
    string temp, linux, path; 
    ifstream input_file; 
    istringstream ss; 
    const char *home_dir;

    // Set path variable to be sysinfo directory in user's home directory 
    home_dir = getenv("HOME");
    temp = (string) home_dir; 
    path = temp + "/systools/txt/";  

    // Pass command to OS and write outupt to filetype.txt 
    linux = "file " + filename + " > " + path + "filetype.txt";
    system(linux.c_str());

    input_file.open((path + "filetype.txt").c_str()); 
    getline(input_file, temp); 
    
    if(command == "list") {
        if(temp == filename + ": directory") {
            linux_command("list", filename, path);
            read_directory(path); 
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

void Input::linux_command(const string &action, const string &filename, const string &path) {
    string linux; 

    // Pass command to OS and write outupt to file_properties.txt 
    if(action == "list") {
        linux = "ls -l " + filename + " > " + path + "file_properties.txt"; 
        system(linux.c_str());
    } 
}

// Places the contents of files in directory into files vector 
void Input::read_directory(const string &path) {
    string filetype, size_adjusted, time, permissions, owner; 
    string group, name, size, hard_links, month, day; 
    string temp, linux; 
    File_Data* f; 
    ifstream input_file; 
    istringstream ss;

    input_file.open(path + "file_properties.txt");

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
#pragma once 
#include <iostream>
#include <vector>
#include <sstream> 

// This class holds data about a particluar file 
class File_Data {
    friend class Input; 
    friend class Output; 

    public: 
        int Size(); 
        std::string Name(); 
        std::string Filetype(); 

    protected: 
        double size;
        int hard_links; 
        std::string filetype;  
        std::string size_adjusted; 
        std::string time; 
        std::string permissions; 
        std::string owner; 
        std::string group; 
        std::string name; 
};

// This class handles input from the user and the output of commands passed to CLI 
class Input {
    friend class output; 
    public:
        ~Input();  
        void Read(const std::string &filename, const std::string &command);  
        void Print(); 
        void Sort(const std::string &key); 

    private:
        std::vector<File_Data*> files;  
        void read_directory(std::ifstream &input_file, const std::string &filename); 
        void sort_size(std::vector<File_Data*> &files);
        void sort_names(std::vector<File_Data*> &files);  
}; 

class Output {
    friend class input; 

}; 
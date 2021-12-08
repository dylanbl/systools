#pragma once 
#include "file_data.hpp"
#include <iostream>
#include <vector>
#include <sstream> 

// This class handles input from the user and the output of commands passed to CLI 
class Input {
    friend class output; 
    public:
        ~Input();   
        void Read(const std::string &filename, const std::string &command);  
        void Print(); 

        /* This is going to the systools classs */ 
        void Sort(const std::string &key); 

    private:
        /* This should be part of the systools class */
        std::vector<File_Data*> files; 

        /* This is going to the systools class */  
        void linux_command(const std::string &action, const std::string &filename, const std::string & path);
        
        /* Keep in Input class. Call systools->get_filetype to determnie if this function should
           be called */
        void read_directory(const std::string &path); 

        /* These are going to systools class */
        void sort_size(std::vector<File_Data*> &files);
        void sort_names(std::vector<File_Data*> &files);  
}; 

class Output {
    friend class input; 

}; 
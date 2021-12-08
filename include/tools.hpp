#pragma once 

#include "../lib/io.hpp"
#include <iostream>
#include <vector>
#include <sstream>

class tools {
    public: 
        tools(); 
        ~tools(); 

        void List(const std::string &key); 
        void Add(const std::string &file1, const std::string &file2, const std::string &dest);

        std::vector<std::string> available_tools; 

    private: 
        // This holds information about the file(s) involved in a particular call 
        std::vector<File_Data*> files; 

        // Executes a certain command line instruction based on the action 
        void linux_command(const std::string &action, const std::string &filename, const std::string &path);

        // Returns the a file's particular type 
        std::string get_filetype(); 

        /* Helper functions for List tool */
        void sort(const std::string &key); 
        void sort_size(std::vector<File_Data*> &files);
        void sort_names(std::vector<File_Data*> &files); 


}; 
#pragma once 

#include "../lib/file_data.hpp"
#include <iostream>
#include <vector>
#include <sstream>

class Tools { 
    public: 
        Tools(); 
        ~Tools(); 

        void List(const std::string &filename, const std::string &flag); 
        void Add(const std::string &file1, const std::string &file2, const std::string &dest);

        std::vector<std::string> available_tools; 

    private: 
        // This holds information about the file(s) involved in a particular call 
        std::vector<File_Data*> files; 

        std::string get_filetype(const std::string &filename) const; 
        std::string get_path() const; 
        void read_directory(const std::string &filename);

        /* Helper functions for List tool */
        void sort_size();
        void sort_names(); 
}; 
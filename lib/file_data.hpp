#include <string>

// This class holds data about a particluar file 
class File_Data {
    friend class Tools; 

    protected: 
        double size; 
        std::string filetype;
        std::string size_adjusted; 
        std::string time; 
        std::string name; 
};
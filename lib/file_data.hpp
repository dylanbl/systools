#include <string>

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
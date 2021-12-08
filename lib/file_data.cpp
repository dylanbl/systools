#include "file_data.hpp"
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
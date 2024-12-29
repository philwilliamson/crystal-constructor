#ifndef GET_FILE_CONTENTS_H
#define GET_FILE_CONTENTS_H

#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

namespace crystal_constructor{ namespace utils {

std::string get_file_contents(const char* filename);

}} // parsing file contents into a string

#endif
//
// Created by Neilf on 11/25/2023.
//

#ifndef COLLEGEROI__CSVCOMPILER_H
#define COLLEGEROI__CSVCOMPILER_H
#include "../College/College.h"
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

class CSVCompiler {
private:
public:
    static std::string filename;
    static void SaveToCSV(size_t, const std::shared_ptr<College>&);
    static std::unique_ptr<std::unordered_map<size_t,  std::shared_ptr<College>>> LoadFromCSV();
};


#endif //COLLEGEROI__CSVCOMPILER_H

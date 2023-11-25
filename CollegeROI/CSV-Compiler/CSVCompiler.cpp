//
// Created by Neilf on 11/25/2023.
//

#include "CSVCompiler.h"
#include <iostream>

std::string CSVCompiler::filename = "colleges.csv";

void CSVCompiler::SaveToCSV(size_t key, const std::shared_ptr<College>& value) {
    std::fstream fout;
    fout.open(CSVCompiler::filename, std::ios::out | std::ios::app );

    fout << key << ","
         << value->GetCost() << ","
         << value->GetReturn() << ","
         << value->GetName() << "\n";
}

std::unique_ptr<std::unordered_map<size_t, std::shared_ptr<College>>> CSVCompiler::LoadFromCSV() {
    std::fstream fin;
    fin.open(CSVCompiler::filename, std::ios::in);
    std::unordered_map<size_t, std::shared_ptr<College>> map;

    std::string line;

    while (getline (fin, line)) {
        std::stringstream  ss(line);
        std::string keyStr;
        std::getline(ss, keyStr, ',');
        size_t key = std::stoull(keyStr);
        std::string values [3];
        for (auto & value : values) {
            std::getline(ss, value, ',');
        }

        std::shared_ptr<College> college =
                std::make_shared<College>(College(std::stoi(values[0]), std::stoi(values[1]), values[2]));
        map[key] = college;
    }
    return std::make_unique<std::unordered_map<size_t, std::shared_ptr<College>>>(map);
}





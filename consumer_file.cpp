#include "consumer_file.h"
#include <iostream>
#include <fstream>

void homework::ConsumerFile::consume(homework::Commands& cmd){
    std::string name(cmd.get_time());
    name+=".log";
    std::ofstream out_file(name, std::ofstream::out);
    std::cout << "Write file:" << name << std::endl;
    auto it = cmd.begin();
    if(it!=cmd.end()) {
        out_file << "bulk: ";
        out_file << *it;
        ++it;
    }
    for(;it!=cmd.end();++it)
        out_file  << ", " << *it;
    out_file << std::endl;

    out_file.close();
}
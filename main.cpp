#include "lib.h"
#include "consumer_out.h"
#include "consumer_file.h"
#include "producer.h"
#include <algorithm>
#include <string>
#include <cctype>

bool isPositiveInteger(const std::string&& s)
{
    return !s.empty() && 
           (std::count_if(s.begin(), s.end(), [](auto a){return (a>='0'&&a<='9');}) == (long)s.size());
}

int main(int argc, char *argv[]){
 
    if(argc>1)
    if(isPositiveInteger(std::string(argv[1]))){
        homework::Producer producer(atoi(argv[1]));
        homework::ConsumerOut consumer_out(std::cout);
        homework::ConsumerFile consumer_file;

        producer.add_customer(&consumer_file);
        producer.add_customer(&consumer_out);


        std::string cmd;
        while(std::cin >> cmd)
            producer.produce(cmd);
        producer.flush();
    }

    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
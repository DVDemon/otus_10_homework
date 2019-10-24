#include "lib.h"
#include "consumer_out.h"
#include "consumer_file.h"
#include "producer.h"
#include "topic.h"
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
        homework::Topic        topic;
        homework::Producer     producer(atoi(argv[1]),topic);
        homework::ConsumerOut  consumer_out(topic,std::cout);
        homework::ConsumerFile consumer_file(topic);


        consumer_out.process();
        consumer_file.process();

        std::string cmd;
        while(std::cin >> cmd)
            producer.produce(cmd);
        producer.flush();

        consumer_out.stop();
        consumer_file.stop();
    }

    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
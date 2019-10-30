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
        homework::ConsumerOut  consumer_out(topic,1,std::cout);
        homework::ConsumerFile consumer_file1(topic,2),consumer_file2(topic,2);


        consumer_out.process();
        consumer_file1.process();
        consumer_file2.process();

        std::string cmd;
        while(std::cin >> cmd)
            producer.produce(cmd);
        producer.flush();

        std::cout << "main поток - " << producer.get_counter_line() << " строк, " << producer.get_counter_block() << " блок, " << producer.get_counter_command() << " комманд" << std::endl;
        std::cout << "log поток - " << consumer_out.get_counter_block() << " блок, " << consumer_out.get_counter_command() << " комманд" << std::endl;
        std::cout << "file1 поток - " << consumer_file1.get_counter_block() << " блок, " << consumer_file1.get_counter_command() << " комманд" << std::endl;
        std::cout << "file2 поток - " << consumer_file2.get_counter_block() << " блок, " << consumer_file2.get_counter_command() << " комманд" << std::endl;
    }

    UNUSED(argc);
    UNUSED(argv);
    return 0;
}
#include "producer.h"
#include "commands.h"

homework::Producer::Producer(size_t size,Topic &t) : bulk_size(size), topic(t), counter_block{0}, counter_command{0},counter_line{0}{
}

void homework::Producer::produce(std::string str){
        counter_line++;
        if(str.find('{')!= std::string::npos) {
            if(state.braces==0){
                notify_bulk();
            }
            state.braces++;
        }
        else
        if(str.find('}')!= std::string::npos) state.braces--;
        else{
            if(state.count==0) next_command.set_current_time();
            state.count ++;
            next_command << str; 
        }

        if(state.count>=bulk_size){
            if(state.braces==0)
                notify_bulk();
        }
    
}

void homework::Producer::notify_bulk(){
    if(state.braces==0)
    if(!next_command.empty()){
        counter_block++; 
        counter_command+=next_command.size();
        topic.publish_command(next_command);
        next_command.clear();
        state.count = 0;      
    }

}

void homework::Producer::flush(){
    notify_bulk();

    while(!topic.empty()){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

size_t homework::Producer::get_counter_block(){
    return counter_block;
}

size_t homework::Producer::get_counter_command(){
    return counter_command;
}

size_t homework::Producer::get_counter_line(){
    return counter_line;
}
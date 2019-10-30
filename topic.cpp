#include "topic.h"
#include <exception>
#include <iostream>

void homework::Topic::publish_command(const homework::Commands& cmds){
    
    std::lock_guard<std::mutex> lock(guard);
    for( std::pair<size_t,std::deque<const Commands>&> queue : topic){
        queue.second.push_back(cmds);
    }
}

void homework::Topic::subscribe_consumer(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    std::cout << "subscribe:" << id <<std::endl;
    if(topic.find(id)==std::end(topic)){
        std::cout << "add queue:" << id <<std::endl;
        topic[id] = std::deque<const Commands>();
    }
}

bool homework::Topic::empty(){
    for(auto q:topic)
     if(!q.second.empty()) return false;
    return true;
}

bool homework::Topic::empty(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<const Commands>& queue = topic[id];
        return queue.empty();
    } 
    throw std::logic_error("Нет такого подписчика");
}

bool homework::Topic::top_and_pop(size_t id, homework::Commands& result){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<const Commands>& queue = topic[id];
        if(!queue.empty()){
            result = queue[0];
            queue.pop_front();
            return true;
        } else {
            return false;
        }
    } 
    throw std::logic_error("Нет такого подписчика");
}
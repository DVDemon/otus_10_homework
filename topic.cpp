#include "topic.h"
#include <exception>
#include <iostream>

void homework::Topic::publish_command(homework::Commands& cmds){
    
    std::lock_guard<std::mutex> lock(guard);

    for(auto it=topic.begin(); it!=topic.end();++it){
        it->second.push_back(cmds);
    }
}

void homework::Topic::subscribe_consumer(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)==std::end(topic)){
        topic[id] = std::deque<Commands>();
    }
}

bool homework::Topic::empty() const {
    std::lock_guard<std::mutex> lock(guard);
    for(auto q:topic)
     if(!q.second.empty()) return false;
    return true;
}

bool homework::Topic::empty(size_t id) const{
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        const std::deque<Commands>& queue = topic.find(id)->second;
        return queue.empty();
    } 
    throw std::logic_error("Нет такого подписчика");
}

bool homework::Topic::top_and_pop(size_t id, homework::Commands& result){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<Commands>& queue = topic[id];
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
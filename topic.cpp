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
    if(topic.find(id)==std::end(topic)){
        topic[id] = std::deque<const Commands>();
    }
}

bool homework::Topic::empty(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<const Commands>& queue = topic[id];
        return queue.empty();
    } 
    throw std::logic_error("Нет такого подписчика");
}

homework::Commands homework::Topic::top(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<const Commands>& queue = topic[id];
        if(!queue.empty()){
            return queue[0];
        }
        throw std::logic_error("Достигнут конец очереди");
    } 
    throw std::logic_error("Нет такого подписчика");
}

void homework::Topic::pop(size_t id){
    std::lock_guard<std::mutex> lock(guard);
    if(topic.find(id)!=std::end(topic)){
        std::deque<const Commands>& queue = topic[id];
        if(!queue.empty()){
            return queue.pop_front();
        }
        throw std::logic_error("Достигнут конец очереди");
    } 
    throw std::logic_error("Нет такого подписчика");
}
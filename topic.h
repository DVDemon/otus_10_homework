#ifndef TOPIC_H
#define TOPIC_H

#include "commands.h"

#include <map>
#include <deque>
#include <mutex>

namespace homework{
    class Topic{
        public:
            void        publish_command(const Commands& cmds);
            void        subscribe_consumer(size_t id);
            Commands    top(size_t id);
            void        pop(size_t id);
            bool        empty(size_t id);
        private:
            std::mutex guard;
            std::map<size_t,std::deque<const Commands>> topic;

    };
}
#endif
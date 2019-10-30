#include "consumer.h"


homework::Consumer::Consumer(homework::Topic &t,size_t id) : thread_group_id(id),
                                                             counter_block{0},
                                                             counter_command{0},
                                                             topic(t) 
{
    topic.subscribe_consumer(thread_group_id);
    running.store(false);
}

size_t homework::Consumer::get_id() const
{
    return thread_group_id;
}

void homework::Consumer::stop()
{
    if (running.load())
    {
        running.store(false);
        result.wait();
    }
}

void homework::Consumer::process()
{
    if (running.load())
        return; // already running

    running.store(true);
    result = std::async(std::launch::async, [&]() {
        while (running.load())
        {
            if (!topic.empty(get_id()))
            {
                try
                {

                    Commands cmd;
                    if(topic.top_and_pop(get_id(),cmd)){
                        counter_block ++;
                        counter_command += cmd.size();
                        consume(cmd);
                    }
                }
                catch (std::logic_error &err)
                {
                    std::cout << err.what() << std::endl;
                }
            }
        }
    });
}

size_t    homework::Consumer::get_counter_block(){
    return counter_block;
}

size_t    homework::Consumer::get_counter_command(){
    return counter_command;
}

homework::Consumer::~Consumer()
{
    stop();
}
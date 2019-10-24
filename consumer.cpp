#include "consumer.h"

size_t homework::Consumer::global_consumer_id = 0;

homework::Consumer::Consumer(homework::Topic &t) : topic(t)
{
    consumer_id = ++global_consumer_id;
    topic.subscribe_consumer(consumer_id);
    running.store(false);
}

size_t homework::Consumer::get_id() const
{
    return consumer_id;
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
                    Commands cmd = topic.top(get_id());
                    consume(cmd);
                    topic.pop(get_id());
                }
                catch (std::logic_error &err)
                {
                    std::cout << err.what() << std::endl;
                }
            }
        }
    });
}

homework::Consumer::~Consumer()
{
    stop();
}
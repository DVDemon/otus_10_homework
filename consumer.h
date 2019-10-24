#ifndef CONSUMER
#define CONSUMER

#include <atomic>
#include "commands.h"
#include "topic.h"
#include <future>

namespace homework{
    /**
     * Интерфейс для наблюдателей, которые будут получть блок команд и куда-нибудь его писать.
     */
    class Consumer{
        public:
                Consumer(Topic &t);
                void      process();
                void      stop();
                virtual ~Consumer();
        protected:
                size_t consumer_id;
                virtual void consume(Commands &) = 0;
                size_t get_id() const;
        private:
                static  size_t  global_consumer_id;
                Topic&          topic;
                std::atomic_bool   running;
                std::future<void>  result;
    };
}
#endif
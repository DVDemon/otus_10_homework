#ifndef CONSUMER_FILE
#define CONSUMER_FILE

#include "consumer.h"
namespace homework{
    /**
     * Наблюдатель для записи блоков команд в файл.
     */
    class ConsumerFile : public Consumer{
            public:
                ConsumerFile(Topic &t);
                void consume(Commands &) override;   
    };
}
#endif
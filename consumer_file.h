#ifndef CONSUMER_FILE
#define CONSUMER_FILE

#include "consumer.h"
#include <utility>
namespace homework{

    /**
     * Синхронизатор имен файлов
     */

    struct FileNameSynchronizer{
            static std::string get_unique_file_name(const std::string &time);
    };
    /**
     * Наблюдатель для записи блоков команд в файл.
     */
    class ConsumerFile : public Consumer{
            public:
                ConsumerFile(Topic &t, size_t id);
                void consume(Commands &) override;   
    };
}
#endif
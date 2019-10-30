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
                /**
                 * В конструкторе запоминаем ссылку на Topic и задаем "группу подписки"
                 */
                Consumer(Topic &t,size_t id);

                /**
                 * Запуск обработки команд
                 */
                void      process();

                /**
                 * Остановка обработчика команд
                 */

                void      stop();

                /**
                 * Информация о внутренних счетчиках: количество прочитанных блоков
                 */
                size_t    get_counter_block();

                /**
                 * Информация о внутренних счетчиках: количество обработанных команд
                 */
                size_t    get_counter_command();

                /**
                 * В деструкторе останавливаем обработку
                 */
                virtual ~Consumer();
        protected:

                /**
                 * Группа подписки
                 */
                size_t          thread_group_id;

                /**
                 * Метод-обработчик команд, который будет переопределяться в наследниках
                 */
                virtual void    consume(Commands &) = 0;

                /**
                 * Акцессор для номера группы подписки
                 */
                size_t          get_id() const;

                /**
                 * Счетчик числа обработанных блоков
                 */
                size_t          counter_block;

                /**
                 * Счетчик числа обработанных команд
                 */
                size_t          counter_command;
        private:
                /**
                 * Ссылка на topic
                 */
                Topic&          topic;

                /**
                 * Индикатор того что идет обработка
                 */
                std::atomic_bool   running;

                /**
                 * Future для синхронизации остановки вычислений
                 */
                std::future<void>  result;
    };
}
#endif
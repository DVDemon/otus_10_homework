#ifndef PRODUCER
#define PRODUCER

#include <vector>
#include <memory>
#include <string>

#include "lib.h"
#include "consumer.h"
#include "topic.h"

namespace homework{

    /**
     * Класс для обработки команд и их группировки в блоки.
     */
    class Producer{
        private:
            /**
             * Текущее состояние обработки. Нам интересна глубина вложенности скобок и количество команд в блоке.
             */
            struct State{
                int braces{0};
                size_t count{0};
             };
            //Текущее состояние обработки команд
            State    state;
            // Максимальное количество команд в блоке
            size_t   bulk_size;
            // Текущий блок команд
            Commands next_command;
            // Ссылки на topic
            Topic    &topic;
            // Метод для уведомления наблюдателей
            void notify_bulk();

            // Счетчик количества блоков
            size_t counter_block;
            // Счетчик количества команд
            size_t counter_command;
            // Счетчик строк
            size_t counter_line;
        public:
            Producer(size_t size,Topic &t);
            
            // Обработать еще одну команду
            void produce(std::string str);
            // Принудительно дослать все команды в буффере и дожидается обработки (страшная вещь)
            void flush();

            // возвращаем счетчик количества обработанных блоков
            size_t get_counter_block();

            // возвращаем счетчик количества обработанных команд
            size_t get_counter_command();

            // возвращаем счетчик количества обработанных строк
            size_t get_counter_line();

    };
} 

#endif
#ifndef TOPIC_H
#define TOPIC_H

#include "commands.h"

#include <map>
#include <deque>
#include <mutex>

namespace homework{
    /**
     * Класс для ведения подписки на команды. Реализует абстракцию topic - т.е. подписки нескольких получателей 
     * на очередь. Для каждой группы подписки делается отдельная очередь команд. При публикации команды она добавляется
     * во все группы подписки.
     */
    class Topic{
        public:

            /**
             * Публикация команды в topic
             */
            void        publish_command(Commands& cmds);

            /**
             * Создание группы подписки
             */
            void        subscribe_consumer(size_t id);

            /**
             * Чтение из очереди по идентификатору группы подписки
             */
            bool        top_and_pop(size_t id,Commands & result);

            /**
             * Проверка на пустоту конкретной группы подписки по идентификатору
             */
            bool        empty(size_t id) const;

            /**
             * Проверка на пустоту всего топика
             */
            bool        empty() const;
        private:
            /**
             * mutex для синхронизации для доступа к topic
             */ 
            mutable std::mutex guard;

            /**
             * хранилище команд
             */
            std::map<size_t,std::deque<Commands>> topic;

    };
}
#endif
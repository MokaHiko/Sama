#pragma once

#include "NetCommon.h"
#include "NetMessage.h"
#include "TSQueue.h"

namespace yoyo
{
    namespace net
    {
        template<typename T> 
        class Connection : public std::enable_shared_from_this<Connection<T>>
        {
        public:
            Connection(asio::io_context& context)
                :m_context(context), m_socket(context)
            {
            };

            virtual ~Connection() 
            {
            };
        public:
            bool ConnectToServer()
            {
                return false;
            };

            void Disconnect()
            {
                if(!IsConnected())
                {
                }
            };

            bool IsConnected()
            {
                return false;
            }
        public:
            bool Send(const Message<T>& msg)
            {
            }
        protected:
            asio::ip::udp::socket m_socket;
            asio::io_context& m_context;   

            // Queue of messages to send to remote   
            TSQueue<Message<T>> out_messages;

            // Queue of messages sent from the remote of this connection.
            // Owned by either client/server
            TSQueue<OwnedMessage<T>>& in_messages;
        };
    };
};

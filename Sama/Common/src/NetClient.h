#pragma once

#include "NetCommon.h"
#include "NetConnection.h"
#include "NetMessage.h"
#include "TSQueue.h"

namespace yoyo
{
    namespace net
    {
        template<typename T>
        class IClient
        {
        public:
            IClient()
                :m_socket(m_context)
            {

            }

            virtual ~IClient()
            {
                if(!IsConnected())
                {
                    Disconnect();
                }
            }
        public:
            // Connect to the server via host and port
            bool Connect(const std::String& host, const uint16_t port)
            {
                return false;
            }

            void Disconnect()
            {
            }

            bool IsConnected()
            {
                return false;
            }

            TSQueue<OwnedMessages<T>>& Incoming()
            {
                return m_owned_messages; 
            }
        protected:
            asio::io_context m_context;

            // Used to connect to the server then handed to a connection to manage
            asio::ip::tcp_socket m_socket;

            // The thread the asio context will run on
            std::thread m_thread_context;

            // Single connection object that handles the data transfer
            Connection<T> m_connection;
        private:
            // Queue of messages from the server
            TSQueue<OwnedMessages<T>> m_owned_messages;
        };
    }
}

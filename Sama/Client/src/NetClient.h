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
            bool Connect(const std::string& host, const uint16_t port)
            {
                try
                {
                    // Create connection 
                    m_connection = std::make_unique<Connection<T>>(m_context);

                    // Create address
                    asio::ip::udp::resolver resolver(m_context);
                    m_endpoints = resolver.resolve(host , std::to_string(port));

                    // m_connection->ConnectToServer(m_endpoints);

                    // m_thread_context = std::thread([this](){m_context.run();})
                }
                catch(std::exception& e)
                {
                    std::cerr << "Client exception: " << e.what() << std::endl;
                    return false;
                }   

                return true;
            }

            void Disconnect()
            {
                if(IsConnected())
                {
                    m_connection->Disconnect();
                }

                m_context.stop();

                if(m_thread_context.joinable())
                {
                    m_thread_context.join();
                }

                m_connection.release();
            }

            bool IsConnected()
            {
                if(!m_connection)
                {
                    return false;
                }

                return m_connection->IsConnected();
            }

            TSQueue<OwnedMessage<T>>& Incoming()
            {
                return m_owned_messages; 
            }
        protected:
            asio::io_context m_context;

            // Used to connect to the server then handed to a connection to manage
            asio::ip::udp::socket m_socket;

            // The thread the asio context will run on
            std::thread m_thread_context;

            // Single connection object that handles the data transfer
            std::unique_ptr<Connection<T>> m_connection;

            asio::ip::udp::resolver::results_type::endpoint_type m_endpoints;
        private:
            // Queue of messages from the server
            TSQueue<OwnedMessage<T>> m_owned_messages;
        };
    }
}

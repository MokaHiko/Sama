#pragma once

#include "NetCommon.h"

namespace yoyo
{
    namespace net
    {
        template<typename T>
        struct MessageHeader
        {
            // User defined ID Type
            T id {};

            // size of message body
            uint32_t size = 0;
        };

        template<typename T>
        struct Message
        {
        public:
            MessageHeader<T> header;
            std::vector<uint8_t> body;

            // Returns the size of the message header and body in bytes
            size_t Size() const
            {
                return sizeof(MessageHeader<T>) + body.size();
            }

            friend std::ostream& operator<<(std::ostream& os, const Message<T>& msg)
            {
                std::cout << "ID" << int(msg.header.id) << "Size:" << msg.header.size << std::endl;
            }

            template<typename DataType>
            friend Message<T>& operator<<(Message<T>& msg, const DataType& in_data)
            {
                // Check if data can be networked
                static_assert(std::is_standard_layout<DataType>::value, "Data is too complexed to be pushed to message!");

                size_t new_size = msg.header.size + sizeof(DataType);
                if(msg.header.size < new_size)
                {
                    msg.body.resize(new_size);
                };

                memcpy(msg.body.data() + msg.header.size, &in_data, sizeof(DataType));
                msg.header.size = new_size; 

                return msg;
            }

            template<typename DataType>
            friend Message<T>& operator>>(Message<T>& msg, DataType& out_data)
            {
                // Check if data can be networked
                static_assert(std::is_standard_layout<DataType>::value, "Data is too complexed to be read from message!");

                size_t new_size = msg.header.size - sizeof(DataType);

                memcpy(&out_data, msg.body.data() + new_size, sizeof(DataType));
                msg.header.size = new_size; 

                // Resize vector
                msg.body.shrink_to_fit();

                return msg;
            }
        };

        template<typename T>
        class Connection; 

        template<typename T>
        struct OwnedMessage
        {
            Connection<T> remote;
            Message<T> message;
        };
    };
};
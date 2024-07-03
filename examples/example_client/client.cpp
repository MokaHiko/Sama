#include "NetClient.h"

enum class MessageType
{
    Uknown,
    Ping
};

class SampleClient : public yoyo::net::IClient<MessageType>
{

};

int main()
{
    SampleClient my_client {};
    return 0;
}


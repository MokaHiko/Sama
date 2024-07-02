#include <gtest/gtest.h>

#include <NetCommon.h>
#include <TSQueue.h>

TEST(SomeTest, BasicAssertions)
{
    EXPECT_EQ(10, 10);
}

namespace yoyo
{
    namespace net
    {
        TEST(MessageStreamTest, BasicAssertions)
        {
            enum class CustomMessageEnum : uint8_t
            {
                Uknown,
                Ping,

                Max,
            };

            MessageHeader<CustomMessageEnum> msg_header;
            msg_header.id = CustomMessageEnum::Ping;

            // Simple Types
            {
                Message<CustomMessageEnum> msg;

                int in_a = 10;
                char in_b = '@';
                char in_c[10] = "012345679";

                size_t total_size = sizeof(in_a) + sizeof(in_b) + sizeof(in_c);

                msg << in_a << in_b << in_c;

                // Expected equal to all data pushed
                EXPECT_EQ(msg.header.size, total_size);

                int out_a;
                char out_b;
                char out_c[10] = {0};

                msg >> out_c;
                EXPECT_TRUE(strcmp(in_c, out_c) == 0);
                EXPECT_EQ(msg.header.size, total_size - sizeof(in_c));

                msg >> out_b;
                EXPECT_EQ(in_b, out_b);
                EXPECT_EQ(msg.header.size, total_size - (sizeof(in_c) + sizeof(in_b)));

                msg >> out_a;
                EXPECT_EQ(in_a, out_a);

                // Expected 0 after all data popped
                EXPECT_EQ(msg.header.size, 0);
            }

            // Custom/Mixed Types
            {
                struct SomeType
                {
                    int x, y, z;
                    char name[16];
                };

                Message<CustomMessageEnum> msg;

                SomeType in_data = {};
                in_data.x = 11;
                in_data.y = 12;
                in_data.z = 13;

                for (size_t i = 0; i < sizeof(in_data.name); i++)
                {
                    in_data.name[i] = i;
                }

                msg << in_data;

                EXPECT_EQ(msg.header.size, sizeof(SomeType));

                SomeType out_data = {};
                msg >> out_data;

                EXPECT_EQ(in_data.x, out_data.x);
                EXPECT_EQ(in_data.y, out_data.y);
                EXPECT_EQ(in_data.z, out_data.z);
                EXPECT_TRUE(strcmp(in_data.name, out_data.name) == 0);

                EXPECT_EQ(msg.header.size, 0);
            }
        }

        TEST(MessageQueueTest, BasicAssertions)
        {
            enum class CustomMessageEnum : uint8_t
            {
                Uknown,
                Ping,

                Max,
            };

            MessageHeader<CustomMessageEnum> msg_header;
            msg_header.id = CustomMessageEnum::Ping;

            TSQueue<CustomMessageEnum> msg_queue;
        }
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
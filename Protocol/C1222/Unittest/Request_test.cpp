#include <gtest/gtest.h>
#include <iostream>

#include "../C1222_Request.h"
#include "../C1222_EPSEM.h"
#include "../C1222_ACSE.h"

uint8_t data[] = "\x60\x29\xA2\x05\x80\x03\x7B\xC1\x75\
\xA6\x04\x80\x02\x7B\x04\xA8\x03\x02\x01\x07\
\xBE\x15\x28\x13\x81\x11\x80\x0F\x50\x00\x02\
\x55\x53\x45\x52\x20\x4E\x41\x4D\x45\x20\x00\x3C";

uint8_t data2[] = "\x60\x22\xa2\x04\x80\x02\x7b\x04\
\xa4\x03\xa6\x05\x80\x03\x7b\xc1\x75\xa8\x03\x02\x01\x07\
\xbe\x09\x28\x07\x81\x05\x80\x03\x00\x00\x3c";

class Request_Build : public ::testing::Test {

};

class Request_Parse : public ::testing::Test {

};

TEST_F(Request_Build, Test_Read)
{

}

TEST_F(Request_Build, Test_Write)
{

}

TEST_F(Request_Build, Test_Logon)
{

}

TEST_F(Request_Build, Test_LogOff)
{

}

TEST_F(Request_Build, Test_Id)
{

}

TEST_F(Request_Build, Test_Wait)
{

}

/** PARSE **/
TEST_F(Request_Parse, Test_Read)
{

}

TEST_F(Request_Parse, Test_Write)
{

}

TEST_F(Request_Parse, Test_Logon)
{

}

TEST_F(Request_Parse, Test_LogOff)
{

}

TEST_F(Request_Parse, Test_Wait)
{

}


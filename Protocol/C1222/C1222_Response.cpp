/* ======================================================================== *
 *                                                                          *
 *                        C1222 Response Implementation                     *  
 *                                                                          *
 * ======================================================================== */

#include "C1222_Response.h"
#include <stdlib.h>
#include <string.h>


C1222_Response::C1222_Response()
{
    buildsize = 0;
    raw_data = NULL;
    response_num = 0;
}

C1222_Response::~C1222_Response()
{
    if(raw_data != NULL)
        delete raw_data;
}

uint8_t *
C1222_Response::build(void)
{
    return raw_data;
}

uint8_t
C1222_Response::get_response_num()
{
    return response_num;
}

long
C1222_Response::get_build_size()
{
    return buildsize;
}

void
C1222_Response::parse(void * data, uint8_t req)
{

}

/**
 * General purpose of response class 
 *
 * Write/Security/Logoff/Terminate/Disconnect
 * Wait/Deregistration/
 *
 *
 */
C1222_Response_General::C1222_Response_General(uint8_t res)
{
    response_num = res;
}

uint8_t *
C1222_Response_General::build()
{
    raw_data = new uint8_t[1];
    raw_data[0] = response_num;

    return raw_data;
}


/**
 * Identify Response
 * 
 * @param res Response isss or bsy or err or ok with parameters
 * @param std represent standard type of device (uint8_t)
 *              0x00 : ANSI C12.18
 *              0x01 : Reserve
 *              0x02 : ANSI C12.21
 *              0x03 : ANSI C12.22
 *              0x04 - 0xFF : Reserve
 * @param ver a byte representation of standard version left of decimal pts 
 * @param rev a byte representation of standard version right of decimal pts
 */
void
C1222_Response_Ident::C1222_Response_Ident(uint8_t res, uint8_t std,
                                           uint8_t ver, uint8_t rev)
{
    response_num = res;
    this->std = std;
    this->ver = ver;
    this->rev = rev;
}

uint8_t *
C1222_Response_Ident::build()
{
    if(response_num == RES_OK) {
        raw_data = new uint8_t[4];
        raw_data[0] = RES_OK;
        raw_data[1] = std;
        raw_data[2] = ver;
        raw_data[3] = rev;
    }
    else {
        raw_data = new uint8_t[1];
        raw_data[0] = response_num;
    }

    return raw_data;
}

uint8_t
C1222_Response_Ident::get_std()
{
    return std;
}

uint8_t
C1222_Response_Ident::get_ver()
{
    return ver;
}

uint8_t
C1222_Response_Ident::get_rev()
{
    return rev;
}

/**
 * Read Response 
 * 
 * @param res    response number
 * @param count  length of data
 * @param data   requested read data 
 * @param chksum 2's compl check sum (add all byte values in data) 
 *
 */
C1222_Response_Read::C1222_Response_Read(uint8_t res, 
     unsigned short count,  uint8_t * data, const uint8_t chksum)
{
    request_num = res;
    this->count = count;
    this->data = data;
    this->chksum = chksum;
}

uint8_t *
C1222_Response_Read::build()
{
    return raw_data;
}

uint8_t *
C1222_Response_Read::get_data()
{
    return data;
}

uint8_t
C1222_Response_Read::get_chksum()
{
    return chksum;
}

unsigned short
C1222_Response_Read::get_count()
{
    return count;
}


/**
 * Logon Response
 *
 * @param res       Response state 
 * @param timeout   seconds to be idle before termination (2bytes)
 */
C1222_Response_Logon::C1222_Response_Logon(uint8_t res, 
                                unsigned short timeout)
{
    response_num = res;
    this->timeout = timeout;
}

uint8_t *
C1222_Response_Logon::build()
{
    if(response_num == RES_OK) {
        raw_data = new uint8_t[3];
        raw_data[0] = response_num;
    
        unsigned short temp = timeout >> 8 | timeout << 8;
        memcpy(raw_data + 1, &temp, 2);
    }
    else {
        raw_data = new uint8_t[1];
        raw_data[0] = response_num;
    }

    return raw_data;
}

/**
 * Resolve Response
 *
 * @param res       Response state
 * @param addr_len  address length 
 * @param addr      local address of requested aptitle
 */
void
C1222_Response_Resolve::C1222_Response_Resolve(uint8_t res, 
                            uint8_t addr_len, uint8_t * addr)
{
    response_num = res;
    this->addr_len = addr_len;
    this->addr = addr;
}

uint8_t *
C1222_Response_Resolve::build()
{
    if(response_num == RES_OK) {
        raw_data = new uint8_t[addr_len + 2];
        raw_data[0] = response_num;
        raw_data[1] = addr_len;

        memcpy(raw_data + 2, addr, addr_len);
    }
    else {
        raw_data = new unsigned[1];
        raw_data[0] = response_num;
    }

    return raw_data;
}

uint8_t
C1222_Response_Resolve::get_addrlen()
{
    return addr_len;
}

uint8_t *
C1222_Response_Resolve::get_addr()
{
    return addr;
}


/**
 * Trace  Response
 *
 * @param res       Response state
 * @param ap_titles aptitle of c12.22 relays used to forward this request
 */

C1222_Response_Trace::C1222_Response_Trace(uint8_t res, 
                                    uint8_t ** aptitles)
{
    response_num = res;
    this->aptitles = aptitles;
}

char **
C1222_Response_Trace::get_aptitles()
{
    return aptitles;
}

/**
 * Registration Response
 *
 * @param res       Response state
 * @param ap_title  registred ap title  
 * @param delay     maximum delay in seconds that device should waits
 * @param period    maximum period in seconds allowed to elapse re-reg
 * @param info      Node info about connection type (see Reg. request)
 */
void
C1222_Response_Registration::C1222_Response_Registration(uint8_t res, 
    uint8_t * ap_title, unsigned short delay, long period, uint8_t info)
{
    response_num = res;
    this->ap_title = ap_title;
    this->delay = delay;
    this->period = period;
    this->info = info;
}

uint8_t *
C1222_Response_Registration::build()
{
    element * encoded_ap = 
        ber_uid_encode(ap_title, strlen(ap_title), 0x80);

    raw_data = new uint8_t[encoded_ap.size + 2 + 4 + 1 + 1];

    raw_data[0] = response_num;
    int offset = 1;
    //copy ap element
    memcpy(raw_data + offset, encoded_ap.data, encoded_ap.size);
    offset += encoded_ap.size;

    short temp_delay, temp_period;

    //byte ordering
    temp_delay = delay >> 8 | delay << 8;
    temp_period = (period >> 24) | (period >> 8 & 0xFF00) | 
        ((period & 0xFF00) << 8)| ((period & 0xFF) << 24);

    memcpy(raw_data + offset, &temp_delay, 2);
    offset += 2;

    memcpy(raw_data + offset, &temp_period, 4);
    offset += 4;

    raw_data[offset] = info;

    delete encoded_ap.data;
    delete encoded_ap;

    return raw_data;
}

char *
C1222_Response_Registration::get_aptitle()
{
    return ap_title;
}

long
C1222_Response_Registration::get_period()
{
    return period;
}

uint8_t
C1222_Response_Registration::get_info()
{
    return info;
}

unsigned short
C1222_Response_Registration::get_delay()
{
    return delay;
}

/**
 * parse response data and convert to human readable format
 * 
 * @param data response data
 * @param req request has been submitted
 */
void
C1222_Response::parse_response(void * data, uint8_t req)
{


}


#include "functions.h"
#include <stdio.h>
#include "tee_internal_api.h"

char* convertNumToStr(char* num, uint32_t size) {
    uint32_t i;
    char* buf_str = (char*) TEE_Malloc(2 * size + 1, 0);
    char* buf_ptr = buf_str;
    for (i = 0; i < size; i++)
    {
        buf_ptr += sprintf(buf_ptr, "%02X", (unsigned char)num[i]);
    }
    PRI_INFO("%d", size);
    *(buf_ptr + 1) = '\0';
    return buf_str;
}

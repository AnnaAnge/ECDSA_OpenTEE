#include "tee_logging.h"
#include <stdio.h>
#include "tee_internal_api.h"

char* convertNumToStr(char* num, uint32_t size);

#define PRI_FAIL(str, ...)  OT_LOG1(LOG_DEBUG, "FAIL  : %s : " str "\n",  __func__, ##__VA_ARGS__);
#define PRI_INFO(str, ...)  OT_LOG1(LOG_DEBUG, "INFO  : %s : " str "\n",  __func__, ##__VA_ARGS__);

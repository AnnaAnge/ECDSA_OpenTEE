#include <stdio.h>

/////////////// convertNumToStr /////////////////////////////
char* convertNumToStr(char* anna_x, uint32_t anna_len_x) {
	uint32_t i;
	char* buf_str = (char*) malloc(2 * anna_len_x + 1);    
	char* buf_ptr = buf_str;  
	for (i = 0; i < anna_len_x; i++) {
		buf_ptr += sprintf(buf_ptr, "%02X", (unsigned char)anna_x[i]);
	}
	printf("%d", anna_len_x);
	*(buf_ptr + 1) = '\0';
	return buf_str; 
}//end convertNumToStr function

/*
 * Copyright (c) 2014, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <string.h> /* memset */
#include <stdio.h>
#include <err.h>
#include <tee_client_api.h>
#include <stdlib.h>
#include "client_socket.c"
#include "functions.c"

static const TEEC_UUID uuid = {
    0x12345678, 0x8765, 0x4321, { 'D', 'I', 'G', 'E', 'S', 'T', '8', '7'}
};

/* The TAFs ID implemented in this TA */
#define TEE_ECDSA_SIGN_APP	1
#define TEE_ECDSA_SIGN_APP1	2

int main() 
{
    TEEC_Result res;
    TEEC_Context ctx;
    TEEC_Session sess;
    TEEC_Operation op = {0}; //to allaxa
    char *buffer="12345sffdsdfsdf";  //SDJFHJ
    uint32_t err_origin;

    //** Initialize a context connecting us to the TEE ** 
    res = TEEC_InitializeContext(NULL, &ctx);
    if (res != TEEC_SUCCESS)
        errx(1, "TEEC_InitializeContext failed with code 0x%x", res);

    //** Open a session to the  TA **
    res = TEEC_OpenSession(&ctx, &sess, &uuid, TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
    if (res != TEEC_SUCCESS)
        errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x", res, err_origin);

    // Allocate shared memory space **
//----> TODO prepei na peraso stin metavliti challenge to buffer pou tha ethei apo to server
/*
TEEC_SharedMemory challenge={0};
op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE);

     // Allocate memory for input **
//challenge.buffer;
challenge.size = 256;
challenge.flags = TEEC_MEM_INPUT;
res=TEEC_AllocateSharedMemory(&ctx, &challenge);
memcpy(challenge.buffer, buffer, 256);
// --> 
op.params[0].memref.parent = challenge; 


    // Allocate memory for output challenge**
TEEC_SharedMemory signed_challenge = {0};
signed_challenge.size = 256;
signed_challenge.flags = TEEC_MEM_OUTPUT;
TEEC_AllocateSharedMemory(&ctx, &signed_challenge);
*op.params[1]->memref.parent = &signed_challenge;

    //Allocate memory for output value X **
TEEC_SharedMemory x_ecc = {0};
x_ecc.size = 256;
x_ecc.flags = TEEC_MEM_OUTPUT;
TEEC_AllocateSharedMemory(&ctx, &x_ecc);
op.params[2].memref.parent = x_ecc; //.buffer

    // Allocate memory for output value Y**
TEEC_SharedMemory y_ecc = {0};
y_ecc.size = 256;
y_ecc.flags = TEEC_MEM_OUTPUT;
TEEC_AllocateSharedMemory(&ctx, &y_ecc);
op.params[3].memref.parent = y_ecc;
*/

//---------Allocate memory ----------//

int alloc_shared_memory(TEEC_Context *context,
                   TEEC_SharedMemory *alloc_shm,
                   char* buffer,     		//itan void*
                   uint32_t buffer_size,
                   uint32_t flags,
                   TEEC_Parameter* param)
{
    TEEC_Result ret;
    buffer_size=256;
    alloc_shm->size = buffer_size;

    alloc_shm->flags = flags;
    ret = TEEC_AllocateSharedMemory(context, alloc_shm);
    if (ret != TEE_SUCCESS) {
        //return 1;
	errx(1, "TEEC_AllocateSharedMemory failed with code 0x%x", ret);
    }
/*
    if (buffer != NULL) {
        memcpy(alloc_shm->buffer, buffer, buffer_size);
    }
*/
	if (flags == TEEC_MEM_INPUT){
		memcpy(alloc_shm->buffer, buffer, buffer_size);
}
    param->memref.parent = alloc_shm;
    return 0;
}

TEEC_SharedMemory challenge = {0}, signed_challenge = {0}, x_ecc = {0}, y_ecc = {0};
op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE, TEEC_MEMREF_WHOLE);
 
alloc_shared_memory(&ctx, &challenge, buffer, 256, TEEC_MEM_INPUT, &op.params[0]);  //--TODO buffer?
alloc_shared_memory(&ctx, &signed_challenge, NULL, 256, TEEC_MEM_OUTPUT, &op.params[1]); //--TODO NULL?
alloc_shared_memory(&ctx, &x_ecc, NULL, 256, TEEC_MEM_OUTPUT, &op.params[2]);
alloc_shared_memory(&ctx, &y_ecc, NULL, 256, TEEC_MEM_OUTPUT, &op.params[3]);


//--------------------- Invoke Command ----------------------------------//
		
printf(" \t buffer value here is: %s\n", buffer);
res = TEEC_InvokeCommand(&sess, TEE_ECDSA_SIGN_APP, &op, &err_origin);
if (res != TEEC_SUCCESS)
    errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
char *signedc[op.params[1].memref.size]; //edo fainetai na skaei
//char *signed_buffer_str = {0};
//signed_buffer_str= convertNumToStr((char*)op.params[1].memref.parent->buffer, op.params[1].memref.size);
//int signed_size = 0;
//op.params[1].memref.size =signed_size; 
memcpy(signedc, op.params[1].memref.parent->buffer, op.params[1].memref.size);


char *x_value[op.params[2].memref.size]; //edo fainetai na skaei
memcpy(x_value, op.params[2].memref.parent->buffer, op.params[2].memref.size);


char *y_value[op.params[3].memref.size]; //edo fainetai na skaei
memcpy(y_value, op.params[3].memref.parent->buffer, op.params[3].memref.size);


printf(" \t TA returned signed challenge \n");
printf(" \t op params[1] signed challenge output here is: %s\n", convertNumToStr((char*)op.params[1].memref.parent->buffer, op.params[1].memref.size));
printf(" \t op params[1] signed challenge output here is: %s\n", op.params[1].memref.parent);
printf(" \t op params[2] public key X output here is: %s\n", convertNumToStr((char*)op.params[2].memref.parent->buffer, op.params[2].memref.size));	
printf(" \t op params[2] public key x value output here is: %s\n", *x_value);
printf(" \t op params[3] public key Y output here is: %s\n", convertNumToStr((char*)op.params[3].memref.parent->buffer, op.params[3].memref.size)); 		
printf(" \t op params[2] public key y value output here is: %s\n", *y_value);
printf(" \t Releasing shared out memory..\n");

TEEC_ReleaseSharedMemory(&challenge);
TEEC_ReleaseSharedMemory(&signed_challenge);
TEEC_ReleaseSharedMemory(&x_ecc);
TEEC_ReleaseSharedMemory(&y_ecc);
 ////////////////////////////////////////////////////////////////////////////////       
    
    TEEC_CloseSession(&sess);
    TEEC_FinalizeContext(&ctx);


    return 1;
}// end main



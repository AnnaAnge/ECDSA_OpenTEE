/*****************************************************************************
** Copyright (C) 2013 Secure Systems Group.                                 **
** Copyright (C) 2015 Intel Corporation.				    **
**                                                                          **
** Licensed under the Apache License, Version 2.0 (the "License");          **
** you may not use this file except in compliance with the License.         **
** You may obtain a copy of the License at                                  **
**                                                                          **
**      http://www.apache.org/licenses/LICENSE-2.0                          **
**                                                                          **
** Unless required by applicable law or agreed to in writing, software      **
** distributed under the License is distributed on an "AS IS" BASIS,        **
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. **
** See the License for the specific language governing permissions and      **
** limitations under the License.                                           **
*****************************************************************************/
// https://github.com/Open-TEE/tests/blob/master/internal_api/crypto_test.c 
/* Extreme simply smoke tests. */


/* Extreme simply smoke tests. */
#define STR_TRACE_USER_TA "HELLO_WORLD"
//#include "crypto_test.h"
#include "../include/tee_internal_api.h"
#include <stdio.h>
/* Start Open-TEE spesifics. NOT GP Compliant. For debugin sake */
#include "../include/tee_logging.h"
#define PRI_STR(str)	    OT_LOG1(LOG_DEBUG, str);
#define PRI(str, ...)       OT_LOG1(LOG_DEBUG, "%s : " str "\n",  __func__, ##__VA_ARGS__);
#define PRI_OK(str, ...)    OT_LOG1(LOG_DEBUG, " [OK] : %s : " str "\n",  __func__, ##__VA_ARGS__);
#define PRI_YES(str, ...)   OT_LOG1(LOG_DEBUG, " YES? : %s : " str "\n",  __func__, ##__VA_ARGS__);
#define PRI_FAIL(str, ...)  OT_LOG1(LOG_DEBUG, "FAIL  : %s : " str "\n",  __func__, ##__VA_ARGS__);
#define PRI_ABORT(str, ...) OT_LOG1(LOG_DEBUG, "ABORT!: %s : " str "\n",  __func__, ##__VA_ARGS__);
/* End Open-TEE spesifics */

#define SIZE_OF_VEC(vec) (sizeof(vec) - 1)
#define MAX_HASH_OUTPUT_LENGTH 64 /* sha512 */

#define STR_TRACE_USER_TA "HELLO_WORLD"
#include <string.h> /* memset */

#include <tee_internal_api.h>
//#include <tee_internal_api_extensions.h>

#include "tee_internal_api.h" /* TA envrionment */
#include "tee_logging.h" /* OpenTEE logging functions */
//#include "functions.h" //convertNumToStr
#include "functions.c" //convertNumToStr
#include "warp_asym_key.c"
#include "ecdsa_sign.c"

#ifdef TA_PLUGIN
#include "tee_ta_properties.h" /* Setting TA properties */

/* UUID must be unique */
SET_TA_PROPERTIES(
    { 0x12345678, 0x8765, 0x4321, { 'D', 'I', 'G', 'E', 'S', 'T', '8', '7'} }, /* UUID */
        512, /* dataSize */
        255, /* stackSize */
        1, /* singletonInstance */
        1, /* multiSession */
        1) /* instanceKeepAlive */
#endif

#define TEE_ECDSA_SIGN_APP	1
#define TEE_ECDSA_SIGN_APP1	2
/////////////////////// TA_CreateEntryPoint ////////////////////////
TEE_Result TA_CreateEntryPoint(void) {
    return TEE_SUCCESS;
}
/////////////////////// TA_DestroyEntryPoint //////////////////////
void TA_DestroyEntryPoint(void) {
}
/////////////////// TA_OpenSessionEntryPoint //////////////////
TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types,
        TEE_Param params[4], void **sess_ctx) {
    /* Unused parameters */
    (void)&params;
    (void)&param_types;
    (void)&sess_ctx;
    OT_LOG(LOG_ERR, "Opened Session: Received attestation request");
    /* If return value != TEE_SUCCESS the session will not be created. */
    return TEE_SUCCESS;
}
/////////////// TA_CloseSessionEntryPoint //////////////////
void TA_CloseSessionEntryPoint(void *sess_ctx) {
    (void)&sess_ctx; /* Unused parameter */
    OT_LOG(LOG_ERR, "Closed Session: Returning attestation reply");
}
//------------------ TA_Invoke Command Entry Point ------------------//

TEE_Result TA_InvokeCommandEntryPoint(void *sess_ctx, uint32_t cmd_id, uint32_t param_types, TEE_Param params[4]) {
	PRI_OK("Hello to Trust Environment");
	PRI_OK("!!!!!!!!!!Anna you can do this!!!!!!!!!!");
    (void)&sess_ctx; /* Unused parameter */
	switch (cmd_id) {
	case TEE_ECDSA_SIGN_APP: //For ECDSA
		OT_LOG(LOG_ERR, "ECDSA_sig");
		return ECDSA_sig(TEE_ECC_CURVE_NIST_P256, 256, TEE_ALG_ECDSA_P256, param_types, params); //
     	/*   case TEE_ECDSA_SIGN_APP1:
                ECDSA_sig1(TEE_ECC_CURVE_NIST_P256);
                return TEEC_SUCCESS;
	*/	
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	    }
}


#include "../include/tee_internal_api.h"
#include <stdio.h>
#include <string.h> /* memset */

#include <tee_internal_api.h>
#include "tee_internal_api.h" /* TA envrionment */
#include "tee_logging.h" /* OpenTEE logging functions */


///////////////////////////// Wsym asym key ////////////////////////////////////////
static int warp_asym_op(TEE_ObjectHandle key,
			TEE_OperationMode mode,
			uint32_t alg,
			TEE_Attribute *params,
			uint32_t paramCount,
			void *in_chunk,
			uint32_t in_chunk_len,
			void *out_chunk,
			uint32_t *out_chunk_len) {
	TEE_Result ret = TEE_SUCCESS;
	TEE_OperationHandle handle; //= (TEE_OperationHandle)NULL;
	TEE_ObjectInfo info;
	TEE_GetObjectInfo(key, &info);

//Allocate operation
	ret = TEE_AllocateOperation(&handle, alg, mode, info.maxObjectSize);
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Failed to alloc operation handle : 0x%x", ret);
		goto err;
	}
//Operation key
	ret = TEE_SetOperationKey(handle, key);
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Failed to set key : 0x%x", ret);
		goto err;
	}
//Sign
	if (mode == TEE_MODE_SIGN) {
		ret = TEE_AsymmetricSignDigest(handle, params, paramCount, in_chunk, in_chunk_len, out_chunk, out_chunk_len);
		if (ret != TEE_SUCCESS) {
			PRI_FAIL("Sign failed : 0x%x", ret);
			goto err;
		}

	} else {
		goto err;
	}
//Free operation
	TEE_FreeOperation(handle);
	return 0;

	err:
	TEE_FreeOperation(handle);
	return 1;
}



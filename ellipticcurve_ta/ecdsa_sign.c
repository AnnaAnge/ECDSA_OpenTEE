#include "../include/tee_internal_api.h"
#include <stdio.h>
#include <string.h> // memset //

#include <tee_internal_api.h>
#include "tee_internal_api.h" // TA envrionment //
#include "tee_logging.h" // OpenTEE logging functions //

//#include "warp_asym_key.c"

/*static uint32_t ECDSA_sig1(uint32_t curve)
{
        TEE_Result ret;
	TEE_ObjectHandle ecdsa_keypair;
	TEE_Attribute ecdsa_attrs[1]; //DEN KATALABAINW
	//size_t key_size = keysize; //will be set as 256
	//char *dig_msg = "ASKLKlkLKLKaksaSDSKkjknsdjJF";
	
	// Curve 
	ecdsa_attrs[0].attributeID = TEE_ATTR_ECC_CURVE;
	ecdsa_attrs[0].content.value.a = curve;
	ecdsa_attrs[0].content.value.b = 0;

	//Allocate transient object
	ret = TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, 256, &ecdsa_keypair);
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Failed to alloc transient object handle : 0x%x", ret);
		goto err;
	}
	//Generate key
	ret = TEE_GenerateKey(ecdsa_keypair, 256, ecdsa_attrs, 1);
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Generate key failure : 0x%x", ret);
		goto err;
	}
	///Print public keys
	//x
	void * anna_x= TEE_Malloc(32, 0); 
	size_t anna_len_x = 32; //error tou TEE kanonika de xreiazetai to 32
	ret = TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_PUBLIC_VALUE_X, anna_x, &anna_len_x);
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Get X object buffer attr failure : 0x%x", ret);
		goto err;
		}
        PRI_OK("- with public key x size %d value %s", anna_len_x, convertNumToStr(anna_x, anna_len_x));
        //PRI_OK("TEST!!!");
	//y
	void * anna_y= TEE_Malloc(32, 0); 
	size_t anna_len_y = 32; //error tou TEE kanonika de xreiazetai to 32
	ret = TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_PUBLIC_VALUE_Y, anna_y, &anna_len_y);
        if (ret != TEE_SUCCESS) {
			PRI_FAIL("Get Y object buffer attr failure : 0x%x", ret);
			goto err;
		}
        PRI_OK("- with public key y size %d value %s", anna_len_y, convertNumToStr(anna_y, anna_len_y));

        return 0;

        err:
          return 1;
}
*/
/////////////////////////// ECDSA sign //////////////////////////////////
static uint32_t ECDSA_sig(uint32_t curve, uint32_t keysize, uint32_t alg, uint32_t param_types, TEE_Param params[4])
{
	if ((TEE_PARAM_TYPE_GET(param_types, 0) != TEE_PARAM_TYPE_MEMREF_INPUT) || 	//inta || kai ta ekana &&
        (TEE_PARAM_TYPE_GET(param_types, 1) != TEE_PARAM_TYPE_MEMREF_OUTPUT) || 
        (TEE_PARAM_TYPE_GET(param_types, 2) != TEE_PARAM_TYPE_MEMREF_OUTPUT) || 
        (TEE_PARAM_TYPE_GET(param_types, 3) != TEE_PARAM_TYPE_MEMREF_OUTPUT)) {
        	OT_LOG(LOG_ERR, "Bad parameter at index 0: expexted memory input or output");
        	return TEE_ERROR_BAD_PARAMETERS;
    		}

	TEE_Result ret;
	TEE_ObjectHandle ecdsa_keypair = (TEE_ObjectHandle)NULL;  /////
	TEE_Attribute ecdsa_attrs[1];
	size_t key_size = keysize; //will be set as 256

	// Curve 
	ecdsa_attrs[0].attributeID = TEE_ATTR_ECC_CURVE;
	ecdsa_attrs[0].content.value.a = curve;
	ecdsa_attrs[0].content.value.b = 0;

	//Allocate transient object
	ret = TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, key_size, &ecdsa_keypair); //key_size=256
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Failed to alloc transient object handle : 0x%x", ret);
		goto err;
	}
	//Generate key
	ret = TEE_GenerateKey(ecdsa_keypair, key_size, ecdsa_attrs, 1); //key_size=256
	if (ret != TEE_SUCCESS) {
		PRI_FAIL("Generate key failure : 0x%x", ret);
		goto err;
	}
	///Print public keys
	//x
	void * anna_x= TEE_Malloc(32, 0); 
	size_t anna_len_x = 32;
	ret = TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_PUBLIC_VALUE_X, anna_x, &anna_len_x);
	if (ret != TEE_SUCCESS) {
			PRI_FAIL("Get X object buffer attr failure : 0x%x", ret);
			goto err;
		}
        PRI_OK("- with public key x size %d value %s", anna_len_x, convertNumToStr(anna_x, anna_len_x));
	//y
	void * anna_y= TEE_Malloc(32, 0); 
	size_t anna_len_y = 32;
	ret = TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_PUBLIC_VALUE_Y, anna_y, &anna_len_y);
        if (ret != TEE_SUCCESS) {
			PRI_FAIL("Get Y object buffer attr failure : 0x%x", ret);
			goto err;
		}
        PRI_OK("- with public key y size %d value %s", anna_len_y, convertNumToStr(anna_y, anna_len_y));
	/*
		//curve
	void * anna_curve= TEE_Malloc(32, 0); 
	size_t anna_len_curve=32;
	TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_CURVE, anna_curve, &anna_len_curve);
        PRI_OK("- with curve size %d value %s", anna_len_curve, convertNumToStr(anna_curve, anna_len_curve));
	*/	
	//private
	void * private= TEE_Malloc(32, 0); 
	size_t private_len=32;
	TEE_GetObjectBufferAttribute(ecdsa_keypair, TEE_ATTR_ECC_PRIVATE_VALUE, private, &private_len);
        PRI_OK("- with private key size %d value %s", private_len, convertNumToStr(private, private_len));
	
///////it's ok until here
        uint32_t dig_len;	// DIGest is coming from the CA //
	// enough for a p256 sig 
	uint32_t sig_len = 256;
			//void *dig = NULL; //								
			//char *sig = {0};//
	char *sig = TEE_Malloc(sig_len, 0);
			//dig = TEE_Malloc(dig_len, 0);	//
			//sig = TEE_Malloc(sig_len, 0);	//

	char *dig = TEE_Malloc(params[0].memref.size, 0);
	dig_len=params[0].memref.size;
	TEE_MemMove(dig, params[0].memref.buffer, dig_len);					

	//SIGN
	uint32_t ecdsa_alg = alg; // will be set as TEE_ALG_ECDSA_P256
	warp_asym_op(ecdsa_keypair, TEE_MODE_SIGN, ecdsa_alg, ecdsa_attrs, 4, dig, dig_len, sig, &sig_len);   
							////////////TODO check paramsCount =4?

        PRI_OK("---digest is: %d value %s", dig_len, dig);
        PRI_OK("---signature is: %d value %s", sig_len, sig);

	TEE_MemMove(params[1].memref.buffer, sig, sig_len);
	params[1].memref.size=sig_len;					

	uint32_t fn_ret = 0; // OK 
	err:
	TEE_FreeTransientObject(ecdsa_keypair);
	TEE_Free(dig);								//
	TEE_Free(sig);
	TEE_Free(anna_x);
	TEE_Free(anna_y);

	if (fn_ret == 0)
		PRI_OK("--- WITH KEY SIZE %u", keysize);
	return fn_ret;

}//end ECDSA_sign function

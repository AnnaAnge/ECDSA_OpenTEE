# ECDSA_OpenTEE

This project aims to integrate Elliptic Curve Digital Signature Algorithm (ECDSA) in Trust Execution Environment using Open-TEE project and create a scheme that meet some of the requirements of FIDO UAF Authentication procedure. 

We have 3 parties:
1. The server (socket)
2. The client app (socket & TEEClient)
3. The trusted app (TEE)


_The scheme is the following:_

The client application receives a challenge from the server (socket) and forwards it to the trusted application within the TEE to be           signed securely.

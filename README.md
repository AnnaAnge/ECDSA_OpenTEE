# ECDSA_OpenTEE


This project aims to integrate Elliptic Curve Digital Signature Algorithm (ECDSA) in Trust Execution Environment using Open-TEE project and create a scheme that meet some of the requirements of FIDO UAF Authentication procedure. 
_The scheme is the following:_
the client application receives a challenge from the server (socket) and forwards it to the trusted application within the TEE to be           signed securely.

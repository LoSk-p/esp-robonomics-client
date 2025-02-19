#pragma once 

#include <string>

#define PUBLIC_KEY_LENGTH 32
#define PRIVATE_KEY_LENGTH 32
#define ADDRESS_LENGTH 48
#define SR25519_PUBLIC_SIZE 32
#define ROBONOMICS_PREFIX 32
#define VARA_PREFIX 137

// #ifdef __cplusplus
// extern "C" {
// #endif

typedef struct RobonomicsPublicKey { unsigned char bytes[PUBLIC_KEY_LENGTH]; } RobonomicsPublicKey;

typedef struct Address { unsigned char symbols[ADDRESS_LENGTH]; } Address;

static int EncodeBase58(const unsigned char *bytes, int len, unsigned char result[]);
static char* getAddrFromPublicKey(RobonomicsPublicKey &pubKey, uint16_t prefix);
char* getAddrFromPrivateKey(uint8_t *private_key, uint16_t prefix);
RobonomicsPublicKey getPublicKeyFromAddr(const char *addrStr);

// #ifdef __cplusplus
// }
// #endif
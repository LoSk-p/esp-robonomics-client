#pragma once

#include "Call.h"
#include "Extrinsic.h"
#include "BlockchainUtils.h"

#include <Arduino.h>
#include "PayloadParamsUtils.h"

class Robonomics {
private:
    BlockchainUtils blockchainUtils;
    uint8_t publicKey_[KEYS_SIZE];
    uint8_t privateKey_[KEYS_SIZE];
    char ss58Address[SS58_ADDRESS_SIZE + 1];
    bool got_extrinsic_result = false;
    const char* createAndSendExtrinsic(Data call);
    Data createCall();
    Data createPayload(Data call, uint32_t era, uint64_t nonce, uint64_t tip, uint32_t sv, uint32_t tv, std::string gen, std::string block);
    Data createSignature(Data data, uint8_t privateKey[32], uint8_t publicKey[32]);
    Data createSignedExtrinsic(Data signature, Data pubKey, uint32_t era, uint64_t nonce, uint64_t tip, Data call);
    const char* sendExtrinsic(Data extrinsicData, int requestId);
public:
    void setup(String host);
    void disconnectWebsocket();
    void setPrivateKey(uint8_t *privateKey);
    const char* sendDatalogRecord(std::string data);
    const char* sendRWSDatalogRecord(std::string data, const char *owner_address);
    const char* sendCustomCall();
    const char* getSs58Address() const;
};

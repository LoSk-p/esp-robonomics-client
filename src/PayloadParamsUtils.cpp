#include <Arduino.h>
#include "PayloadParamsUtils.h"
#include <string>

JSONVar emptyParamsArray;
JSONVar paramsArray;

uint32_t getEra() {
    return 0;
}

uint64_t getTip() {
    return 0;
}

std::string getGenesisBlockHash(BlockchainUtils *blockchainUtils) {
    // return "525639f713f397dcf839bd022cd821f367ebcf179de7b9253531f8adbe5436d6"; // Vara
    // return "631ccc82a078481584041656af292834e1ae6daab61d2875b4dd0c14bb9b17bc"; // Robonomics
    const char* res = getBlockHash(blockchainUtils, 0);
    std::string res_str(res);
    return res_str;
}

uint32_t getSpecVersion(JSONVar *runtimeInfo) {
    if (runtimeInfo == nullptr) {
        ESP_LOGE("getSpecVersion", "runtimeInfo is NULL");
        return 34; // Return a default value or handle error
    }
    int specVersion_ = (int) (runtimeInfo->operator[]("specVersion"));
    return (uint32_t) specVersion_;
}

uint32_t getTransactionVersion(JSONVar *runtimeInfo) {
    int tx_version_ = (int)(runtimeInfo->operator[]("transactionVersion"));
    return (uint32_t) tx_version_;
}

// Get Nonce

uint64_t getNonce(BlockchainUtils *blockchainUtils, char *ss58Address) {
    paramsArray[0] = ss58Address;
    String message = blockchainUtils->createWebsocketMessage("system_accountNextIndex", paramsArray);
    JSONVar response = blockchainUtils->rpcRequest(message);
    int received_nonce = (int) (response["result"]);
    logMessage("Nonce: %d", received_nonce);
    return (uint64_t) (received_nonce);
}

// Get Block Hash

const char* getBlockHash(BlockchainUtils *blockchainUtils, int block_number) {
    paramsArray[0] = block_number;
    String message = blockchainUtils->createWebsocketMessage("chain_getBlockHash", paramsArray);
    JSONVar response = blockchainUtils->rpcRequest(message);
    const char* genesis_hash = (const char*) response["result"];
    logMessage("Block 0 hash: %s", genesis_hash);
    return strdup(genesis_hash);
}

// Get Runtime Info

void getRuntimeInfo(BlockchainUtils *blockchainUtils, uint32_t *payloadSpecVersion, uint32_t *payloadTransactionVersion) {
    const char* chain_head_local = getChainHead(blockchainUtils);
    const char* parent_block_local = getParentBlockHash(chain_head_local, blockchainUtils);
    getRuntimeInfo(parent_block_local, blockchainUtils, payloadSpecVersion, payloadTransactionVersion);
}

void getRuntimeInfo(const char* parentBlockHash, BlockchainUtils *blockchainUtils, uint32_t *payloadSpecVersion, uint32_t *payloadTransactionVersion) {
    paramsArray[0] = parentBlockHash;
    String message = blockchainUtils->createWebsocketMessage("state_getRuntimeVersion", paramsArray);
    JSONVar response = blockchainUtils->rpcRequest(message);
    int specVersion_ = (int) response["result"]["specVersion"];
    *payloadSpecVersion = (uint32_t) specVersion_;
    int transactionVersion_ = (int) response["result"]["transactionVersion"];
    *payloadTransactionVersion = (uint32_t) transactionVersion_;
}

// Get Chain Head

const char* getChainHead(BlockchainUtils *blockchainUtils) {
    String message = blockchainUtils->createWebsocketMessage("chain_getHead", emptyParamsArray);
    JSONVar response = blockchainUtils->rpcRequest(message);
    const char* chain_head = (const char *) (response["result"]);
    logMessage("Chain head: %s", chain_head);
    return strdup(chain_head);
}

// Get Parent Block Hash

const char* getParentBlockHash(const char* chainHead, BlockchainUtils *blockchainUtils) {
    paramsArray[0] = chainHead;
    String message = blockchainUtils->createWebsocketMessage("chain_getHeader", paramsArray);
    JSONVar response = blockchainUtils->rpcRequest(message);
    const char* parent_block_hash = (const char *) (response["result"]["parentHash"]);
    logMessage("Chain header: %s", parent_block_hash);
    return strdup(parent_block_hash);
}

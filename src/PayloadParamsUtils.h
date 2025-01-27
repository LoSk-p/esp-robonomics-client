#pragma once

#include "JsonUtils.h"
#include "BlockchainUtils.h"

uint32_t getEra();
uint64_t getTip();
std::string getGenesisBlockHash(BlockchainUtils *blockchainUtils);
uint32_t getSpecVersion(JSONVar *runtimeInfo);
uint32_t getTransactionVersion(JSONVar *runtimeInfo);

uint64_t getNonce(BlockchainUtils *blockchainUtils, char *ss58Address);
const char* getBlockHash(BlockchainUtils *blockchainUtils, int block_number);
void getRuntimeInfo(const char* parentBlockHash, BlockchainUtils *blockchainUtils, uint32_t *payloadSpecVersion, uint32_t *payloadTransactionVersion);
void getRuntimeInfo(BlockchainUtils *blockchainUtils, uint32_t *payloadSpecVersion, uint32_t *payloadTransactionVersion);
const char* getChainHead(BlockchainUtils *blockchainUtils);
const char* getParentBlockHash(const char* chainHead, BlockchainUtils *blockchainUtils);


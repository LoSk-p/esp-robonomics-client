cmake_minimum_required(VERSION 3.5)
idf_component_register(SRCS "src/address.cpp"
                       "src/blake/blake2b.cpp"
                       "src/BlockchainUtils.cpp"
                       "src/Call.cpp"
                       "src/Encoder.cpp"
                       "src/Extrinsic.cpp"
                       "src/JsonUtils.cpp"
                       "src/PayloadParamsUtils.cpp"
                       "src/Robonomics.cpp"
                       "src/Utils.cpp"
                       "src/requestUtils/HTTPRequests.cpp"
                       "src/requestUtils/WebsocketRequests.cpp"
                       "src/requestUtils/WebsocketUtils.cpp"
                    INCLUDE_DIRS "src/."
                    REQUIRES "arduino" "Arduino_JSON" "Crypto"
                    )

project(esp-robonomics-client)
// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <TrustWalletCore/TWAnyProto.h>

#include <string>
//#include <iostream>

using namespace std;

/// Helper for Signer input and output protobuf message building and parsing.
class ProtobufHelper {
public:
    // Build an AnySigner SignerInput protobuf message, with the given components.
    static string buildAnySignerInputMsg(uint32_t coinType, string transaction, string privKeyHex);
    // Parse out the output field from an AnySigner SignerOutput protobuf message.
    static bool parseSignedTransactionOutput(TW_Any_Proto_SigningOutput signerOutput, string& out);
};

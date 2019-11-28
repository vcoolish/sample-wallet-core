// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <TrustWalletCore/TWAnyProto.h>

#include <iostream>
#include <vector>

using namespace std;

/// As protobuf is not fully supported from C++, some direct message serialization/parsing is done here.
/// For dertails, see  src/proto/Any.proto  and  src/proto/Any.pb.h .
class ProtobufHelper {
public:
    // Build an AnySigner SignerInput protobuf message, with the given components.
    static vector<uint8_t> buildAnySignerInputMsg(uint8_t coinType, string transaction, string privKeyHex);
    // Parse out the output field from an AnySigner SignerOutput protobuf message.
    static bool parseSignedTransactionOutput(TW_Any_Proto_SigningOutput signerOutput, string& out);
protected:
    static bool appendUInt32(vector<uint8_t>& data, uint32_t n);
    static bool parseUInt32(const vector<uint8_t>& data, int idx, uint32_t& out);
    static void appendString(vector<uint8_t>& data, const string& s);
};

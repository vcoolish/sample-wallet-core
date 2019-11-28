// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "protobuf_helper.h"

#include <TrustWalletCore/TWAnyProto.h>
#include <TrustWalletCore/TWAnySigner.h>
#include <TrustWalletCore/TWString.h>
#include <TrustWalletCore/TWData.h>

#include <iostream>
#include <vector>

using namespace std;

bool ProtobufHelper::appendUInt32(vector<uint8_t>& data, uint32_t n) {
    if (n >= 0x3FFF) {
        cout << "Number too large " << n << endl;
        return false;
    }
    if (n <= 0x7F) {
        // fits on 7 bits
        data.push_back((uint8_t)n);
        return true;
    }
    // 0x0080 -- 0x3FFF: fits on 14 bits
    data.push_back(0x80 | ((uint8_t)(n & 0x7F))); // last 7 bits (0--6), plus first bit 1
    data.push_back(((uint8_t)(n & 0x3F80)) >> 7); // bits 7--13
    return true;
}

bool ProtobufHelper::parseUInt32(const vector<uint8_t>& data, int idx, uint32_t& out) {
    if (data.size() <= idx) {
        // too short
        return false;
    }
    if (data[idx] < 0x80) {
        // 7-bit number
        out = data[idx];
        return true;
    }
    if (data.size() <= idx + 1) {
        // too short
        return false;
    }
    if (data[idx + 1] >= 0x80) {
        // larger than 14 bits, not supported
        return false;
    }
    // 14 bit number
    uint32_t res = (data[idx] & 0x7F);
    res |= (data[idx + 1] << 7);
    out = res;
    return true;
}

void ProtobufHelper::appendString(vector<uint8_t>& data, const string& s) {
    if (!appendUInt32(data, s.length())) {
        cout << "String too long " << s.length() << endl;
        return;
    }
    data.insert(data.end(), s.begin(), s.end());
}

vector<uint8_t> ProtobufHelper::buildAnySignerInputMsg(uint8_t coinType, string transaction, string privKeyHex) {
    vector<uint8_t> msg;
    // coin type
    msg.push_back(0x08);
    msg.push_back(coinType);
    // transaction
    msg.push_back(0x12);
    appendString(msg, transaction);
    // privkey
    msg.push_back(0x1a);
    appendString(msg, privKeyHex);
    return msg;
}

bool ProtobufHelper::parseSignedTransactionOutput(TW_Any_Proto_SigningOutput signerOutput, string& out) {
    // copy to byte vector
    vector<uint8_t> data;
    data.insert(data.end(), TWDataBytes(signerOutput), TWDataBytes(signerOutput) + TWDataSize(signerOutput));
    if (data.size() < 3) {
        cout << "Signed transaction too short!" << endl;
        return false;
    }
    if (data[0] != 0x10 || data[1] != 0x01) {
        cout << "Signed transaction is not Success!" << endl;
        return false;
    }
    if (data[2] != 0x22) {
        cout << "Signed transaction has no output field!" << endl;
        return false;
    }
    uint32_t fieldLen;
    if (!parseUInt32(data, 3, fieldLen)) {
        cout << "Could not parse output field lenght!" << endl;
        return false;
    }
    if (data.size() < 5 + fieldLen) {
        cout << "Signed transaction too short, cannot read full output!" << endl;
        return false;
    }
    string output;
    output.insert(output.end(), data.data() + 5, data.data() + 5 + fieldLen);
    out = output;
    return true;
}

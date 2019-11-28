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

// Note: this include file is internal for TrustWalletCore
#include <proto/Any.pb.h>

#include <iostream>
//#include <vector>

using namespace std;

string ProtobufHelper::buildAnySignerInputMsg(uint32_t coinType, string transaction, string privKeyHex) {
    TW::Any::Proto::SigningInput si;
    si.set_coin_type(coinType);
    si.set_transaction(transaction);
    si.set_private_key(privKeyHex);
    string serialized;
    if (!si.SerializeToString(&serialized)) { return ""; }
    return serialized;
}

bool ProtobufHelper::parseSignedTransactionOutput(TW_Any_Proto_SigningOutput signerOutput, string& out) {
    // copy to byte string
    string outStr;
    outStr.insert(outStr.end(), TWDataBytes(signerOutput), TWDataBytes(signerOutput) + TWDataSize(signerOutput));
    // parse protobuf message
    TW::Any::Proto::SigningOutput so;
    if (!so.ParseFromString(outStr)) {
        cout << "Error parsing SingerOutput protobuf message!" << endl;
        return false;
    }
    if (so.has_error()) {
        cout << "SingerOutput has error! " << so.error().description() << endl;
        return false;
    }
    // OK, get output
    out = so.output();
    return true;
}

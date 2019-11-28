// Copyright © 2017-2019 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "protobuf_helper.h"

#include <TrustWalletCore/TWAnyProto.h>
#include <TrustWalletCore/TWAnySigner.h>
#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWPrivateKey.h>
#include <TrustWalletCore/TWString.h>

#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "Wallet Core Demo, C++" << endl << endl;
    cout << "DISCLAIMER: This is a sample application with demonstration purposes only, do not use it with real addresses, or real transactions, use it at your own risk." << endl;

    // Create a new wallet, with new mnemonic passphrase
    cout << "Creating a new HD wallet ... ";
    TWHDWallet* wallet = TWHDWalletCreate(128, TWStringCreateWithUTF8Bytes(""));
    cout << "done." << endl;
    cout << "Secret menmonic phrase for new wallet: '";
    cout << TWStringUTF8Bytes(TWHDWalletMnemonic(wallet)) << "'." << endl << endl;

    // coin type: we use Ethereum
    const TWCoinType coinType = TWCoinType::TWCoinTypeEthereum;
    cout << "Working with coin: " << 
        TWStringUTF8Bytes(TWCoinTypeConfigurationGetName(coinType)) << " " <<
        TWStringUTF8Bytes(TWCoinTypeConfigurationGetSymbol(coinType)) << endl; 

    // Derive default address.  Done in 2 steps: derive private key, then address from private key
    cout << "Obtaining default address ... "; 
    TWPrivateKey* secretPrivateKey = TWHDWalletGetKeyForCoin(wallet, coinType);
    string address = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKey));
    cout << "'" << address << "'" << endl << endl;

    cout << "RECEIVE funds: send to the address:   " << address << " ." << endl << endl;

    // Steps for sending:
    // 1. put together a send message (contains sender and receiver address, amount, etc.)
    // 2. sign this message
    // 3. broadcast this message to the P2P network -- not done in this sample
    // Note that Signer input and output are represented as protobuf binary messages, for which support is missing in C++.
    // Therefore some direct serialization/parsing is done in ProtocolHelper.
    cout << "SEND funds:" << endl;
    cout << "preparing transaction ... ";
    const string dummyReceiverAddress = "0xC37054b3b48C3317082E7ba872d7753D13da4986";
    string transaction = R"({"chainId":"AQ==","gasPrice":"1pOkAA==","gasLimit":"Ugg=","toAddress":")";
    transaction += dummyReceiverAddress;
    transaction += R"(","amount":"A0i8paFgAA=="})";
    cout << "transaction: " << transaction << endl;
    
    const string secretPrivKeyHex = TWStringUTF8Bytes(TWStringCreateWithHexData(TWPrivateKeyData(secretPrivateKey)));
    vector<uint8_t> signerInput = ProtobufHelper::buildAnySignerInputMsg((uint32_t)coinType, transaction, secretPrivKeyHex);
    cout << "signing transaction ... ";
    TW_Any_Proto_SigningOutput signerOutput = TWAnySignerSign(TWDataCreateWithBytes(signerInput.data(), signerInput.size()));
    cout << "done" << endl;
    // Extract signed output
    string signedTransaction;
    if (!ProtobufHelper::parseSignedTransactionOutput(signerOutput, signedTransaction)) {
        cout << "Could not parse out signed transaction!" << endl;
    }
    else
    {
        cout << "Signed transaction data:  (len " << signedTransaction.length() << ") '" << signedTransaction << "'" << endl;    
    }
    cout << endl;

    cout << "Bye!" << endl;
}

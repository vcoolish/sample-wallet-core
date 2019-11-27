# Sample [TrustWallet](https://www.trustwallet.com) [Wallet-Core](https://github.com/trustwallet/wallet-core) client application in C++

## Prerequisites

You need to download and build WalletCore yourself
(there is no official binary distribution).
Get it from
[GitHub](https://github.com/trustwallet/wallet-core).
The dependencies TrezorCrypto and protobuf are also needed, these are also come with WalletCore.

## Building and Running

Get this sample:

    git clone https://github.com/trustwallet/sample-wallet-core-cpp.git
    cd sample-wallet-core-cpp

Configure and build -- path to the TrustWalletCore build directory is needed:

    cmake . -DWALLET_CORE=../wallet-core
    make

Run it:

    ./sample

## What it Does


# Sample [TrustWallet](https://www.trustwallet.com) [Wallet-Core](https://github.com/trustwallet/wallet-core) client application in C++

## DISCLAIMER

This is a sample application with demonstration purposes only, do not use it with real addresses, or real transactions, use it at your own risk.
 
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

The sample code should be self-documented, but here are some overview explanations:

### Create a new wallet

A brand new wallet, with a new mnemonic passphrase, is created with **HDWallet**.  The mnemonic is retrieved and printed.

### Coin Type

Many APIs are coin-agnostic, and require a coin type as input.
In this sample we use Ethereum, whose value is *TWCoinType::TWCoinTypeEthereum*.

### Derive the Ethereum address

The multi-coin HDWallet implicitly contains addressess for each and every coin.
To obtain our Eth address, we first retrieve the private key, then the address from the private key.
Note that private keys should be always handled with uttermost care!

### Sending Eth

To send Eth from this address, the following steps are needed:

* put together a send transaction (contains sender and receiver address, amount, etc.)
* sign this transaction (using the private key)
* broadcast the transaction to the P2P network (not done in this sample)

TODO

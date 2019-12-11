# Sample [TrustWallet](https://www.trustwallet.com) [Wallet-Core](https://github.com/trustwallet/wallet-core) Applications

## DISCLAIMER

> Thare are sample application with demonstration purposes only,
> do not use them with real addresses, real transactions, or real funds.
> Use it at your own risk.
 
## Prerequisites

You need to download and build WalletCore yourself
(there is no official binary distribution).
Get it from
[GitHub](https://github.com/trustwallet/wallet-core).
The dependencies TrezorCrypto and protobuf are also needed, these are also come with WalletCore.

## Documentation

See the official [Trust Wallet developer documentation here](https://developer.trustwallet.com).

See especially Wallet Core
[Integration Guide](https://developer.trustwallet.com/wallet-core/integration-guide.md),
[Build Instructions](https://developer.trustwallet.com/wallet-core/building.md).

## Building and Running

First of all, get this sample:

```shell
git clone https://github.com/trustwallet/sample-wallet-core.git
cd sample-wallet-core
```

### iOS

Go to the **ios** folder:

```shell
cd sample-wallet-core/ios/cocoapods
```

Install dependencies with [*CocoaPods*](https://cocoapods.org/).  If you don't have CocoaPods, install it by
`gem install cocoapods`.

```shell
pod install
```

* Open the following workspace with Xcode: `ios/cocoapods/WalletCoreExample.xcworkspace` 
* Build and Run

The relevant sample code is in the file `WalletCoreExample/ViewController.swift`.  Output appears in Output window (or stdout).

```
├── Podfile
├── Podfile.lock
├── WalletCoreExample
│   ├── AppDelegate.swift
│   ├── Info.plist
│   ├── ViewController.swift
│   └── WalletCoreExample.entitlements
├── WalletCoreExample.xcodeproj
└── WalletCoreExample.xcworkspace
```

### C++

Go to the **cpp** folder:

```shell
cd sample-wallet-core/cpp
```

Configure and build -- path to the TrustWalletCore build directory is needed:

```shell
cmake . -DWALLET_CORE=../../wallet-core
make
```

Run it:

```shell
./sample
```

The relavant sample code is in the file `cpp/sample.cpp`.

## What it Does

The sample code should be self-documented, but here are some overview explanations:

* Import a wallet
  * Create a wallet by importing an existing recovery phrase (mnemonic), using HDWallet.
* Coin Type
  * In this sample we use Ethereum.
* Derive address
  * Address is derived from the HD wallet.
* Create send transaction
  * put together a send transaction (contains sender and receiver address, amount, etc.)
  * sign this transaction (using the private key)

See the [Integration Guide](https://developer.trustwallet.com/wallet-core/integration-guide.md).


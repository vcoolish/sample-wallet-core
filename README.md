# Sample [TrustWallet](https://www.trustwallet.com) [Wallet-Core](https://github.com/trustwallet/wallet-core) Applications

## Overview

This repository contains a few simple, but complete sample applications, for demostrating usage of the
[Wallet Core](https://github.com/trustwallet/wallet-core) library (part of [Trust Wallet](https://trustwallet.com)).
There are several samples:
* **iOS**
* **C++**

## DISCLAIMER

> Thare are sample application with demonstration purposes only,
> do not use them with real addresses, real transactions, or real funds.
> Use it at your own risk.

## Documentation

See the official [Trust Wallet developer documentation here](https://developer.trustwallet.com).

See especially Wallet Core
[Integration Guide](https://developer.trustwallet.com/wallet-core/integration-guide),
[Build Instructions](https://developer.trustwallet.com/wallet-core/building).

# iOS

## Prerequisites

* [*CocoaPods*](https://cocoapods.org/).  If you don't have it, install it by
`gem install cocoapods`.

## Building and Running

Get this sample, and go to the **ios** folder:

```shell
git clone https://github.com/trustwallet/sample-wallet-core.git
cd sample-wallet-core/ios/cocoapods
```

Install dependencies with CocoaPods:

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

# C++

## Prerequisites

You need to download and build WalletCore yourself
(there is no official binary distribution).
Get it from
[GitHub](https://github.com/trustwallet/wallet-core).
The dependencies TrezorCrypto and protobuf are also needed, these are also come with WalletCore.
You need to [build](https://developer.trustwallet.com/wallet-core/building) them.

## Building and Running

Get this sample, and go to the **cpp** folder:

```shell
git clone https://github.com/trustwallet/sample-wallet-core.git
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

# What it Does

The sample code should be self-documented, but here are some overview explanations:

* Import a wallet
  * Create a wallet by importing an existing recovery phrase (mnemonic), using HDWallet.
* Derive address
  * Address is derived from the HD wallet.
* Create send transaction
  * put together a send transaction (contains sender and receiver address, amount, etc.)
  * sign this transaction (using the private key)

See the [Integration Guide](https://developer.trustwallet.com/wallet-core/integration-guide).

//
//  ViewController.swift
//  WalletCoreExample
//
//  Created by Tao X on 10/29/19.
//  Copyright © 2019 Tao X. All rights reserved.
//

import Cocoa
import TrustWalletCore

class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        let wallet = HDWallet(strength: 128, passphrase: "")
        print(wallet.mnemonic)
        let key = wallet.getKeyForCoin(coin: .ethereum)
        let address = CoinType.ethereum.deriveAddress(privateKey: key)
        print(address)

        let msg = "hello".data(using: .utf8)!
        let sig = key.sign(digest: Hash.keccak256(data: msg), curve: .secp256k1)!
        print(sig.hexString)
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }
}

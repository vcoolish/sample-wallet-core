#include <TrustWalletCore/TWCoinType.h>
#include <TrustWalletCore/TWCoinTypeConfiguration.h>
#include <TrustWalletCore/TWHDWallet.h>
#include <TrustWalletCore/TWPrivateKey.h>
#include <TrustWalletCore/TWString.h>

#include <iostream>

using namespace std;

int main()
{
    cout << "Wallet Core Demo, C++" << endl << endl;;

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

    cout << "Obtaining default address ... "; 
    TWPrivateKey* secretPrivateKey = TWHDWalletGetKeyForCoin(wallet, coinType);
    string address = TWStringUTF8Bytes(TWCoinTypeDeriveAddress(coinType, secretPrivateKey));
    cout << "'" << address << "'" << endl << endl;

    cout << "RECEIVE funds: send to the address:   " << address << " ." << endl << endl;

    cout << "SEND funds:" << endl;
    cout << "  TODO:" << endl;
}

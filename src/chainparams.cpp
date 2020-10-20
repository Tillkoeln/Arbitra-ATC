// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0x23;
        pchMessageStart[2] = 0xe1;
        pchMessageStart[3] = 0x15;
		vAlertPubKey = ParseHex("");
        nDefaultPort = 15500;
        nRPCPort = 16550;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "Erexcoin POS 16 october 2020";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1603201858, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1603201858;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 1280869;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x890add2ab742e009de79cb83e8194e21337163533e5da70f206673bd9f2748b2"));
        assert(genesis.hashMerkleRoot == uint256("0x22271d6b9ed94190645f29a700fa9a649f1e6020cf2823070e12e5c49a0d939c"));

//        vSeeds.push_back(CDNSSeedData("seed1", "185.203.116.62"));
//        vSeeds.push_back(CDNSSeedData("seed2", "185.203.118.42"));
//        vSeeds.push_back(CDNSSeedData("seed3", "185.177.59.218"));
		

        base58Prefixes[PUBKEY_ADDRESS] = {33};
        base58Prefixes[SCRIPT_ADDRESS] = {5};
        base58Prefixes[SECRET_KEY] =     {128};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 2628000; // 5 years
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe4;
        pchMessageStart[1] = 0xe6;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xca;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		vAlertPubKey = ParseHex("");
        nDefaultPort = 15551;
        nRPCPort = 16551;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        /*genesis.nBits  = bnProofOfWorkLimit.GetCompact();*/
		genesis.nBits  = 0x1e0fffff; //504365055 Decimal Number
        genesis.nTime    = 1603201860;
        genesis.nNonce = 4131102;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xdc4495d31a4bb19a0c899f5cd4d2b886722af868ad3ad540e118e631d4b28158"));

        vFixedSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("testseed1", "node IP Here"));

        base58Prefixes[PUBKEY_ADDRESS] = {83};
        base58Prefixes[SCRIPT_ADDRESS] = {196};
        base58Prefixes[SECRET_KEY]     = {239};
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04,0x35,0x83,0x94};

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;




static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;

        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);



    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

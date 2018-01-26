// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (    100, uint256("0xc3d91cb4726610d422f8652a5a7cc21bd42e1b8009c00462081c81316d9abad6"))
        (  10000, uint256("0x7b50ea3b42e613e65ec2aca6797a5780e1c545a617e4a610577fb4b040f0035b"))
        (  30000, uint256("0x43e2fe7c700191ddfabe2cd09dfd3fc9eb6331f3c19e59b3e4a87cfa88cac543"))
        (  50000, uint256("0x6a4f705b7a34de7dc1b6573b3595fde05c7b4303b35ede20a3b945244adc6c70"))
        (  69500, uint256("0x8387b49853928fc67d8b8421fd9214184db590eeecd90a200c9d902d8b42e11f"))
        (  80000, uint256("0xa7d7ac0b4b1f5eb56b50ad0693c47f47863b8df81f17514bcb5e59c0a4074eba"))
        (  91000, uint256("0x3f135e0e06ae032de5437ae2b981e3ab84c7d22310224a6e53c6e6e769e8f8f0"))
        ( 101000, uint256("0xba5948ef9fce38887df24c54366121437d336bd67a4332508248def0032c5d6e"))
        ( 111000, uint256("0xbb9cc6e2d9da343774dc4b49be417731991b90ef53a7fa7eb669cce237223c37"))
        ( 121000, uint256("0x1d286956120cf256bed13bcc1f5fe79a98347c80f2225ded92bbbdfc1147b5f5"))
        ( 136000, uint256("0xb7c7416c40425bc7976c7b6b87734e2fb84855eecd30e3e9673caf8c7f599b5c"))
        ( 153000, uint256("0x9f31abd27721e7eb2b58c0a61a117c324a3a6b8f45c82e8963b1bd14166f6510"))
        ( 161000, uint256("0xf7a9069c705516f60878bf6da9bac02c12d0d8984cb90bce03fe34842ba7eb3d"))
        ( 170000, uint256("0x827d5ce5ed69153deacab9a2d3c35a7b33cdaa397a6a4a540d538b765182f234"))
        ( 181000, uint256("0x69fa48e8b9231f101df79c5b3174feb70bf6da11d88a4ce879a7c9ecb799f46d"))
        ( 191000, uint256("0x80a9ea6b375312c376de880b6958459973a95be1dcbf28db1731452a59ef9750"))
        ( 200000, uint256("0x003a4cb3bf206cfc23b9477e1c433280ae1b3393a21aa858aa322e8402204cd0"))
        ( 220000, uint256("0xbed97c09983d1ee14d5f925c31dc4245b6c9d66af4fdadcf973465cb265b52c3"))
        ( 240000, uint256("0xd4e782aae21f551d4a8d7756eb92dfa2cb23d1ede58162382b3bbced4fbee518"))
        ( 260000, uint256("0xdfaef016341fab642190a6656b6c52efbdb43ce8a590bace86793f3c1b1276be"))
        ( 280000, uint256("0x6b836125e431d3fd31ef55f5fbbdfdadc4d9b98b11db5ee0b7ac8f1f8c3ede32"))
        ( 301000, uint256("0xc557d7363393148a630a3fda46ca380a202fe82fa594c5e57f88fbece755bb05"))
        ( 324000, uint256("0x8f6cb33fd75e327eb1a1d90b13ba2124e077b4cc5240bc7ec8039aee8a345e85"))
        ( 347000, uint256("0xf4bd9894306981ca4c20cdbf0bbd9e9832696701f5b3d3a840d026b893db7337"))
        ( 383000, uint256("0xd902cf21480851c35844b0744ea72c1bc2d9318e87a7de63a5e3e3854331a39c"))
        ( 401000, uint256("0xe43417eb3b583fd28dfbfb38c65763d990b4c370066ac615a08c4c5c3910ebc9"))
        ( 420000, uint256("0x76e0de5adb117e12e85beb264c45e768e47d1720d72a49a24daab57493e07a04"))
        ( 440000, uint256("0xbbc6051554e936d0a18adddb95064b16a001ce164d061fb399f26416ce7860f9"))
        ( 461000, uint256("0xa60d67991b4963efee5b102c281755afde28803b9bc0b647f0cbc2120b35185b"))
        ( 480000, uint256("0xd88e6f5e77a8cb4bcb883168f357a94db31203f1977a15d90b6f6d4c2edebbbb"))
        ( 500000, uint256("0xa2989da9f8e785f7040c2e2dfc0177babbf736cfad9f2b401656fea4c3c7c9db"))
        ( 510000, uint256("0x7646ee1a99843f1e303d85e14c58dbf2bd65b393b273b379de14534743111b72"))
        ( 520000, uint256("0x114f6c2065ad5e668b901dd5ed5e9d302d6153f8e38381fbfd44485d7d499e10"))
        ( 540000, uint256("0xd7480699ff87574bfad0038b8697f9bc4df5f0cba31058a637eefbc94e402761"))
        ( 600000, uint256("0x85ac8dbbba7a870a45740677be5f35114cb3b70f56d1c93cc2aaf415629037e7"))
        ( 700000, uint256("0x450af2f828cdfb29be40d644d39a0858b29fe05b556946db31a7c365cffed705"))
        ( 800001, uint256("0xa6d915a25e905d1329e482aac91228b168de6e6efb3838df16c21c3ac3a82ea2"))
        ( 900000, uint256("0x7854a46edbdc4311006a9fd27ae601bb1ebd22fc5e8d6f1757e15237080a545b"))
        (1000000, uint256("0xec070022a4fe9b450e02edd08c6ed355047bc8e65ef05e881b51c212d7c0fe95"))
        (1010001, uint256("0xa2cb82b4ae04854108b18c502f1b33e18c6f69b9d4407e8aa205a23242cd4daf"))
        (1050000, uint256("0x3369fa16394aa222736793fd3fd50d7f7a34d5b1ff67b344eaba269daab28a68"))
        (1060000, uint256("0x44e3b2bfbfb9eef5ef34df447c9ea4c4912b8a3819c2c56dfd0dc02db8a84347"))
        (1100000, uint256("0x4173031420285636eeecfab94e4e62e3a3cf6e144b97b2cc3622c683e09102f0"))
        (1394462, uint256("0xef308b7f477903acd8f300e6f0684c4888ce28c491fc32c1c469bfba6abf091b"))
        (1400000, uint256("0x4bc57c3a57cc977db9f3bd6a095f51c0c7cc9c30fa8554505fa8f8e33d9f2b80"))
        (1410000, uint256("0x7512574ec717d46a90b8c36fd923ef819fdc298b8e4be57be631519662f0db59"))
        (1573741, uint256("0x6e4dacfd1684e71a178f29f3e9c714d264e6d385f64c31cdbe532b3204ce4e1d"))
        (1574000, uint256("0xcef389868efd7785b977eb86527e8049a2a5ea472a6ed9bfc0741c6d6b39234b"))
        (1579000, uint256("0x12cb8ae28107d99f4ba24465b9abf21f98fe855d9b09449cf5c8ed98120829c1"))
        (1589000, uint256("0x479746c27e323e233e58af6024bb7b9727a26bc0114c26ff537469e6ada105e1"))
        (1600000, uint256("0xf44cbdcb21fc7716947f763ccca5de5b02ffff7f14beafef0a7486067f6777fa"))
        (1650000, uint256("0x70caabb0720c95f67a02eabfde27253eaa8698dc6ea5716631890876b9df421a"))        
        (1700000, uint256("0x691eb62d25a0961e81f1a8427b8c21e01ade5befe4a94be5826f49cfecc070a0"))
        (1750000, uint256("0x8971f1790e58c6de0ea2854872c6ad03752b65567ab8e5c8458ae4a6eb9fb783"))
        (1766666, uint256("0xffb7d30ec4d20cae926af05252dc39dbc433b068a0807a8f0dfa63521caca6f0"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1516769324, // * UNIX timestamp of last checkpoint block
        3066043,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        7200.0      // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (     0, uint256("0xed0457370ddafea96096d4c9f5187efceece8d8ab5558194c7eebb06943c8c8c"))
        (   610, uint256("0x26c53c6df7d16be2596ef3eaf11c7281b05061d76b8b146413d4899e33ff5e3a"))
        (  1400, uint256("0x3fc44fd682e0b5f338ca2dc8df8de9b4a72806906338a8c553b3f63f728e2930"))
        ( 15560, uint256("0x0e9b2f7a43065cdf3b505b72d22520d0d261cc53346f10821c9b8ac88c1733b7"))
        ( 32000, uint256("0x01a7ebef1672ba5d4562d3cde51503f6ad1cdd7af6b8004f3b105220b3e7b9ef"))
        ( 33000, uint256("0x356527f8441aaf6218a89b5d8e7ba737ffa1861cf71d5cbb7ee6aee66144c52e"))
        ( 40000, uint256("0x5333431da95d8417da7572328d487546313709c67f08f4135db7ce99b51655ae"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1454963888,
        41211,
        100
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}

EarthCoin
=============

1.5.3 changes
=============

- New checkpoind added
- Elimination of false positive virus alerts for Windows wallet
- New stable nodes IP hardcoded
- Build for Mac OSX released

1.5.2 changes
=============

- All block extracted by attackers were marked as invalid
- Prevention for a larg blockchain reorganization and time-travel attack
- New checkpoints added
- Permanent nodes IP hardcoded, no need for addnodes in the config file

1.5.1 changes
=============

- A hard fork to stop mining monopoly
- Change default port numbers to disconnect attackers

1.3.4 changes
=============

- Update Mainnet checkpoints up to block 1,410,000
- Refresh pnSeed node list

1.3.3 changes
=============

- Update Mainnet checkpoints to post-halving block 540,000
- Update checkpoints as of February 07, 2015 (Block 520,000)

1.3.2 changes
=============

- Update checkpoints as of October 05, 2014 (Block 347,000)

1.3.1 changes
=============

- Upgrade to openssl-1.0.1h for CVE-2014-0224

1.3.0 changes
=============
- Forked off Litecoin Release 0.8.7.1
  - Includes lots of bugfixes compared to 0.6 based release
  - Upgrade to openssl-1.0.1g for CVE-2014-0160
  - Upgrade qt, miniupnpc, zlib, libpng, qrencode
  - Transaction malleability mitigation
  - Coin Control Feature
- Checkpoints up to block 191,000 (May 18, 2014)
- Enable QR code generation
- Setup a working testnet
- Add alert keys to enable network alerts
- Add DNS seed nodes as well as permanent nodes
- Add IP addresses of reliable nodes to source code
- Make true release builds:
  - installer for windows releases
  - DMG for Mac releases
  - 32-bit and 64-bit binaries for linux releases
- Fix several inconsistency in the old client

Litecoin
=============

0.8.7.1 changes
=============
- Mac and Windows Official Gitian Builds: upgrade to openssl-1.0.1g for CVE-2014-0160
                   Linux was not vulnerable with Lucid openssl-0.9.8k
                   Older versions were only vulnerable with rarely used RPC SSL
- If you build from source, be sure that your openssl is patched for CVE-2014-0160.
- Upgrade openssl, qt, miniupnpc, zlib, libpng, qrencode
- Many bug fixes from Bitcoin 0.8.7rc stable branch
    including transaction malleability mitigation backports from 0.9
- Add testnet checkpoints
- Add new testnet seed

0.8.6.2 changes
=============

- Windows only: Fixes issue where network connectivity can fail.

- Cleanup of SSE2 scrypt detection.

- Minor fixes:
  - s/Bitcoin/EarthCoin/ in the Coin Control example
  - Fix custom build on MacOS X 10.9
  - Fix QT5 custom build
  - Update Debian build instructions
  - Update Homebrew build 

0.8.6.1 changes
=============

- Coin Control - experts only GUI selection of inputs before you send a transaction

- Disable Wallet - reduces memory requirements, helpful for miner or relay nodes

- 20x reduction in default mintxfee.

- Up to 50% faster PoW validation, faster sync and reindexing.

- Peers older than protocol version 70002 are disconnected.  0.8.3.7 is the oldest compatible client.

- Internal miner added back to EarthCoin.  setgenerate now works, although it is generally a bad idea as it is significantly slower than external CPU miners.

- New RPC commands: getbestblockhash and verifychain

- Improve fairness of the high priority transaction space per block

- OSX block chain database corruption fixes
  - Update leveldb to 1.13
  - Use fcntl with `F_FULLSYNC` instead of fsync on OSX
  - Use native Darwin memory barriers
  - Replace use of mmap in leveldb for improved reliability (only on OSX)

- Fix nodes forwarding transactions with empty vins and getting banned

- Network code performance and robustness improvements

- Additional debug.log logging for diagnosis of network problems, log timestamps by default

- Fix rare GUI crash on send

0.8.5.1 changes
===============

Workaround negative version numbers serialization bug.

Fix out-of-bounds check (EarthCoin currently does not use this codepath, but we apply this
patch just to match Bitcoin 0.8.5.)

0.8.4.1 changes
===============

CVE-2013-5700 Bloom: filter crash issue - EarthCoin 0.8.3.7 disabled bloom by default so was 
unaffected by this issue, but we include their patches anyway just in case folks want to 
enable bloomfilter=1.

CVE-2013-4165: RPC password timing guess vulnerability

CVE-2013-4627: Better fix for the fill-memory-with-orphaned-tx attack

Fix multi-block reorg transaction resurrection.

Fix non-standard disconnected transactions causing mempool orphans.  This bug could cause 
nodes running with the -debug flag to crash, although it was lot less likely on EarthCoin 
as we disabled IsDust() in 0.8.3.x.

Mac OSX: use 'FD_FULLSYNC' with LevelDB, which will (hopefully!) prevent the database 
corruption issues have experienced on OSX.

Add height parameter to getnetworkhashps.

Fix Norwegian and Swedish translations.

Minor efficiency improvement in block peer request handling.


0.8.3.7 changes
===============

Fix CVE-2013-4627 denial of service, a memory exhaustion attack that could crash low-memory nodes.

Fix a regression that caused excessive writing of the peers.dat file.

Add option for bloom filtering.

Fix Hebrew translation.

Argentum integration/staging tree
========================================

[Website](http://www.argentum.io)

Copyright (c) 2009-2015 Bitcoin Core Developers

Copyright (c) 2013-2017 Argentum Developers


What is Argentum?
-------------------

Argentum is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. Argentum uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Argentum is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately usable, binary version of
the Argentum software, see http://www.argentum.io/

License
-------

Argentum is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Building
--------

See files in the [doc](doc) directory for generic build instructions for Windows,
OSX and Unix. Basic requirements:

* GCC and binuntils
* Git
* Boost C++ libraries
* Berkeley DB - Should be version 5.1.29, newer versions are known to work but not guaranteed
* libssl (part of openssl)
* [miniupnpc](http://miniupnp.free.fr/) for optional UPNP support

Requirements to build the GUI:

* QT4 or QT5 development libraries
* protobuf development libraries
* libqrencode development libraries

A common question is how to build from Ubuntu, instructions follow:

1. sudo add-apt-repository ppa:bitcoin/bitcoin -y
2. sudo apt-get update
3. sudo apt-get install build-essential curl git libminiupnpc-dev libssl-dev m4 -y
4. sudo apt-get install libprotoc-dev libprotobuf-dev -y
5. sudo apt-get install libtool automake autoconf make pkg-config -y
6. sudo apt-get install libpng-dev -y
7. sudo apt-get install libqrencode-dev -y
8. sudo apt-get install libqt5-dev -y
9. sudo apt-get install libboost-all-dev -y
10. sudo apt-get install libcurl4-openssl-dev -y
11. git clone git://github.com/argentumproject/argentum.git
12. cd argentum
13. See /doc/build_unix.md to build Berkeley DB 5.1.29
14. ./autogen.sh
15. ./configure --enable-hardening --disable-tests --disable-upnp-default
16. make
Other Build Notes:

If you are compiling yourself, please configure with something like this:
```
CFLAGS="-O2 -fPIC" CPPFLAGS="-O2 -fPIC" ./configure
```
otherwise you'll probably get some errors later on. Additionally, if your CPU supports SSE2, and most modern CPU's do, use this:
```
CFLAGS="-O2 -fPIC -DUSE_SSE2" CPPFLAGS="-O2 -fPIC -DUSE_SSE2" ./configure
```
That will enable the SSE2 version of the Scrypt algorithm. This may reduce the CPU load when syncing the blockchain.


Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging message are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play argentum" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regest mode.

**DEBUG_LOCKORDER**

Argentum is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of what locks
are held, and adds warning to the debug.log file if inconsistencies are detected.

## Argentum Version 3.11.2
- Update the code base to Bitcoin version 11.2
- Hard fork for coinbase maturity at Block 2,422,000. New coinbase maturiy will be 100 confirmations
- Up to date Gitian build scripts and setup guide
- BIP65 Soft Fork when ~>78% of nodes have upgraded
- Minimum protocol version is 1050000

## General
- Scrypt & SHA256D
- AUXPoW (Merged Mining)

## Blocks
- Max Block size 10mb
- 45 Second block time
- 3 Argentums per block

## Currency Creation
- 64 million Argentums will be created

## Security
- Mined blocks mature after 100 confirms (Hard Fork, Block #2,420,000)
- Argentum is a fast currency, but it does not compromise the safety of the blockchain in the process

## Mining Settings
Use this to set the algorithm to SHA256D for mining (add to argentum.conf)  

algo=sha256d

## Add nodes to argentum.conf
addnode=144.76.71.141
addnode=149.210.234.234
addnode=157.161.128.63
addnode=167.160.36.126
addnode=184.164.129.202
addnode=217.175.119.125
addnode=23.152.0.149
addnode=24.247.103.100
addnode=34.208.13.90
addnode=66.56.61.161
addnode=72.13.188.130
addnode=74.66.86.127
addnode=82.155.132.130
addnode=85.236.188.28
addnode=92.3.32.28
addnode=92.3.34.76
addnode=92.3.40.194
addnode=92.3.45.249
addnode=92.3.46.51
addnode=95.218.175.59
addnode=95.218.215.95

## Bootstrap
https://electrum-arg.org/bootstrap.dat  
sha256 checksum 37020ed0abe02d7bf97a9dde7de0419d278f88866ff9d67419492d2be0dd32db

https://electrum-arg.org/bootstrap.zip  

November 1, 2017
Block 2,723,638

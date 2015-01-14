CLHCO
=====

Tools for the LHC Olympics (LHCO) data files analyses using C++. If you want to use Haskell, see [lhco-tools](https://github.com/cbpark/lhco-tools).

## Usage

You'll need [cmake](http://www.cmake.org) in order to build and install.

```shell
git clone git@github.com:cbpark/CLHCO.git
cd CLHEF && mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/some/where ..
make
make install
```

Note that it would be installed in `/usr/local` unless you specify the installation path via `-DCMAKE_INSTALL_PREFIX`.

## References

- [How to Read LHC Olympics Data Files](http://madgraph.phys.ucl.ac.be/Manual/lhco.html).
- [LHC Olympics Wiki](http://www.jthaler.net/olympicswiki/doku.php).
- [PGS 4 and the LHC Olympics](http://online.kitp.ucsb.edu/online/lhco_c06/conway/).

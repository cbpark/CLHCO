# CLHCO

**DEPRECATED** Use [colevent](https://github.com/cbpark/colevent).

Tools for the LHC Olympics (LHCO) data analyses using C++. If you want to use Haskell, see [lhco-tools](https://github.com/cbpark/lhco-tools).

## Installation

```shell
./configure
make
make install
```
If ROOT is not located in the system path, it can be set by `./configure --with-rootsys=path/of/root`.

### Prerequisite

- C++ compiler supporting C++11 features ([Clang](http://clang.llvm.org/cxx_status.html) >= 3.3, [GCC](https://gcc.gnu.org/projects/cxx-status.html) >= 4.8.1),
- (optional) [ROOT](https://root.cern.ch/).

## Usage

See [`src/test_parse.cc`](src/test_parse.cc) and [`src/test_render.cc`](src/test_render.cc) for the example usage.

## References

- [How to Read LHC Olympics Data Files](http://madgraph.phys.ucl.ac.be/Manual/lhco.html).
- [LHC Olympics Wiki](http://www.jthaler.net/olympicswiki/doku.php).
- [PGS 4 and the LHC Olympics](http://online.kitp.ucsb.edu/online/lhco_c06/conway/).

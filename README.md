# libSpikes

A Spiking Neural Network framework.

This library was written using cygwin/minGW. It also supports MSVC but external libraries are required.

## Instillation

> I would highly recommend using `Jetbrains CLion` IDE.

External libraries required:

1. Boost 1.64+ - http://www.boost.org/
2. Eigen 3.3+ - http://eigen.tuxfamily.org
3. `dirent.h` for MSVC - https://github.com/tronkko/dirent

Setting up the libraries:

1. Clone the repository
```
git clone https://github.com/akshaybabloo/libSpikes.git
```
2. open `libSpikes` and create two folders - `libs` and `winLibs` (only if you are using MSVC)
3. Copy Boost and Eigen folders to `libs` and `dirent.h` to `winLibs`

CLion should be able to index the libraries.

## Example

Coming soon.

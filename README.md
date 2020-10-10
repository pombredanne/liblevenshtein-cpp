# liblevenshtein

## C++

### A library for generating Finite State Transducers based on Levenshtein Automata.

#### Building and Installation

```shell
git clone https://github.com/universal-automata/liblevenshtein-cpp.git
cd liblevenshtein-cpp
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
```

#### Testing

#### Dependencies
1. [Google Test](https://github.com/google/googletest)
2. [RapidCheck](https://github.com/emil-e/rapidcheck)

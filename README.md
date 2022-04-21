# confTainter

## Dependency
```
llvm-10.0.0
```

## Build
```
cd tainter
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++-10 -DCMAKE_C_COMPILER=/usr/bin/clang-10 -DLLVM_DIR=/usr/lib/llvm-10/cmake . 
make
```

## Usage
```
cd test/demo
../../tainter test.bc test-var.txt
```
## Check results
```
cat test-records.dat
```

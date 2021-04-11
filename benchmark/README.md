#Benchmark

Code in this dir is for benchmarking parts of the solver program.

---

##Setting up

This code uses google benchmark, to setup follow these steps:

```sh
git clone git@github.com:google/benchmark.git
git clone git@github.com:google/googletest.git benchmark/googletest
cd benchmark
cmake -E make_directory "build"
cmake -E chdir "build" cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build "build" --config Release
cd ..
```

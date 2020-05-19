# cppredicates

Fast Robust Predicates for Computational Geometry in modern C++

## Project status: WIP

This project is currently work in progress.

- [x] Basic CMakeLists files
- [x] Setup original predicates, add initial benchmarks
- [x] Add doxygen and clang-format
- [x] Setup (dummy) support classes and `enums` for readability and type checking
- [ ] port `orient2d()` from `predicates` to `cppredicates`
- [ ] port `orient3d()` from `predicates` to `cppredicates`
- [ ] port in-circle test (2D) from `predicates` to `cppredicates`
- [ ] port in-sphere test from `predicates`  to `cppredicates`

## What is this all about?

This project ports [Adaptive Precision Floating-Point Arithmetic and Fast Robust Predicates for Computational Geometry](https://www.cs.cmu.edu/~quake/robust.html) by [Jonathan Richard Shewchuk](http://www.cs.berkeley.edu/~jrs) to modern C++.

## Acknowledgements

This project is just a port. All the hard work was done by [Jonathan Richard Shewchuk](http://www.cs.berkeley.edu/~jrs).

This project uses [Catch2](https://github.com/catchorg/Catch2) for testing and benchmarking.

## Contributing

Contributions are welcome. I have a `.clang-format` file, please use it to format your code before submitting a PR. Also, please run `doxygen` from the top-level directory of this project and make sure it doesn't complain.

## License

This port follows the decision of the [original code](https://www.cs.cmu.edu/afs/cs/project/quake/public/code/predicates.c), which was released into the public domain without any restrictions. Use it for whatever you see fit, see [The Unlicense](https://unlicense.org/).

The tests are building on [Catch2](https://github.com/catchorg/Catch2), which is licensed under BSL-1.0.

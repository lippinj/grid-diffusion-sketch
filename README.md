# grid-diffusion

Sketches on how to simulate heat transfer (and similar diffusion-like
processes) in a 3D rectangular grid (voxel grid).

The common theme in such processes is that a point in space continuously
interacts with its immediate neighborhood (exchanges heat, for instance).
In terms of a discrete grid, at each update pass, each cell communicates with
all of its immediate neighbors.
Effective implementation requires attention to details such as cache locality.

## building and running

Build with CMake, e.g.:

```
mkdir build
cd build
cmake ..
make
```

This produces an executable that runs some benchmarks, as well as a unit test
executable.
To run the benchmarks:

```
./grid-diffusion-benchmarks
```
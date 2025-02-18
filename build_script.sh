
git submodule update --init --recursive # This did all the below

# # 1. Build Kokkos
# cd ~/pj/skema/kokkos
# mkdir -p build
# cd build
# cmake -G Ninja -DCMAKE_INSTALL_PREFIX=./install ..
# ninja
# ninja install

# # 2. Build KokkosKernels
# cd ~/pj/skema/kokkos-kernels
# mkdir -p build
# cd build
# KOKKOS_PATH=$(readlink -f ../../kokkos/build/install)
# cmake -G Ninja \
#   -DKokkos_DIR=${KOKKOS_PATH}/lib/cmake/Kokkos \
#   -DCMAKE_INSTALL_PREFIX=./install \
#   ..
# ninja
# ninja install

# 3. Build main project (skema)
cd ~/pj/skema
mkdir -p build
cd build
KERNELS_PATH=$(readlink -f ../kokkos-kernels/build/install)
cmake -G Ninja \
  -DKokkosKernels_DIR=${KERNELS_PATH}/lib/cmake/KokkosKernels \
  ..
ninja


#!/bin/bash -le

#
# Reminder: Revert any changes to nvstdpar/CMakeLists.txt and
# nvstdpar/apps/heat-equation/CMakeLists.txt that you did
# for GCC compiler script before running this.
#

set -x

mkdir -p ${HOME}/stdparperformance/buildcpu1
cd ${HOME}/stdparperformance/buildcpu1

module use /global/cfs/cdirs/m1759/wwei/nvhpc_23_7/modulefiles

rm -rf ./*
ml unload cudatoolkit cray-mpich
ml cmake/3.24 nvhpc/23.1

cmake .. -DCMAKE_CXX_COMPILER=$(which nvc++) -DCMAKE_C_COMPILER=$(which nvc) -DCMAKE_BUILD_TYPE=Release -DSTDPAR= -DOMP=multicore

make -j

cd ${HOME}/stdparperformance/buildcpu1/apps/choleskey

./choleskey_serial --time 2>&1 |& tee md.txt

# parallel runs
T=(128 64 32 16 8 4 2 1)

# for i in "${T[@]}"; do
#     ./heat-equation-omp  --nthreads=${i} 2>&1 |& tee omp-${i}.txt
# done

for i in "${T[@]}"; do
    export OMP_NUM_THREADS=${i}
    ./choleskey_stdpar --time 2>&1 |& tee stdpar-${i}.txt
done

unset OMP_NUM_THREADS

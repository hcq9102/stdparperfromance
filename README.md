# stdparperfromance
Env prepare:

    salloc --nodes 1 --qos interactive --time 03:00:00 --constraint gpu --account=nintern
    
    ml use /global/cfs/cdirs/m1759/wwei/nvhpc_23_7/modulefiles ; ml unload cudatoolkit ; ml nvhpc/23.1 cmake/3.24

1. modified files in folder sourcefile.
   
           choleskey_serial.cpp,
           choleskey_stdpar.cpp,
           choleskey_stdpar_snd.cpp, and
           matrixutil.hpp
   
   
3. generate matrix for choleskey decomposition: input_generate.ipynb 
4. GPU build:
   
       cmake .. -DCMAKE_CXX_COMPILER=$(which nvc++) -DCMAKE_C_COMPILER=$(which nvc) -DCMAKE_BUILD_TYPE=Release -DSTDPAR=gpu
5. CPU build:
  
       cmake .. -DCMAKE_CXX_COMPILER=$(which nvc++) -DCMAKE_C_COMPILER=$(which nvc) -DCMAKE_BUILD_TYPE=Release -DSTDPAR=multicore


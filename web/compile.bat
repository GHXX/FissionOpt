"../../emsdk/emsdk_env.bat"
em++ --bind -O3 -s MODULARIZE=1 -s EXPORT_NAME=FissionOpt -s ALLOW_MEMORY_GROWTH=1 -o FissionOpt.js -std=c++17 -flto -O3 Bindings.cpp ../Fission.cpp ../OptFission.cpp ../FissionNet.cpp ../OverhaulFission.cpp ../OptOverhaulFission.cpp ../OverhaulFissionNet.cpp -I../../xtl/include -I../../xtensor/include

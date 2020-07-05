# GraphBuilder build script
# Find result in dir: out/linux

cd ..

[ -d out ] || mkdir out
cd out

[ -d linux ] || mkdir linux
cd linux

cmake ../.. && cmake --build .

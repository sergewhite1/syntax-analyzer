# Syntax analyzer  build script
# Find result in dir: out/linux

cd .. &&

mkdir -p out/linux &&
cd       out/linux &&

cmake ../.. && cmake --build .

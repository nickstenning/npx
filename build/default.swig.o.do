redo-ifchange compile "../src/$1.swig.cpp"
./compile "../src/$1.swig.cpp" "$3" "$1.swig.d" \
  "-isysroot / -isystem /usr/local/include/python2.7 -Wno-self-assign"
../tools/odeps -n "$1.swig.o" | xargs redo-ifchange 

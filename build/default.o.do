mkdir -p $(dirname "$1")
redo-ifchange ../compile "../src/$1.cpp"
../compile "../src/$1.cpp" "$3" "$1.d" "-I../src"
../odeps -n "$1.o" | xargs redo-ifchange 

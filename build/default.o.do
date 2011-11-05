SRC=$(echo "$1" | sed "s/__/\//g")
redo-ifchange ../compile "../src/$SRC.cpp"
../compile "../src/$SRC.cpp" "$3" "$1.d" "-I../src"
../odeps "$1.o" | xargs redo-ifchange 

redo-ifchange config.sh
. ./config.sh

# Write out a compile script, which takes four params:
#     $1 - the name of the source file, e.g. "src/main.cpp"
#     $2 - the name of the object file to write, e.g. "build/main.o"
#     $3 - the name of the deps file to write, e.g "build/main.d"
#     $4 - any additional CFLAGS

cat > "$3" <<-EOF    
    clang++ -MMD -MF "\$3" $CFLAGS \$4 -I../src -c -o "\$2" "\$1"
EOF
chmod a+x "$3"
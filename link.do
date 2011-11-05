redo-ifchange config.sh
. ./config.sh
LIBARGS=$(for l in ${LIBS}; do echo -n "-l${l} "; done)
cat > "$3" <<-EOF    
    clang++ $LIBARGS -o \${*}
EOF
chmod a+x "$3"

CFLAGS="-std=c++0x -stdlib=libc++
        -g \
        -pedantic-errors \
        -Wall -Wextra -Werror \
        -D__USE_FIXED_PROTOTYPES__ \
        -U__STRICT_ANSI__ \
        -D__STDC_FORMAT_MACROS"

clang++ -MMD -MF $1.d $CFLAGS -Isrc -c -o $3 $1.cpp
        
# kernel_libghthash
Windows Kernel adaptation of libghthash, kudos to Simon Kagstrom for making this awesome library.
All I did was port this library for usage in the Windows Kernel.

INTRODUCTION:
The Generic Hash Table (GHT) is a hash table that should be
extensible, generic and clean (codewise). You can store any kind of
data with it and, specify hash functions (or write your own) and
specify heuristics to use (like transposing touched elements).

The hash table *should* be portable, but it has only been tested on
Windows (x86) Linux (x86) and Solaris (SPARC). It compiles with the
-ansi directive under GCC, so it should hopefully be possible to
compile under many other systems as well.

USAGE
To use the library, add
  #include <ght_hash_table.h>

to your source-file and link your executable with
  -lghthash

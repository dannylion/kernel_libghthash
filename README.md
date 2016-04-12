# kernel_libghthash
Windows Kernel adaptation of libghthash, kudos to Simon Kagstrom for making this awesome library.
All I did was port this library for usage in the Windows Kernel.

See the original library at: https://github.com/SimonKagstrom/libghthash

INTRODUCTION:
The Generic Hash Table (GHT) is a hash table that should be
extensible, generic and clean (codewise). You can store any kind of
data with it and, specify hash functions (or write your own) and
specify heuristics to use (like transposing touched elements).

USAGE
To use the library, add
  #include <ght_hash_table.h>

to your source-file and add kernel_libghthash.lib to your project

#include "compress.hpp"
#include <iostream>

int main() {
    std::string original = "Hello, Make! This string will be compressed with zlib. "
                           "Repeating data compresses well: aaaaaaaaaaaaaaaaaaaaaa";

    auto compressed = compress_data(original);

    std::cout << "Original size:    " << original.size() << " bytes\n"
              << "Compressed size:  " << compressed.size() << " bytes\n";

    auto decompressed = decompress_data(compressed, original.size());

    std::cout << "Decompressed:     \"" << decompressed << "\"\n"
              << "Round-trip OK:    " << (decompressed == original ? "yes" : "no") << '\n';
}

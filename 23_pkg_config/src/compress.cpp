#include "compress.hpp"
#include <zlib.h>
#include <stdexcept>

std::vector<uint8_t> compress_data(const std::string& input) {
    uLongf compressed_size = compressBound(input.size());
    std::vector<uint8_t> output(compressed_size);

    int result = compress(output.data(), &compressed_size,
                          reinterpret_cast<const Bytef*>(input.data()),
                          input.size());

    if (result != Z_OK) {
        throw std::runtime_error("compress() failed with error code " + std::to_string(result));
    }

    output.resize(compressed_size);
    return output;
}

std::string decompress_data(const std::vector<uint8_t>& compressed, size_t original_size) {
    std::vector<uint8_t> output(original_size);
    uLongf dest_size = original_size;

    int result = uncompress(output.data(), &dest_size,
                            compressed.data(), compressed.size());

    if (result != Z_OK) {
        throw std::runtime_error("uncompress() failed with error code " + std::to_string(result));
    }

    return std::string(output.begin(), output.begin() + dest_size);
}

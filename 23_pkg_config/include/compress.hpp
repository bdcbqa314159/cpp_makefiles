#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <string>
#include <vector>
#include <cstdint>

std::vector<uint8_t> compress_data(const std::string& input);
std::string decompress_data(const std::vector<uint8_t>& compressed, size_t original_size);

#endif

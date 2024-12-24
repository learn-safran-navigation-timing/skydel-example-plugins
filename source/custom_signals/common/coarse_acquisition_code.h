#pragma once

#include <array>
#include <cstdint>
#include <vector>

class CoarseAcquisitionCode
{
public:
  CoarseAcquisitionCode();

  const int8_t* code(uint32_t prn) const; // returns the entire code for a prn

  static constexpr auto CHIPS_PER_MS = 1023;

private:
  std::vector<std::array<int8_t, CHIPS_PER_MS>> m_codes;
};

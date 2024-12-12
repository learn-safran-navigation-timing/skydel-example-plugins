#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class E1Code
{
public:
  static constexpr size_t E1B_CHIP_COUNT = 1023 * 4;
  static constexpr size_t E1C_PRIMARY_CHIP_COUNT = 1023 * 4;
  static constexpr size_t E1C_SECONDARY_CHIP_COUNT = 25;
  static constexpr size_t E1C_CHIP_COUNT = 1023 * 100;
  static constexpr size_t E1_MEMBERS_COUNT = 50;
  static const std::string CS_251;

  E1Code();

  const int8_t* getE1B(const uint32_t memberIdx) { return m_E1B[memberIdx].data(); }
  const int8_t* getE1C(const uint32_t memberIdx) { return m_E1C[memberIdx].data(); }

private:
  void loadFiles();
  void createE1BCode();
  void createE1CCode();
  void charToChipsVector(const std::string& c, std::vector<int8_t>& chipsOneChar);

  std::string m_E1BFile;
  std::vector<std::vector<int8_t>> m_E1B;

  std::string m_E1CFile;
  std::vector<std::vector<int8_t>> m_E1C;
};

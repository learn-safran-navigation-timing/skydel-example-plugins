#include "custom_g1.h"

#include <array>
#include <cstring>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_g1_downlink.csv"
#endif

namespace
{

constexpr uint64_t G1_SV_COUNT = 24;
constexpr uint64_t G1_FIRST_SLOT = 1;
constexpr uint64_t G1_NAV_MSG_BIT_COUNT = 200;
constexpr uint64_t G1_NAV_MSG_DURATION_MS = 2000;

// See glonass_constants.h
constexpr size_t G1_CODE_LENGTH = 511;
constexpr std::array<int8_t, G1_CODE_LENGTH> G1_RANGING_CODE = {
  {-1, -1, -1, -1, -1, -1, -1, 1,  1,  1,  1,  1,  -1, -1, -1, -1, 1,  -1, -1, -1, -1, -1, 1,  1,  1,  -1, 1,  -1, -1,
   -1, 1,  1,  -1, -1, 1,  1,  -1, 1,  1,  1,  1,  1,  -1, 1,  1,  -1, 1,  -1, 1,  1,  -1, -1, -1, 1,  -1, -1, 1,  -1,
   1,  1,  1,  -1, -1, -1, -1, 1,  1,  -1, -1, -1, -1, -1, 1,  1,  -1, -1, 1,  -1, -1, 1,  1,  1,  -1, 1,  -1, 1,  -1,
   1,  1,  -1, 1,  1,  1,  -1, -1, -1, 1,  1,  1,  -1, -1, 1,  -1, -1, 1,  -1, 1,  -1, 1,  -1, -1, -1, 1,  1,  1,  -1,
   1,  1,  -1, -1, 1,  1,  1,  -1, 1,  1,  1,  -1, 1,  1,  1,  1,  1,  1,  1,  1,  -1, 1,  1,  1,  1,  -1, 1,  1,  1,
   -1, -1, 1,  1,  1,  1,  -1, 1,  1,  -1, -1, -1, 1,  1,  -1, 1,  -1, 1,  -1, 1,  -1, -1, 1,  1,  1,  1,  -1, -1, 1,
   -1, -1, -1, -1, 1,  -1, 1,  1,  -1, -1, 1,  -1, -1, -1, 1,  1,  -1, 1,  1,  1,  -1, 1,  -1, 1,  1,  1,  1,  -1, 1,
   -1, 1,  -1, -1, 1,  -1, 1,  1,  -1, -1, -1, -1, -1, -1, 1,  -1, -1, 1,  1,  -1, 1,  1,  -1, 1,  1,  -1, 1,  -1, -1,
   1,  -1, -1, -1, -1, -1, -1, 1,  1,  -1, 1,  1,  -1, -1, 1,  -1, 1,  -1, 1,  1,  -1, -1, 1,  1,  -1, -1, 1,  1,  1,
   1,  1,  1,  1,  -1, -1, 1,  1,  1,  -1, -1, 1,  1,  -1, 1,  -1, 1,  1,  1,  -1, -1, 1,  -1, 1,  1,  -1, 1,  -1, -1,
   -1, -1, -1, -1, -1, 1,  -1, 1,  1,  1,  -1, 1,  -1, -1, 1,  1,  1,  -1, -1, -1, 1,  -1, 1,  -1, -1, 1,  1,  -1, 1,
   -1, -1, 1,  1,  -1, -1, -1, -1, 1,  1,  1,  -1, -1, -1, -1, -1, 1,  -1, -1, -1, 1,  -1, 1,  1,  1,  1,  1,  -1, -1,
   1,  -1, 1,  -1, -1, 1,  -1, -1, 1,  -1, -1, -1, 1,  -1, -1, 1,  1,  1,  1,  1,  -1, 1,  -1, -1, 1,  -1, 1,  -1, -1,
   -1, -1, -1, 1,  -1, 1,  -1, 1,  -1, 1,  -1, 1,  1,  1,  1,  1,  1,  -1, 1,  -1, 1,  1,  -1, 1,  -1, 1,  -1, -1, -1,
   -1, 1,  1,  -1, 1,  -1, -1, -1, 1,  -1, -1, -1, 1,  1,  1,  1,  1,  1,  -1, -1, -1, 1,  1,  -1, -1, -1, 1,  -1, 1,
   1,  -1, 1,  1,  -1, -1, -1, -1, 1,  -1, 1,  -1, -1, -1, 1,  -1, 1,  -1, 1,  1,  1,  -1, 1,  1,  -1, 1,  1,  1,  1,
   -1, -1, 1,  1,  -1, -1, -1, 1,  1,  1,  1,  -1, 1,  -1, -1, -1, -1, 1,  -1, -1, 1,  -1, -1, 1,  1,  -1, -1, 1,  -1,
   1,  1,  1,  1,  -1, -1, -1, 1,  -1, -1, -1, -1, 1,  1,  1,  1,  -1, -1}};

constexpr uint32_t G1_CHIPS_PER_MS = G1_CODE_LENGTH;

void setBits(std::array<bool, G1_NAV_MSG_BIT_COUNT>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  uint32_t word = 0;
  for (size_t i = 0; iss >> word; ++i)
  {
    for (size_t j = 0; (j < 32) && (i * 32 + j < bits.size()); ++j)
    {
      bits[i * 32 + j] = (word & (1 << (31 - j)));
    }
  }
}

} // namespace

G1Data::G1Data(const Sdx::CS::InitData& data) :
  startWeek(data.startWeek),
  startSecondOfWeek(data.startSecondOfWeek),
  navMsg(std::string {data.pathToXml} + '/' + DOWNLINK_PATH,
         std::make_unique<NavMessageBlock<G1_SV_COUNT, G1_FIRST_SLOT, G1_NAV_MSG_BIT_COUNT, G1_NAV_MSG_DURATION_MS>>(
           &setBits))
{
}

CustomG1NavMsg::CustomG1NavMsg(G1Data& data) : m_data(data)
{
}

uint32_t CustomG1NavMsg::getNavMsgDurationMs()
{
  return G1_NAV_MSG_DURATION_MS;
}

int32_t CustomG1NavMsg::getTOWOffset()
{
  return 0;
}

void CustomG1NavMsg::buildNavMsg(int64_t elapsedTimeMs, uint32_t prn, const Sdx::CS::Constellation& /*data*/)
{
  m_data.navMsg.prepare(elapsedTimeMs, prn);
}

CustomG1Code::CustomG1Code(G1Data& data) : m_data(data)
{
}

void CustomG1Code::getChips(int64_t elapsedTimeMs, uint32_t prn, int8_t* chips)
{
  int8_t sign = m_data.navMsg.getBit(elapsedTimeMs, prn) ? -1 : 1;
  for (size_t i = 0; i < G1_CHIPS_PER_MS; ++i)
    chips[i] = G1_RANGING_CODE[i] * sign;
}

uint32_t CustomG1Code::getNumberOfChipsPerMSec()
{
  return G1_CHIPS_PER_MS;
}

uint32_t CustomG1Code::getExtraAllocSize()
{
  return 0;
}

CustomG1::CustomG1(const Sdx::CS::InitData& data) : m_data(data), m_msg(m_data), m_code(m_data)
{
}

CustomG1::~CustomG1()
{
}

SkydelCustomSignalNavMsg* CustomG1::getNavMsg()
{
  return &m_msg;
}

SkydelCustomSignalCode* CustomG1::getCode(const char* name)
{
  return std::strcmp(name, "G1") == 0 ? &m_code : nullptr;
}

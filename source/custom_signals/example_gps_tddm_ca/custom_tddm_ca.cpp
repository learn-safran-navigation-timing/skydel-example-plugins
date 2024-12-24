#include "custom_tddm_ca.h"

#include <cstring>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_tddm_ca_downlink.csv"
#endif

namespace
{

void setBits(std::array<bool, 300>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  for (int i = 0; i < 10; ++i)
  {
    uint32_t word = 0;
    iss >> word;

    for (int j = 0; j < 30; ++j)
      bits[i * 30 + j] = word & (1 << (29 - j));
  }
}

} // namespace

TddmCAData::TddmCAData(const Sdx::CS::InitData& data) :
  startWeek(data.startWeek),
  startSecondOfWeek(data.startSecondOfWeek),
  navMsg(std::string {data.pathToXml} + '/' + DOWNLINK_PATH,
         std::make_unique<NavMessageBlock<32, 1, 300, 6000>>(&setBits))
{
}

CustomTddmCANavMsg::CustomTddmCANavMsg(TddmCAData& data) : m_data(data)
{
}

uint32_t CustomTddmCANavMsg::getNavMsgDurationMs()
{
  return 6000;
}

int32_t CustomTddmCANavMsg::getTOWOffset()
{
  return 0;
}

void CustomTddmCANavMsg::buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& /*data*/)
{
  m_data.navMsg.prepare(elapsedTime, prn);
}

CustomTddmCACode::CustomTddmCACode(TddmCAData& data) : m_data(data)
{
}

void CustomTddmCACode::getChips(int64_t elapsedMs, uint32_t prn, int8_t* chips)
{
  const auto chipStartIdx = elapsedMs * CoarseAcquisitionCode::CHIPS_PER_MS;
  const int8_t sign = m_data.navMsg.getBit(elapsedMs, prn) ? -1 : 1;
  const auto code = m_data.codes.code(prn);

  for (int i = 0; i < CoarseAcquisitionCode::CHIPS_PER_MS; ++i)
  {
    const auto chipIdx = chipStartIdx + i;
    chips[i] = code[i];

    if (chipIdx % 2 == 1) // Odd chip
    {
      chips[i] *= sign;
    }
  }
}

uint32_t CustomTddmCACode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomTddmCACode::getExtraAllocSize()
{
  return 0;
}

CustomTddmCA::CustomTddmCA(const Sdx::CS::InitData& data) : m_data(data), m_msg(m_data), m_code(m_data)
{
}

CustomTddmCA::~CustomTddmCA()
{
}

SkydelCustomSignalNavMsg* CustomTddmCA::getNavMsg()
{
  return &m_msg;
}

SkydelCustomSignalCode* CustomTddmCA::getCode(const char* name)
{
  if (std::strcmp(name, "TDDM_L1CA") == 0)
    return &m_code;
  return nullptr;
}

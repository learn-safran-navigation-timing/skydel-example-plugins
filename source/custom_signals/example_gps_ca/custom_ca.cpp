#include "custom_ca.h"

#include <cstring>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_ca_downlink.csv"
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

CAData::CAData(const Sdx::CS::InitData& data) :
  startWeek(data.startWeek),
  startSecondOfWeek(data.startSecondOfWeek),
  navMsg(std::string {data.pathToXml} + '/' + DOWNLINK_PATH,
         std::make_unique<NavMessageBlock<32, 1, 300, 6000>>(&setBits))
{
}

CustomCANavMsg::CustomCANavMsg(CAData& data) : m_data(data)
{
}

uint32_t CustomCANavMsg::getNavMsgDurationMs()
{
  return 6000;
}

int32_t CustomCANavMsg::getTOWOffset()
{
  return 0;
}

void CustomCANavMsg::buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& /*data*/)
{
  m_data.navMsg.prepare(elapsedTime, prn);
}

CustomCACode::CustomCACode(CAData& data) : m_data(data)
{
}

void CustomCACode::getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips)
{
  int8_t sign = m_data.navMsg.getBit(elapsedTime, prn) ? -1 : 1;
  for (int i = 0; i < 1023; ++i)
    chips[i] = m_data.codes.code(prn)[i] * sign;
}

uint32_t CustomCACode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomCACode::getExtraAllocSize()
{
  return 0;
}

CustomCA::CustomCA(const Sdx::CS::InitData& data) : m_data(data), m_msg(m_data), m_code(m_data)
{
}

CustomCA::~CustomCA()
{
}

SkydelCustomSignalNavMsg* CustomCA::getNavMsg()
{
  return &m_msg;
}

SkydelCustomSignalCode* CustomCA::getCode(const char* name)
{
  if (std::strcmp(name, "L1CA") == 0)
    return &m_code;
  return nullptr;
}

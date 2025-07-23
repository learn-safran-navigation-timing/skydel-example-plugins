#include "custom_qzss_ca.h"

#include <cstring>
#include <filesystem>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_qzss_ca_downlink.csv"
#endif

namespace
{

constexpr auto toPrn(auto svID)
{
  constexpr auto QZSS_FIRST_PRN = 193;
  return svID + QZSS_FIRST_PRN - 1;
}

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

QzssCAData::QzssCAData(const Sdx::CS::InitializationDatas& datas) :
  navMsg((std::filesystem::path(std::get<std::string>(datas.at(Sdx::CS::PATH_TO_XML_KEY))) / DOWNLINK_PATH).string(),
         std::make_unique<NavMessageBlock<10, 300, 6000>>(&setBits))
{
}

CustomQzssCANavMsg::CustomQzssCANavMsg(QzssCAData& data) : m_data(data)
{
}

uint32_t CustomQzssCANavMsg::getNavMsgDurationMs()
{
  return 6000;
}

int32_t CustomQzssCANavMsg::getTOWOffset()
{
  return 0;
}

void CustomQzssCANavMsg::buildNavMsg(int64_t elapsedTime, uint32_t svID, const Sdx::CS::ConstellationDatas&)
{
  m_data.navMsg.prepare(elapsedTime, svID);
}

CustomQzssCACode::CustomQzssCACode(QzssCAData& data) : m_data(data)
{
}

void CustomQzssCACode::getChips(int64_t elapsedTime, uint32_t svID, int8_t* chips)
{
  int8_t sign = m_data.navMsg.getBit(elapsedTime, svID) ? -1 : 1;
  for (int i = 0; i < 1023; ++i)
    chips[i] = m_data.codes.code(toPrn(svID))[i] * sign;
}

uint32_t CustomQzssCACode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomQzssCACode::getExtraAllocSize()
{
  return 0;
}

CustomQzssCA::CustomQzssCA(const Sdx::CS::InitializationDatas& datas) : m_data(datas), m_msg(m_data), m_code(m_data)
{
}

CustomQzssCA::~CustomQzssCA()
{
}

SkydelCustomSignalNavMsg* CustomQzssCA::getNavMsg()
{
  return &m_msg;
}

SkydelCustomSignalCode* CustomQzssCA::getCode(const char* name)
{
  if (std::strcmp(name, "L1CA") == 0)
    return &m_code;
  return nullptr;
}

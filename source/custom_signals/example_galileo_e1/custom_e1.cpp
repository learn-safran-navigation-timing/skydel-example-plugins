#include "custom_e1.h"

#include <cstring>
#include <filesystem>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_e1_downlink.csv"
#endif

namespace
{

void setBits(std::array<bool, 500>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  uint32_t word;
  int i = 0;
  while (iss >> word)
  {
    for (int j = 0; j < 32; ++j)
    {
      if (i * 32 + j < 500)
        bits[i * 32 + j] = (word & (1 << (31 - j))) != 0;
    }
    ++i;
  }
}

} // namespace

E1Data::E1Data(const Sdx::CS::InitializationDatas& datas) :
  navMsg((std::filesystem::path(std::get<std::string>(datas.at(Sdx::CS::PATH_TO_XML_KEY))) / DOWNLINK_PATH).string(),
         std::make_unique<NavMessageBlock<36, 500, 2000>>(&setBits))
{
}

CustomE1NavMsg::CustomE1NavMsg(E1Data& data) : m_data(data)
{
}

uint32_t CustomE1NavMsg::getNavMsgDurationMs()
{
  return 2000;
}

int32_t CustomE1NavMsg::getTOWOffset()
{
  return 1;
}

void CustomE1NavMsg::buildNavMsg(int64_t elapsedTime, uint32_t svID, const Sdx::CS::ConstellationDatas&)
{
  m_data.navMsg.prepare(elapsedTime, svID);
}

CustomE1BCode::CustomE1BCode(E1Data& data) : m_data(data)
{
}

void CustomE1BCode::getChips(int64_t elapsedTime, uint32_t svID, int8_t* chips)
{
  const int8_t* fullCode = m_data.code.getE1B(svID - 1);
  const int8_t* curMs = fullCode + (elapsedTime % 4) * 1023;

  int8_t navBit = m_data.navMsg.getBit(elapsedTime, svID) ? -1 : 1;

  for (int i = 0; i < 1023; ++i)
    chips[i] = navBit * curMs[i];
}

uint32_t CustomE1BCode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomE1BCode::getExtraAllocSize()
{
  return 0;
}

CustomE1CCode::CustomE1CCode(E1Data& data) : m_data(data)
{
}

void CustomE1CCode::getChips(int64_t elapsedTime, uint32_t svID, int8_t* chips)
{
  const int8_t* fullCode = m_data.code.getE1C(svID - 1);
  const int8_t* curMs = fullCode + (elapsedTime % 100) * 1023;
  std::memcpy(chips, curMs, 1023);
}

uint32_t CustomE1CCode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomE1CCode::getExtraAllocSize()
{
  return 0;
}

CustomE1::CustomE1(const Sdx::CS::InitializationDatas& datas) :
  m_data(datas),
  m_msg(m_data),
  m_e1bCode(m_data),
  m_e1cCode(m_data)
{
}

CustomE1::~CustomE1()
{
}

SkydelCustomSignalNavMsg* CustomE1::getNavMsg()
{
  return &m_msg;
}

SkydelCustomSignalCode* CustomE1::getCode(const char* name)
{
  if (name == std::string {"E1B"})
    return &m_e1bCode;
  if (name == std::string {"E1C"})
    return &m_e1cCode;
  return nullptr;
}

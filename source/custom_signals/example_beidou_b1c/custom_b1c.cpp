#include "custom_b1c.h"

#include <filesystem>
#include <string>

#include "custom_b1c_codes.h"
#include "custom_b1c_nav_message.h"

namespace
{
constexpr auto DOWNLINK_FILENAME = "custom_b1c_downlink.csv";
}

struct CustomB1C::Pimpl
{
  Pimpl(uint32_t startSecOfBeiDouWeek) : csDataCode(startSecOfBeiDouWeek), csPilotCode(startSecOfBeiDouWeek), csNavMsg()
  {
  }

  CustomB1CDataCode csDataCode;
  CustomB1CPilotCode csPilotCode;
  CustomB1CNavMsg csNavMsg;
};

CustomB1C::CustomB1C(const Sdx::CS::InitializationDatas& csInitDatas) :
  m(std::make_unique<Pimpl>(std::get<uint32_t>(csInitDatas.at(Sdx::CS::START_SECOND_OF_WEEK_KEY))))
{
  auto navGenPtr = CustomB1CNavMsg::makeSharedB1CNavMsgFromFile(
    (std::filesystem::path(std::get<std::string>(csInitDatas.at(Sdx::CS::PATH_TO_XML_KEY))) / DOWNLINK_FILENAME)
      .string());
  m->csDataCode.setNavMessageGenerator(navGenPtr);
  m->csNavMsg.setNavMessageGenerator(navGenPtr);
}

CustomB1C::~CustomB1C()
{
}

SkydelCustomSignalNavMsg* CustomB1C::getNavMsg()
{
  return &m->csNavMsg;
}

SkydelCustomSignalCode* CustomB1C::getCode(const char* name)
{
  if (name == std::string(CustomB1CDataCode::xmlCodeName))
  {
    return &m->csDataCode;
  }
  else if (name == std::string(CustomB1CPilotCode::xmlCodeName))
  {
    return &m->csPilotCode;
  }
  return nullptr;
}

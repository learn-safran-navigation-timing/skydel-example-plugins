#include "custom_b1c_nav_message.h"

#include <limits>
#include <sstream>

#include "custom_signal_nav_msg_from_file.h"

namespace
{
constexpr uint32_t NB_SVID_MAX = 63;
constexpr uint64_t MESSAGE_DURATION_MS = 18000;
constexpr uint64_t BIT_COUNT = 1800;
constexpr uint64_t DOWNLINK_NAV_MESSAGE_INDEX = 6;

void setBits(std::array<bool, BIT_COUNT>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  uint32_t word = 0;
  constexpr auto nbBitsInWord = std::numeric_limits<decltype(word)>::digits;
  for (size_t bitIdxOffset = 0; iss >> word; bitIdxOffset += nbBitsInWord)
  {
    for (size_t bitIdx = 0; (bitIdx < nbBitsInWord) && (bitIdxOffset + bitIdx < bits.size()); ++bitIdx)
    {
      bits[bitIdxOffset + bitIdx] = (word & (1 << (nbBitsInWord - 1 - bitIdx)));
    }
  }
}

} // namespace

std::shared_ptr<CustomSignalNavMsgFromFile> CustomB1CNavMsg::makeSharedB1CNavMsgFromFile(std::string downlinkPath)
{
  return std::make_shared<CustomSignalNavMsgFromFile>(
    downlinkPath,
    std::make_unique<NavMessageBlock<NB_SVID_MAX, BIT_COUNT, MESSAGE_DURATION_MS>>(&setBits),
    DOWNLINK_NAV_MESSAGE_INDEX);
}

struct CustomB1CNavMsg::Pimpl
{
  Pimpl();
  Pimpl(std::shared_ptr<CustomSignalNavMsgFromFile>);
  std::shared_ptr<CustomSignalNavMsgFromFile> navMsg;
};

CustomB1CNavMsg::Pimpl::Pimpl() : navMsg(nullptr)
{
}

CustomB1CNavMsg::CustomB1CNavMsg() : m(std::make_unique<Pimpl>())
{
}

void CustomB1CNavMsg::setNavMessageGenerator(std::shared_ptr<CustomSignalNavMsgFromFile> gen)
{
  m->navMsg = gen;
}

CustomB1CNavMsg::~CustomB1CNavMsg()
{
}

uint32_t CustomB1CNavMsg::getNavMsgDurationMs()
{
  return MESSAGE_DURATION_MS;
}

int32_t CustomB1CNavMsg::getTOWOffset()
{
  return 0;
}

void CustomB1CNavMsg::buildNavMsg(int64_t elapsedTime, uint32_t svID, const Sdx::CS::ConstellationDatas&)
{
  m->navMsg->prepare(elapsedTime, svID);
}

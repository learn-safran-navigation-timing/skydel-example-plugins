#pragma once

#include <memory>
#include <string>

#include "skydel_plug_ins/custom_signal/skydel_custom_signal_nav_msg.h"

class CustomSignalNavMsgFromFile;

class CustomB1CNavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomB1CNavMsg();
  ~CustomB1CNavMsg() override;
  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& data) override;
  void setNavMessageGenerator(std::shared_ptr<CustomSignalNavMsgFromFile>);
  static std::shared_ptr<CustomSignalNavMsgFromFile> makeSharedB1CNavMsgFromFile(std::string downlinkPath);

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

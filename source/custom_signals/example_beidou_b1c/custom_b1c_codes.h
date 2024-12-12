#pragma once

#include <memory>

#include "skydel_plug_ins/custom_signal/skydel_custom_signal_code.h"

class CustomSignalNavMsgFromFile;

class CustomB1CCode : public SkydelCustomSignalCode
{
public:
  CustomB1CCode(uint32_t startSecOfBeiDouWeek) : m_startMSOfBeiDouWeek(startSecOfBeiDouWeek * 1000) {}

  int64_t elapsedTimeMsToBeidouTOWMs(int64_t elapsedTimeMs) const;

private:
  uint64_t m_startMSOfBeiDouWeek;
};

class CustomB1CDataCode : public CustomB1CCode
{
public:
  static constexpr auto xmlCodeName = "B1CData";

  CustomB1CDataCode(uint32_t startSecOfBeiDouWeek);
  ~CustomB1CDataCode() override;

  void setNavMessageGenerator(std::shared_ptr<CustomSignalNavMsgFromFile>);

  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;
  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

class CustomB1CPilotCode : public CustomB1CCode
{
public:
  static constexpr auto xmlCodeName = "B1CPilot";

  CustomB1CPilotCode(uint32_t startSecOfBeiDouWeek);
  ~CustomB1CPilotCode() override;

  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;
  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

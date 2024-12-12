#pragma once

#include <fstream>

#include "custom_signal_nav_msg_from_file.h"
#include "e1_code.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_factory_interface.h"

class E1Data
{
public:
  E1Data(const Sdx::CS::InitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  E1Code code;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomE1NavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomE1NavMsg(E1Data& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& data) override;

private:
  E1Data& m_data;
};

class CustomE1BCode : public SkydelCustomSignalCode
{
public:
  CustomE1BCode(E1Data& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  E1Data& m_data;
};

class CustomE1CCode : public SkydelCustomSignalCode
{
public:
  CustomE1CCode(E1Data& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  E1Data& m_data;
};

class CustomE1 : public SkydelCustomSignalInterface
{
public:
  CustomE1(const Sdx::CS::InitData& data);
  ~CustomE1();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  E1Data m_data;
  CustomE1NavMsg m_msg;
  CustomE1BCode m_e1bCode;
  CustomE1CCode m_e1cCode;
};

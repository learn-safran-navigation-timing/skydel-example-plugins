#pragma once

#include <fstream>

#include "coarse_acquisition_code.h"
#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_factory_interface.h"

class TddmCAData
{
public:
  TddmCAData(const Sdx::CS::InitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomTddmCANavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomTddmCANavMsg(TddmCAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& data) override;

private:
  TddmCAData& m_data;
};

class CustomTddmCACode : public SkydelCustomSignalCode
{
public:
  CustomTddmCACode(TddmCAData& data);

  void getChips(int64_t elapsedMs, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  TddmCAData& m_data;
};

class CustomTddmCA : public SkydelCustomSignalInterface
{
public:
  CustomTddmCA(const Sdx::CS::InitData& data);
  ~CustomTddmCA();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  TddmCAData m_data;
  CustomTddmCANavMsg m_msg;
  CustomTddmCACode m_code;
};

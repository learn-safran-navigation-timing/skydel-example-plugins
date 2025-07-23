#pragma once

#include "coarse_acquisition_code.h"
#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_interface.h"

class TddmCAData
{
public:
  TddmCAData(const Sdx::CS::InitializationDatas& datas);

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomTddmCANavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomTddmCANavMsg(TddmCAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t svID, const Sdx::CS::ConstellationDatas& datas) override;

private:
  TddmCAData& m_data;
};

class CustomTddmCACode : public SkydelCustomSignalCode
{
public:
  CustomTddmCACode(TddmCAData& data);

  void getChips(int64_t elapsedMs, uint32_t svID, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  TddmCAData& m_data;
};

class CustomTddmCA : public SkydelCustomSignalInterface
{
public:
  CustomTddmCA(const Sdx::CS::InitializationDatas& datas);
  ~CustomTddmCA();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  TddmCAData m_data;
  CustomTddmCANavMsg m_msg;
  CustomTddmCACode m_code;
};

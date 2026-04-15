#pragma once

#include "coarse_acquisition_code.h"
#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_interface.h"

class CAData
{
public:
  CAData(const Sdx::CS::InitializationDatas& datas);

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomCANavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomCANavMsg(CAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t svID, const Sdx::CS::ConstellationDatas& datas) override;

private:
  CAData& m_data;
};

class CustomCACode : public SkydelCustomSignalCode
{
public:
  CustomCACode(CAData& data);

  void getChips(int64_t elapsedTime, uint32_t svID, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  CAData& m_data;
};

class CustomCA : public SkydelCustomSignalInterface
{
public:
  CustomCA(const Sdx::CS::InitializationDatas& datas);
  ~CustomCA();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  CAData m_data;
  CustomCANavMsg m_msg;
  CustomCACode m_code;
};

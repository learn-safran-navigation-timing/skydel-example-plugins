#pragma once

#include <fstream>

#include "coarse_acquisition_code.h"
#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_factory_interface.h"

class CAData
{
public:
  CAData(const Sdx::CS::InitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomCANavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomCANavMsg(CAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& data) override;

private:
  CAData& m_data;
};

class CustomCACode : public SkydelCustomSignalCode
{
public:
  CustomCACode(CAData& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  CAData& m_data;
};

class CustomCA : public SkydelCustomSignalInterface
{
public:
  CustomCA(const Sdx::CS::InitData& data);
  ~CustomCA();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  CAData m_data;
  CustomCANavMsg m_msg;
  CustomCACode m_code;
};

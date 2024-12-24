#pragma once

#include <fstream>

#include "coarse_acquisition_code.h"
#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_factory_interface.h"

class QzssCAData
{
public:
  QzssCAData(const Sdx::CS::InitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomQzssCANavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomQzssCANavMsg(QzssCAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const Sdx::CS::Constellation& data) override;

private:
  QzssCAData& m_data;
};

class CustomQzssCACode : public SkydelCustomSignalCode
{
public:
  CustomQzssCACode(QzssCAData& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  QzssCAData& m_data;
};

class CustomQzssCA : public SkydelCustomSignalInterface
{
public:
  CustomQzssCA(const Sdx::CS::InitData& data);
  ~CustomQzssCA();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  QzssCAData m_data;
  CustomQzssCANavMsg m_msg;
  CustomQzssCACode m_code;
};

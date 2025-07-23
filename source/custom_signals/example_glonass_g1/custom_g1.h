#pragma once

#include "custom_signal_nav_msg_from_file.h"
#include "skydel_plug_ins/custom_signal/skydel_custom_signal_interface.h"

class G1Data
{
public:
  G1Data(const Sdx::CS::InitializationDatas& datas);

  CustomSignalNavMsgFromFile navMsg;
};

class CustomG1NavMsg : public SkydelCustomSignalNavMsg
{
public:
  CustomG1NavMsg(G1Data& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTimeMs, uint32_t svID, const Sdx::CS::ConstellationDatas& datas) override;

private:
  G1Data& m_data;
};

class CustomG1Code : public SkydelCustomSignalCode
{
public:
  CustomG1Code(G1Data& data);

  void getChips(int64_t elapsedTimeMs, uint32_t svID, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  G1Data& m_data;
};

class CustomG1 : public SkydelCustomSignalInterface
{
public:
  CustomG1(const Sdx::CS::InitializationDatas& datas);
  ~CustomG1();

  SkydelCustomSignalNavMsg* getNavMsg() override;
  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  G1Data m_data;
  CustomG1NavMsg m_msg;
  CustomG1Code m_code;
};

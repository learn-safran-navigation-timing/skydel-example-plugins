#pragma once

#include <memory>

#include "skydel_plug_ins/custom_signal/skydel_custom_signal_interface.h"

class CustomB1C final : public SkydelCustomSignalInterface
{
public:
  CustomB1C(const Sdx::CS::InitializationDatas& csInitDatas);

  ~CustomB1C() override;

  SkydelCustomSignalNavMsg* getNavMsg() override;

  SkydelCustomSignalCode* getCode(const char* name) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

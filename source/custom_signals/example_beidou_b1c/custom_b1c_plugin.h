#pragma once

#include "custom_b1c.h"
#include "skydel_plug_ins/skydel_plugin.h"

class CustomB1CPlugin : public QObject, public SkydelCoreInterface, public SkydelCustomSignalFactoryInterface
{
  Q_OBJECT

public:
  CustomB1CPlugin();

  // SkydelCoreInterface
  inline void setLogPath(const QString&) override {}
  inline void setInstanceIdentifier(uint32_t) override {}
  inline void setNotifier(SkydelNotifierInterface*) override {}
  void setConfiguration(const QString&, const QJsonObject&) override {}
  QJsonObject getConfiguration() const override { return {}; }
  SkydelWidgets createUI() override { return {}; }
  inline void initialize() override {}

  // SkydelCustomSignalFactoryInterface
  inline SkydelCustomSignalInterface* createCustomSignal(const Sdx::CS::InitData& data) override
  {
    return new CustomB1C(data);
  };

signals:
  void configurationChanged();
};

REGISTER_SKYDEL_PLUGIN(CustomB1CPlugin)

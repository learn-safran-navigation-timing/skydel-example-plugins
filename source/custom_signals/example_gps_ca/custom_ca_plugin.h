#pragma once

#include "custom_ca.h"
#include "skydel_plug_ins/skydel_plugin.h"

class CustomCAPlugin : public QObject, public SkydelCoreInterface, public SkydelCustomSignalFactoryInterface
{
  Q_OBJECT

public:
  CustomCAPlugin();

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
    return new CustomCA(data);
  };

signals:
  void configurationChanged();
};

REGISTER_SKYDEL_PLUGIN(CustomCAPlugin)

#pragma once

#include "custom_qzss_ca.h"
#include "skydel_plug_ins/skydel_plugin.h"

class CustomQzssCAPlugin : public QObject, public SkydelCoreInterface, public SkydelCustomSignalFactoryInterface
{
  Q_OBJECT

public:
  CustomQzssCAPlugin();

  // SkydelCoreInterface
  inline void setLogPath(const QString&) override {}
  inline void setNotifier(SkydelNotifierInterface*) override {}
  void setConfiguration(const QString&, const QJsonObject&) override {}
  QJsonObject getConfiguration() const override { return {}; }
  SkydelWidgets createUI() override { return {}; }
  inline void initialize() override {}

  // SkydelCustomSignalFactoryInterface
  inline SkydelCustomSignalInterface* createCustomSignal(const Sdx::CS::InitData& data) override
  {
    return new CustomQzssCA(data);
  };

signals:
  void configurationChanged();
};

REGISTER_SKYDEL_PLUGIN(CustomQzssCAPlugin)

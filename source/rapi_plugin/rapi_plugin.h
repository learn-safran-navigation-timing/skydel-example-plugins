#pragma once

#include "rapi_plugin_command_handler.h"
#include "skydel_plug_ins/skydel_command_handler_access.h"
#include "skydel_plug_ins/skydel_plugin.h"
#include "skydel_plug_ins/skydel_rapi_access.h"

// Plugin implementation
class RapiPlugin :
  public QObject,
  public SkydelCoreInterface,
  public SkydelRapiAccess,
  public SkydelCommandHandlerAccess
{
  Q_OBJECT

public:
  RapiPlugin();

  // SkydelCoreInterface
  inline void setLogPath([[maybe_unused]] const QString& path) override {};
  inline void setNotifier(SkydelNotifierInterface* notifier) override
  {
    m_notifier = notifier;
    m_commandHandler.setNotifier(m_notifier);
  }
  inline void setConfiguration([[maybe_unused]] const QString& version,
                               [[maybe_unused]] const QJsonObject& configuration) override
  {
  }
  inline QJsonObject getConfiguration() const override { return QJsonObject {}; }
  SkydelWidgets createUI() override;
  inline void initialize() override {}

private:
  RapiPluginCommandHandler m_commandHandler;
  SkydelNotifierInterface* m_notifier;
};

REGISTER_SKYDEL_PLUGIN(RapiPlugin)

#pragma once

#include "skydel_plug_ins/skydel_plugin.h"

// Plugin implementation
class SimplePlugin : public QObject, public SkydelCoreInterface
{
  Q_OBJECT

public:
  // SkydelCoreInterface
  inline void setLogPath(const QString&) override {}
  inline void setNotifier(SkydelNotifierInterface* notifier) override { m_skydelNotifier = notifier; }
  void setConfiguration(const QString& version, const QJsonObject& configuration) override;
  QJsonObject getConfiguration() const override;
  SkydelWidgets createUI() override;
  inline void initialize() override {}

signals:
  void configurationChanged();

private:
  QString m_logPath;
  SkydelNotifierInterface* m_skydelNotifier;
  QString m_notificationMessage {"Hello Skydel!"};
  SkydelNotifierInterface::Type m_notificationType {SkydelNotifierInterface::Type::WARNING};
};

REGISTER_SKYDEL_PLUGIN(SimplePlugin)

#pragma once

#include "skydel_plug_ins/skydel_plugin.h"

// Plugin implementation
class HilObserverPlugin : public QObject, public SkydelCoreInterface, public SkydelHilObserverInterface
{
  Q_OBJECT

public:
  // SkydelCoreInterface
  inline void setLogPath(const QString& logPath) override { m_logPath = logPath; }
  inline void setNotifier(SkydelNotifierInterface* notifier) override { m_skydelNotifier = notifier; }
  void setConfiguration(const QString&, const QJsonObject& configuration) override;
  QJsonObject getConfiguration() const override;
  SkydelWidgets createUI() override;
  inline void initialize() override {}

  // SkydelHilObserverInterface
  SkydelRuntimeHilObserver* createRuntimeHilObserver() override;

signals:
  void configurationChanged();

private:
  QString m_logPath;
  bool m_enableFileLogging {false};
  SkydelNotifierInterface* m_skydelNotifier;
};

REGISTER_SKYDEL_PLUGIN(HilObserverPlugin)

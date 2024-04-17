#pragma once

#include <QObject>
#include <QString>
#include <QUdpSocket>

#include "radio_time_logger.h"
#include "skydel_plug_ins/skydel_plugin.h"

// Plugin implementation
class RadioTimeObserverPlugin :
  public QObject,
  public SkydelCoreInterface,
  public SkydelRadioTimeObserverInterface,
  public SkydelPositionObserverInterface
{
  Q_OBJECT

public:
  explicit RadioTimeObserverPlugin(QObject* parent = nullptr);
  // SkydelCoreInterface
  inline void setLogPath(const QString& path) override { m_logPath = path; }
  inline void setNotifier(SkydelNotifierInterface* notifier) override { m_skydelNotifier = notifier; }
  void setConfiguration(const QString& version, const QJsonObject& configuration) override;
  QJsonObject getConfiguration() const override;
  SkydelWidgets createUI() override;
  inline void initialize() override {}

  // SkydelRadioTimeObserverInterface
  SkydelRuntimeRadioTimeObserver* createRuntimeRadioTimeObserver() override;

  // SkydelPositionObserverInterface
  SkydelRuntimePositionObserver* createRuntimePositionObserver() override;

private slots:
  void onRuntimeObjectsDestroyed();

signals:
  void configurationChanged();
  void lockConfiguration(bool lock);

private:
  bool isEnabled() const;

  QHostAddress m_address {QHostAddress(QHostAddress::LocalHost)};
  QString m_logPath;
  SkydelNotifierInterface* m_skydelNotifier;
  RadioTimeLogger m_logger;
  uint16_t m_port {1610};
  bool m_enableFileLogging {false};
  bool m_enableNetworkLogging {false};
};

REGISTER_SKYDEL_PLUGIN(RadioTimeObserverPlugin)

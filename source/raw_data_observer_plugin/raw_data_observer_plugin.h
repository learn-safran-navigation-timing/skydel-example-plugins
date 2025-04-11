#pragma once

#include <QString>
#include <QUdpSocket>

#include "raw_data_logger.h"
#include "skydel_plug_ins/skydel_plugin.h"

// Plugin implementation
class RawDataObserverPlugin : public QObject, public SkydelCoreInterface, public SkydelRawDataObserverInterface
{
  Q_OBJECT

public:
  // SkydelCoreInterface
  inline void setLogPath(const QString& path) override { m_logPath = path; }
  inline void setInstanceIdentifier(uint32_t) override {}
  inline void setNotifier(SkydelNotifierInterface* notifier) override { m_skydelNotifier = notifier; }
  void setConfiguration(const QString& version, const QJsonObject& configuration) override;
  QJsonObject getConfiguration() const override;
  SkydelWidgets createUI() override;
  inline void initialize() override {}

  // SkydelRawDataObserverInterface
  inline SkydelRuntimeRawDataObserver* createRuntimeRawDataObserver(
    const SkydelConstellationIDToStringMap& constellationIDToString,
    const SkydelSignalIDToStringMap& signalIDToString) override
  {
    return (m_enableFileLogging || m_enableNetworkLogging) ? new RawDataLogger(m_skydelNotifier,
                                                                               constellationIDToString,
                                                                               signalIDToString,
                                                                               m_address,
                                                                               m_port,
                                                                               m_loggerRateMs,
                                                                               m_enableNetworkLogging,
                                                                               m_enableFileLogging,
                                                                               m_logPath)
                                                           : nullptr;
  }

signals:
  void configurationChanged();

private:
  bool m_enableFileLogging {false};
  bool m_enableNetworkLogging {false};
  QHostAddress m_address {QHostAddress(QHostAddress::LocalHost)};
  uint16_t m_port {161};
  QString m_logPath;
  SkydelNotifierInterface* m_skydelNotifier;
  uint64_t m_loggerRateMs {100};
};

REGISTER_SKYDEL_PLUGIN(RawDataObserverPlugin)

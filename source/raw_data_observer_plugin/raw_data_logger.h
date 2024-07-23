#pragma once

#include <QFile>
#include <QUdpSocket>

#include "skydel_plug_ins/skydel_plugin.h"

// Runtime raw data observer implementation
class RawDataLogger : public SkydelRuntimeRawDataObserver
{
  Q_OBJECT
public:
  explicit RawDataLogger(SkydelNotifierInterface* skydelNotifier,
                         const SkydelConstellationIDToStringMap& constellationIDToString,
                         const SkydelSignalIDToStringMap& signalIDToString,
                         const QHostAddress& address,
                         uint16_t port,
                         uint64_t rawRateMs,
                         bool enableNetworkLogging,
                         bool enableFileLogging,
                         const QString& logPath);
  ~RawDataLogger();
  void pushRawData(const SkydelRuntimeRawDataObserver::TimedRawData&) override;
  void connectToView(QWidget* view) override;

signals:
  void lockConfiguration(bool lock);

private:
  void streamData(const SkydelRuntimeRawDataObserver::TimedRawData& data, QTextStream& stream);

  SkydelNotifierInterface* m_skydelNotifier;
  SkydelConstellationIDToStringMap m_constellationIDToString;
  SkydelSignalIDToStringMap m_signalIDToString;
  bool m_enableFileLogging;
  bool m_enableNetworkLogging;
  QHostAddress m_address;
  uint16_t m_port;
  uint64_t m_rateMs;
  QString m_logPath;
  QFile m_file;
  QUdpSocket m_socket;
};

#include "raw_data_logger.h"

#include <QDir>
#include <QTextStream>

#include <stdexcept>

#include "widgets/simple_logging_view.h"

RawDataLogger::RawDataLogger(SkydelNotifierInterface* skydelNotifier,
                             const SkydelConstellationIDToStringMap& constellationIDToString,
                             const SkydelSignalIDToStringMap& signalIDToString,
                             const QHostAddress& address,
                             uint16_t port,
                             uint64_t rateMs,
                             bool enableNetworkLogging,
                             bool enableFileLogging,
                             const QString& logPath) :
  m_skydelNotifier(skydelNotifier),
  m_constellationIDToString(constellationIDToString),
  m_signalIDToString(signalIDToString),
  m_enableFileLogging(enableFileLogging),
  m_enableNetworkLogging(enableNetworkLogging),
  m_address(address),
  m_port(port),
  m_rateMs(rateMs),
  m_logPath(logPath),
  m_file(m_logPath + QDir::separator() + "raw_data_observer_output.csv")
{
  if (m_enableFileLogging)
  {
    if (!m_file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
      throw std::runtime_error("RawDataLogger - Can't open file.");
    }
  }

  m_skydelNotifier->notify("RawDataLogger initialized");
}

RawDataLogger::~RawDataLogger()
{
  emit lockConfiguration(false);
}

void RawDataLogger::connectToView(QWidget* view)
{
  if (auto* simpleLoggingView = dynamic_cast<SimpleLoggingView*>(view))
  {
    simpleLoggingView->lockConfiguration(true);
    connect(this, &RawDataLogger::lockConfiguration, simpleLoggingView, &SimpleLoggingView::lockConfiguration);
  }
}

void RawDataLogger::pushRawData(const TimedRawData& data)
{

  if ((data.elapsedTimeMs % m_rateMs) != 0)
  {
    return;
  }

  if (m_enableNetworkLogging)
  {
    QByteArray byteArray;
    QTextStream stream(&byteArray);
    streamData(data, stream);
    stream.flush();

    if (m_socket.writeDatagram(byteArray, m_address, m_port) == -1)
    {
      throw std::runtime_error(m_socket.errorString().toStdString().c_str());
    }
  }

  if (m_enableFileLogging)
  {
    QTextStream stream(&m_file);
    streamData(data, stream);

    if (stream.status() == QTextStream::WriteFailed)
    {
      throw std::runtime_error("RawDataLogger - Failed to write in file.");
    }
  }
}

void RawDataLogger::streamData(const SkydelRuntimeRawDataObserver::TimedRawData& data, QTextStream& stream)
{
  stream.setRealNumberPrecision(15);

  for (const auto& constellationRawData : data.constellationsRawData)
  {
    const auto constellationString = m_constellationIDToString.at(constellationRawData.id);
    for (const auto& svRawData : constellationRawData.svsRawData)
    {
      for (const auto& signalRawData : svRawData.signalsRawData)
      {
        stream << constellationString << ',' << svRawData.id << ',' << m_signalIDToString.at(signalRawData.id) << ','
               << signalRawData.svElapsedTimeMs << ',' << signalRawData.position.x << ',' << signalRawData.position.y
               << ',' << signalRawData.position.z << ',' << signalRawData.positionError.x << ','
               << signalRawData.positionError.y << ',' << signalRawData.positionError.z << ',' << signalRawData.range
               << ',' << signalRawData.pseudorange << ',' << signalRawData.adr << ',' << signalRawData.clockCorrection
               << ',' << signalRawData.clockNoise << ',' << signalRawData.deltaAf0 << ',' << signalRawData.deltaAf1
               << ',' << signalRawData.ionoCorrection << ',' << signalRawData.tropoCorrection << ','
               << signalRawData.psrOffset << ',' << signalRawData.receiverAntennaAzimuth << ','
               << signalRawData.receiverAntennaElevation << ',' << signalRawData.receiverAntennaGain << ','
               << signalRawData.svAntennaAzimuth << ',' << signalRawData.svAntennaElevation << ','
               << signalRawData.relativePowerLevel << ',' << signalRawData.receiverCarrierPhaseOffset << ','
               << signalRawData.satelliteCarrierPhaseOffset << ',' << signalRawData.gpsTow << ','
               << signalRawData.gpsWeekNumber << ',' << signalRawData.sbas << ',' << signalRawData.calibrationOffset
               << ',' << signalRawData.psrSatTime << '\n';
      }
    }
  }
}

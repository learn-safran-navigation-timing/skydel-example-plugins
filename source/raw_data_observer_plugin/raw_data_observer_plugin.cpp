#include "raw_data_observer_plugin.h"

#include "widgets/simple_logging_view.h"

void RawDataObserverPlugin::setConfiguration(const QString&, const QJsonObject& configuration)
{
  m_enableFileLogging = configuration["enableFileLogging"].toBool(false);
  m_enableNetworkLogging = configuration["enableNetworkLogging"].toBool(false);
  m_address = (configuration.contains("address") && configuration["address"].isString())
                ? QHostAddress(configuration["address"].toString())
                : QHostAddress(QHostAddress::LocalHost);
  m_port = static_cast<uint16_t>(configuration["port"].toInt(161));
  m_loggerRateMs = configuration["loggerRateMs"].toDouble(100);

  emit configurationChanged();
}

QJsonObject RawDataObserverPlugin::getConfiguration() const
{
  return {{"enableFileLogging", m_enableFileLogging},
          {"enableNetworkLogging", m_enableNetworkLogging},
          {"address", m_address.toString()},
          {"port", m_port},
          {"loggerRateMs", static_cast<qint64>(m_loggerRateMs)}};
}

SkydelWidgets RawDataObserverPlugin::createUI()
{
  auto view = new SimpleLoggingView;

  view->setEnableFileLogging(m_enableFileLogging);
  view->setEnableNetworkLogging(m_enableNetworkLogging);
  view->setAddress(m_address.toString());
  view->setPort(static_cast<int>(m_port));

  connect(view, &SimpleLoggingView::enableFileLoggingClicked, this, [this](bool checked) {
    m_enableFileLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &SimpleLoggingView::enableNetworkLoggingClicked, this, [this](bool checked) {
    m_enableNetworkLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &SimpleLoggingView::addressChanged, this, [this](const QString& address) {
    m_address = QHostAddress(address);
    m_skydelNotifier->setDirty();
  });

  connect(view, &SimpleLoggingView::portChanged, this, [this](int port) {
    m_port = static_cast<uint16_t>(port);
    m_skydelNotifier->setDirty();
  });

  connect(view, &SimpleLoggingView::loggerRateChanged, this, [this](uint64_t loggerRateMs) {
    m_loggerRateMs = loggerRateMs;
    m_skydelNotifier->setDirty();
  });

  connect(this, &RawDataObserverPlugin::configurationChanged, this, [this, view]() {
    view->setEnableFileLogging(m_enableFileLogging);
    view->setEnableNetworkLogging(m_enableNetworkLogging);
    view->setAddress(m_address.toString());
    view->setPort(static_cast<int>(m_port));
  });

  return {view};
}

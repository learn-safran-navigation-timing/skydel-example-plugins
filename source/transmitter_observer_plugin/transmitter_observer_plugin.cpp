#include "transmitter_observer_plugin.h"

#include "runtime_position_observer.h"
#include "runtime_transmitter_observer.h"
#include "transmitter_observer_view.h"

void TransmitterObserverPlugin::setConfiguration(const QString&, const QJsonObject& configuration)
{
  m_enableFileLogging = configuration["enableFileLogging"].toBool(false);
  m_enableNetworkLogging = configuration["enableNetworkLogging"].toBool(false);
  m_address = (configuration.contains("address") && configuration["address"].isString())
                ? QHostAddress(configuration["address"].toString())
                : QHostAddress(QHostAddress::LocalHost);
  m_port = static_cast<uint16_t>(configuration["port"].toInt(161));

  emit configurationChanged();
}

QJsonObject TransmitterObserverPlugin::getConfiguration() const
{
  return {{"enableFileLogging", m_enableFileLogging},
          {"enableNetworkLogging", m_enableNetworkLogging},
          {"address", m_address.toString()},
          {"port", m_port}};
}

SkydelWidgets TransmitterObserverPlugin::createUI()
{
  auto view = new TransmitterObserverView;

  view->setEnableFileLogging(m_enableFileLogging);
  view->setEnableNetworkLogging(m_enableNetworkLogging);
  view->setAddress(m_address.toString());
  view->setPort(static_cast<int>(m_port));

  connect(view, &TransmitterObserverView::enableFileLoggingClicked, [this](bool checked) {
    m_enableFileLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &TransmitterObserverView::enableNetworkLoggingClicked, [this](bool checked) {
    m_enableNetworkLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &TransmitterObserverView::addressChanged, [this](const QString& address) {
    m_address = QHostAddress(address);
    m_skydelNotifier->setDirty();
  });

  connect(view, &TransmitterObserverView::portChanged, [this](int port) {
    m_port = static_cast<uint16_t>(port);
    m_skydelNotifier->setDirty();
  });

  connect(this, &TransmitterObserverPlugin::configurationChanged, [this, view]() {
    view->setEnableFileLogging(m_enableFileLogging);
    view->setEnableNetworkLogging(m_enableNetworkLogging);
    view->setAddress(m_address.toString());
    view->setPort(static_cast<int>(m_port));
  });

  return {view};
}

SkydelRuntimeTransmitterObserver* TransmitterObserverPlugin::createRuntimeTransmitterObserver()
{
  if (!isEnabled())
    return nullptr;

  m_logger.reset(m_address, m_port, m_enableNetworkLogging, m_enableFileLogging, m_logPath);
  auto* txObserver = new RuntimeTransmitterObserver();

  connect(txObserver,
          &RuntimeTransmitterObserver::updateTransmitters,
          this,
          &TransmitterObserverPlugin::onNewTransmitterUpdate);
  connect(txObserver, &QObject::destroyed, this, &TransmitterObserverPlugin::onSimulationEnd);

  return txObserver;
}

SkydelRuntimePositionObserver* TransmitterObserverPlugin::createRuntimePositionObserver()
{
  if (!isEnabled())
    return nullptr;

  auto* positionObserver = new RuntimePositionObserver();

  connect(positionObserver,
          &RuntimePositionObserver::updatePosition,
          this,
          &TransmitterObserverPlugin::onNewPositionUpdate);

  return positionObserver;
}

void TransmitterObserverPlugin::onNewTransmitterUpdate(const SkydelRuntimeTransmitterObserver::TimedTransmitters& txs)
{
  m_logger.pushTransmitters(txs);
}

void TransmitterObserverPlugin::onNewPositionUpdate(const SkydelRuntimePositionObserver::TimedPosition& p)
{
  m_logger.pushPosition(p);
}

void TransmitterObserverPlugin::onSimulationEnd()
{
  m_logger.close();
}

bool TransmitterObserverPlugin::isEnabled() const
{
  return (m_enableFileLogging || m_enableNetworkLogging);
}

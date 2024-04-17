#include "position_observer_plugin.h"

#include "position_observer_view.h"

void PositionObserverPlugin::setConfiguration(const QString&, const QJsonObject& configuration)
{
  m_enableFileLogging = configuration["enableFileLogging"].toBool(false);
  m_enableNetworkLogging = configuration["enableNetworkLogging"].toBool(false);
  m_address = (configuration.contains("address") && configuration["address"].isString())
                ? QHostAddress(configuration["address"].toString())
                : QHostAddress(QHostAddress::LocalHost);
  m_port = static_cast<uint16_t>(configuration["port"].toInt(161));

  emit configurationChanged();
}

QJsonObject PositionObserverPlugin::getConfiguration() const
{
  return {{"enableFileLogging", m_enableFileLogging},
          {"enableNetworkLogging", m_enableNetworkLogging},
          {"address", m_address.toString()},
          {"port", m_port}};
}

SkydelWidgets PositionObserverPlugin::createUI()
{
  auto view = new PositionObserverView;

  view->setEnableFileLogging(m_enableFileLogging);
  view->setEnableNetworkLogging(m_enableNetworkLogging);
  view->setAddress(m_address.toString());
  view->setPort(static_cast<int>(m_port));

  connect(view, &PositionObserverView::enableFileLoggingClicked, [this](bool checked) {
    m_enableFileLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &PositionObserverView::enableNetworkLoggingClicked, [this](bool checked) {
    m_enableNetworkLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(view, &PositionObserverView::addressChanged, [this](const QString& address) {
    m_address = QHostAddress(address);
    m_skydelNotifier->setDirty();
  });

  connect(view, &PositionObserverView::portChanged, [this](int port) {
    m_port = static_cast<uint16_t>(port);
    m_skydelNotifier->setDirty();
  });

  connect(this, &PositionObserverPlugin::configurationChanged, [this, view]() {
    view->setEnableFileLogging(m_enableFileLogging);
    view->setEnableNetworkLogging(m_enableNetworkLogging);
    view->setAddress(m_address.toString());
    view->setPort(static_cast<int>(m_port));
  });

  return {view};
}

#include "hil_observer_plugin.h"

#include "hil_logger.h"
#include "hil_observer_view.h"

void HilObserverPlugin::setConfiguration(const QString&, const QJsonObject& configuration)
{
  m_enableFileLogging = configuration["enableFileLogging"].toBool(false);

  emit configurationChanged();
}

QJsonObject HilObserverPlugin::getConfiguration() const
{
  return {{"enableFileLogging", m_enableFileLogging}};
}

SkydelWidgets HilObserverPlugin::createUI()
{
  auto view = new HilObserverView;

  view->setEnableFileLogging(m_enableFileLogging);

  connect(view, &HilObserverView::enableFileLoggingClicked, [this](bool checked) {
    m_enableFileLogging = checked;
    m_skydelNotifier->setDirty();
  });

  connect(this, &HilObserverPlugin::configurationChanged, [this, view]() {
    view->setEnableFileLogging(m_enableFileLogging);
  });

  return {view};
}

SkydelRuntimeHilObserver* HilObserverPlugin::createRuntimeHilObserver()
{
  return m_enableFileLogging ? new HilLogger(m_logPath, m_enableFileLogging, m_skydelNotifier) : nullptr;
}

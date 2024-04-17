#pragma once

#include <QString>
#include <QWidget>

namespace Ui
{
class RapiPluginView;
}

class RapiPluginView : public QWidget
{
  Q_OBJECT

public:
  explicit RapiPluginView(QWidget* parent = nullptr);
  ~RapiPluginView();

  void setSimulatorState(const QString& state);

signals:
  void buttonUpdateClicked();
  void buttonPostSetterCommandClicked();

private:
  Ui::RapiPluginView* m_ui;
};

#pragma once

#include <QWidget>

namespace Ui
{
class SimpleLoggingView;
}

class QLabel;

class SimpleLoggingView : public QWidget
{
  Q_OBJECT

public:
  explicit SimpleLoggingView(QWidget* parent = nullptr);
  ~SimpleLoggingView();
  void setEnableFileLogging(bool enable);
  void setEnableNetworkLogging(bool enable);
  void setAddress(const QString& address);
  void setPort(int port);

public slots:
  void lockConfiguration(bool lock);

private slots:
  void changeRawRate();

signals:
  void enableFileLoggingClicked(bool checked);
  void enableNetworkLoggingClicked(bool checked);
  void addressChanged(const QString& address);
  void portChanged(int port);
  void loggerRateChanged(uint64_t loggerRateMs);

private:
  uint64_t m_loggerRateMs {100};
  Ui::SimpleLoggingView* m_ui;
};

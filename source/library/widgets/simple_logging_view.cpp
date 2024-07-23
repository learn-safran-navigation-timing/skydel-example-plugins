#include "simple_logging_view.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLabel>

#include "dialogs/duration_dialog.h"
#include "ui_simple_logging_view.h"

namespace
{
QString millisecondsToString(uint64_t milliseconds)
{
  int secondsInADay = 86400;
  int secondsInAnHour = 3600;
  int tempValue;

  QString out = "";

  int seconds = milliseconds / 1000;

  if (seconds >= secondsInADay)
  {
    tempValue = seconds / secondsInADay;
    seconds -= tempValue * secondsInADay;
    if (tempValue > 0)
    {
      out += QString::number(tempValue);
      out += tempValue > 1 ? " days " : " day ";
    }
  }
  if (seconds >= secondsInAnHour)
  {
    tempValue = seconds / secondsInAnHour;
    seconds -= tempValue * secondsInAnHour;
    if (tempValue > 0)
    {
      out += QString::number(tempValue);
      out += tempValue > 1 ? " hours " : " hour ";
    }
  }
  if (seconds >= 60)
  {
    tempValue = seconds / 60;
    seconds -= tempValue * 60;
    if (tempValue > 0)
    {
      out += QString::number(tempValue);
      out += tempValue > 1 ? " minutes " : " minute ";
    }
  }
  if (seconds > 0)
  {
    out += QString::number(seconds);
    out += seconds > 1 ? " seconds " : " second ";
  }
  tempValue = milliseconds % 1000;
  if (tempValue > 0)
  {
    out += QString::number(tempValue);
    out += tempValue > 1 ? " milliseconds" : " millisecond";
  }
  if (out == "")
  {
    out += "0 milliseconds";
  }
  return out;
}
} // namespace

SimpleLoggingView::SimpleLoggingView(QWidget* parent) : QWidget(parent), m_ui(new Ui::SimpleLoggingView)
{
  m_ui->setupUi(this);

  m_ui->rawRateButton->setText(millisecondsToString(m_loggerRateMs));

  connect(m_ui->rawRateButton, &QPushButton::clicked, this, &SimpleLoggingView::changeRawRate);
  connect(m_ui->fileLogging, &QCheckBox::clicked, this, &SimpleLoggingView::enableFileLoggingClicked);
  connect(m_ui->networkLogging, &QCheckBox::clicked, this, &SimpleLoggingView::enableNetworkLoggingClicked);
  connect(m_ui->address, &QLineEdit::textChanged, this, &SimpleLoggingView::addressChanged);
  connect(m_ui->portSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &SimpleLoggingView::portChanged);
}

SimpleLoggingView::~SimpleLoggingView()
{
  delete m_ui;
}

void SimpleLoggingView::setEnableFileLogging(bool enable)
{
  QSignalBlocker blocker {m_ui->fileLogging};
  m_ui->fileLogging->setChecked(enable);
}

void SimpleLoggingView::setEnableNetworkLogging(bool enable)
{
  QSignalBlocker blocker {m_ui->networkLogging};
  m_ui->networkLogging->setChecked(enable);
}

void SimpleLoggingView::setAddress(const QString& address)
{
  QSignalBlocker blocker {m_ui->address};
  m_ui->address->setText(address);
}

void SimpleLoggingView::setPort(int port)
{
  QSignalBlocker blocker {m_ui->portSpinBox};
  m_ui->portSpinBox->setValue(port);
}

void SimpleLoggingView::lockConfiguration(bool lock)
{
  setEnabled(!lock);
}

void SimpleLoggingView::changeRawRate()
{
  DurationDialog dlg(this);
  if (dlg.exec() == QDialog::Accepted)
  {
    m_loggerRateMs = dlg.durationMs();
    {
      QSignalBlocker blocker {m_ui->rawRateButton};
      m_ui->rawRateButton->setText(millisecondsToString(m_loggerRateMs));
    }
    emit loggerRateChanged(m_loggerRateMs);
  }
}

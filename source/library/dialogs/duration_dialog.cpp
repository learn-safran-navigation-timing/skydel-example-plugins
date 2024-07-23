#include "duration_dialog.h"

#include "ui_duration_dialog.h"

DurationDialog::DurationDialog(QWidget* parent) : QDialog(parent), m_ui(new Ui::DurationDialog)
{
  m_ui->setupUi(this);
}

DurationDialog::~DurationDialog()
{
  delete m_ui;
}

uint64_t DurationDialog::durationMs() const
{
  return (static_cast<uint64_t>(static_cast<uint32_t>(m_ui->spinBoxDays->value())) * 86400 +
          static_cast<uint32_t>(m_ui->spinBoxHours->value()) * 3600 +
          static_cast<uint32_t>(m_ui->spinBoxMinutes->value()) * 60 +
          static_cast<uint32_t>(m_ui->spinBoxSeconds->value())) *
           1000 +
         static_cast<uint32_t>(m_ui->spinBoxMilliseconds->value());
}

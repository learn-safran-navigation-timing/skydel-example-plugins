#pragma once

#include <QDialog>

namespace Ui
{
class DurationDialog;
}

class DurationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DurationDialog(QWidget* parent = nullptr);
  ~DurationDialog();

  uint64_t durationMs() const;

private:
  Ui::DurationDialog* m_ui;
};

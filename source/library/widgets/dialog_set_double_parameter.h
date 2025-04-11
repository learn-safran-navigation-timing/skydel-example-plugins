#pragma once

#include <QDialog>

class QLineEdit;
class QDialogButtonBox;

struct ParameterInfo
{
  QString name {};
  QString unit {};
  double min {std::numeric_limits<double>::lowest()};
  double max {std::numeric_limits<double>::max()};
  QString description {};
  double defaultValue = 0.0;
};

class DialogSetDoubleParameter : public QDialog
{
  Q_OBJECT

public:
  DialogSetDoubleParameter(const ParameterInfo& parameter, QWidget* parent = nullptr);

  double getValue() const;

private:
  void textEdited(const QString& newText, const ParameterInfo& parameterInfo);

  QLineEdit* m_lineEdit;
  QDialogButtonBox* m_buttonBox;
};

#pragma once

#include <QPushButton>

#include "dialog_set_double_parameter.h"

class SetDoubleParameterPushButton : public QPushButton
{
  Q_OBJECT

public:
  SetDoubleParameterPushButton(QWidget* parent = nullptr);

  void setCurrentValue(double defaultValue);
  double getCurrentValue();

  void setParameterInfo(const ParameterInfo& newParameterInfo, double currentValue);

signals:
  void valueChanged(double newValue);

private slots:
  void openDialog();

private:
  void updateVisual();

  ParameterInfo m_parameterInfo {};
};

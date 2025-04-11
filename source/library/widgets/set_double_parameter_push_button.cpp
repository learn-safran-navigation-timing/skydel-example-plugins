#include "set_double_parameter_push_button.h"

namespace
{
constexpr uint32_t MAX_BUTTON_WIDTH = 80;
constexpr uint32_t MAX_BUTTON_HEIGHT = 24;
} // namespace

SetDoubleParameterPushButton::SetDoubleParameterPushButton(QWidget* parent) : QPushButton(parent)
{
  setMinimumSize(MAX_BUTTON_WIDTH, MAX_BUTTON_HEIGHT);
  setMaximumSize(MAX_BUTTON_WIDTH, MAX_BUTTON_HEIGHT);
  connect(this, &QPushButton::clicked, this, &SetDoubleParameterPushButton::openDialog);
}

void SetDoubleParameterPushButton::setCurrentValue(double value)
{
  m_parameterInfo.defaultValue = value;
  updateVisual();
}

double SetDoubleParameterPushButton::getCurrentValue()
{
  return m_parameterInfo.defaultValue;
}

void SetDoubleParameterPushButton::setParameterInfo(const ParameterInfo& newParameterInfo, double currentValue)
{
  m_parameterInfo = newParameterInfo;
  setCurrentValue(currentValue);
}

void SetDoubleParameterPushButton::openDialog()
{
  DialogSetDoubleParameter dialog(m_parameterInfo, this);

  if (dialog.exec() == QDialog::Accepted)
  {
    auto newValue = dialog.getValue();
    setCurrentValue(newValue);
    emit valueChanged(newValue);
  }
}

void SetDoubleParameterPushButton::updateVisual()
{
  setText(QString::number(m_parameterInfo.defaultValue));
}

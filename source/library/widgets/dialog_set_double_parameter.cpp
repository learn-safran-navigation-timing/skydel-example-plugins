#include "dialog_set_double_parameter.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <ranges>

namespace
{
bool isInInclusiveRange(double value, const std::pair<double, double>& bounds) noexcept
{
  return bounds.first <= value && value <= bounds.second;
}
} // namespace

DialogSetDoubleParameter::DialogSetDoubleParameter(const ParameterInfo& parameter, QWidget* parent) :
  QDialog(parent),
  m_lineEdit(new QLineEdit()),
  m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this))
{
  setWindowTitle(parameter.title);

  QVBoxLayout* layout = new QVBoxLayout(this);

  m_lineEdit->setText(QString::number(parameter.defaultValue));

  connect(m_lineEdit, &QLineEdit::textChanged, [this, parameter](const QString& newText) {
    textEdited(newText, parameter);
  });

  QHBoxLayout* paramLayout = new QHBoxLayout();
  paramLayout->addWidget(new QLabel(parameter.name));
  paramLayout->addWidget(m_lineEdit);
  paramLayout->addWidget(new QLabel(parameter.unit));
  layout->addLayout(paramLayout);

  layout->addWidget(new QLabel("Min: " + QString::number(parameter.min) + " Max: " + QString::number(parameter.max)));
  layout->addSpacing(10);

  if (parameter.description.size() > 0)
  {
    layout->addWidget(new QLabel(parameter.description));
    layout->addSpacing(10);
  }

  layout->addWidget(m_buttonBox);

  connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void DialogSetDoubleParameter::showEvent(QShowEvent* event)
{
  QDialog::showEvent(event);
  m_lineEdit->setFocus();
}

void DialogSetDoubleParameter::textEdited(const QString& newText, const ParameterInfo& parameterInfo)
{
  bool isDouble;
  double v(newText.toDouble(&isDouble));
  bool ok = isDouble && isInInclusiveRange(v, {parameterInfo.min, parameterInfo.max});
  m_buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ok);
}

double DialogSetDoubleParameter::getValue() const
{
  return m_lineEdit->text().toDouble();
}

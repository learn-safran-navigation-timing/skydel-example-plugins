#include "info_button.h"

#include <QFile>

namespace
{
constexpr auto INFO_BUTTON_DEFAULT_SIZE_PX = 20;
constexpr auto INFO_BUTTON_STYLESHEET_TEMPLATE =
  "QPushButton {width: %1px; height: %1px; border: 0px; image: url(:/plugin_widgets/info-normal-20.png); }"
  "QPushButton:hover {image: url(:/plugin_widgets/info-hover-20.png);}"
  "QPushButton:pressed {image: url(:/plugin_widgets/info-click-20.png);}";
} // namespace

InfoButton::InfoButton(QWidget* parent) : InfoButton(INFO_BUTTON_DEFAULT_SIZE_PX, parent)
{
  Q_INIT_RESOURCE(resources);
}

InfoButton::InfoButton(int size, QWidget* parent) : QPushButton(parent)
{
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  setStyleSheet(QString(INFO_BUTTON_STYLESHEET_TEMPLATE).arg(QString::number(size)));
}

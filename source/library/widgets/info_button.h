#pragma once

#include <QPushButton>

class InfoButton : public QPushButton
{
public:
  InfoButton(QWidget* parent = nullptr);
  InfoButton(int size, QWidget* parent = nullptr);
};

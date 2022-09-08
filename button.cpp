#include "button.hpp"

#include <QKeyEvent>
#include <QDebug>

Button::Button(const QString& fileName, const QString& text, const QString& color,
               const QString& maskColor, bool isEnabled, QWidget* parent)
    : QPushButton(parent), _fileName(fileName), _color(color), _maskColor(maskColor)
{
    resetToDefault();

    this->setProperty("isEnabled", isEnabled);
    this->setText(text);
    this->setEnabled(isEnabled);
}

Button::Button(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {}

/**
 * @brief Button::changeIconColor
 *
 * Change button icon color.
 *
 * @param btn
 * @param fileName
 * @param color
 * @param maskColor
 * @param mode
 */
void Button::changeIconColor(Button* const btn, const QString& fileName,
                             const QString& color, const QString& maskColor,
                             Qt::MaskMode mode) const
{
    auto pixmap_ico = QPixmap(fileName);
    auto mask_ico = pixmap_ico.createMaskFromColor(maskColor, mode);
    pixmap_ico.fill(color);
    pixmap_ico.setMask(mask_ico);
    btn->setIcon(QIcon(std::move(pixmap_ico)));
}

/**
 * @brief Button::changeStyleButton
 *
 * Change the style of the button when hovering over it depending
 * on the passed element name and color.
 *
 * @param btn
 * @param objName
 * @param color
 */
void Button::changeStyleButton(Button* const btn, const QString& objName,
                               const QString color) const
{
    auto style = QString("Button#%1:hover {" \
                    "color: %2;" \
                    "background-color: #fff;" \
                    "}").arg(objName, color);
    btn->setStyleSheet(style);
}

/**
 * @brief Button::resetToDefault
 *
 * Resets button icon states to default.
 *
 * @param mode
 */
void Button::resetToDefault(Qt::MaskMode mode)
{
    QPixmap pixmap_ico(_fileName);
    auto mask_ico = pixmap_ico.createMaskFromColor(_maskColor, mode);
    pixmap_ico.fill(_color);
    pixmap_ico.setMask(mask_ico);
    this->setIcon(QIcon(std::move(pixmap_ico)));
}

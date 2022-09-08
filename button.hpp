#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QBitmap>

class Button : public QPushButton
{
    Q_OBJECT
public:
    Button(const QString& fileName, const QString& text, const QString& color,
           const QString& maskColor, bool isEnabled = false, QWidget* parent = nullptr);
    Button(const QString& text, QWidget* parent = nullptr);

    void changeIconColor(Button* const btn, const QString& fileName,
                         const QString& color, const QString& maskColor,
                         Qt::MaskMode mode = Qt::MaskOutColor) const;
    void changeStyleButton(Button* const btn, const QString& objName, const QString color) const;
    void resetToDefault(Qt::MaskMode mode = Qt::MaskOutColor);

private:
    QString _fileName;
    QString _color;
    QString _maskColor;
};

#endif // BUTTON_H

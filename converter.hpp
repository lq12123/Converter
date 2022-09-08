#ifndef CONVERTER_H
#define CONVERTER_H

#include <QWidget>
#include <QLabel>
#include <QPointer>
#include <QPushButton>

#include "button.hpp"

class Converter : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(NOTIFY change_color)
private:
    enum BtnTypes
    {
        UPLOAD_BTN,
        CLEAR_QUEUE_BTN,
        DOWNLOAD_ALL_BTN,
        LEFT_ARROW_BTN,
        RIGHT_ARROW_BTN
    };

protected:
    bool eventFilter(QObject* obj, QEvent* ev) override;

public:
    explicit Converter(QWidget *parent = nullptr);

protected:

signals:

private slots:
    void uploadFiles();

private:
    QVector<QPointer<Button> > _btns;
    QVector<QPointer<QLabel> > _labels;
};

#endif // CONVERTER_H

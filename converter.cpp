#include "converter.hpp"
#include "loader.hpp"

#include <QGridLayout>
#include <QFile>

#include <QDebug>
#include <QGuiApplication>
#include <QFileDialog>

Converter::Converter(QWidget *parent)
    : QWidget{parent}
{
    // Styles
    QFile fcss(":/css/style.css");
    if (fcss.open(QIODevice::ReadOnly))
    {
        setStyleSheet(fcss.readAll());
        fcss.close();
    }

    // Elements
    auto base_layout = new QGridLayout;
    base_layout->setSizeConstraint(QLayout::SetFixedSize);

    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    auto upload_btn = new Button(":/icons/circle-arrow-up-solid.svg", tr("UPLOAD FILES"), "white", "black", true);
    auto clear_queue_btn = new Button(":/icons/circle-xmark-solid.svg", tr("CLEAR QUEUE"), "white", "black");
    auto download_all_btn = new Button(":/icons/circle-arrow-down-solid.svg", tr("DOWNLOAD ALL"), "white", "black");
    auto left_arrow_btn = new Button(tr("\u2bc7"));
    auto right_arrow_btn = new Button(tr("\u2bc8"));

    upload_btn->setObjectName("uploadBtn");
    clear_queue_btn->setObjectName("clearQueueBtn");
    download_all_btn->setObjectName("downloadAllBtn");

    auto btn_font = upload_btn->font();
    upload_btn->setFont(btn_font);
    clear_queue_btn->setFont(btn_font);

    base_layout->addWidget(upload_btn, 0, 1, 1, 1);
    base_layout->addWidget(clear_queue_btn, 0, 2, 1, 1);
    base_layout->addWidget(download_all_btn, 2, 1, 1, 2);
    base_layout->addWidget(left_arrow_btn, 1, 0, 1, 1);
    base_layout->addWidget(right_arrow_btn, 1, 3, 1, 1);

    _btns.push_back(std::move(upload_btn));
    _btns.push_back(std::move(clear_queue_btn));
    _btns.push_back(std::move(download_all_btn));
    _btns.push_back(std::move(left_arrow_btn));
    _btns.push_back(std::move(right_arrow_btn));

    // Labels settings
    auto drop_field = new QLabel(tr("Drop Your Files Here"));
    auto cnt_files = new QLabel("0");

    left_arrow_btn->setObjectName("arrow");
    right_arrow_btn->setObjectName("arrow");

    drop_field->setObjectName("dropField");

    drop_field->setAlignment(Qt::AlignCenter);
    drop_field->setMinimumSize(.7*drop_field->width(), 11*drop_field->minimumSizeHint().height());

    cnt_files->setProperty("isEnabled", false);
    cnt_files->setObjectName("fileCounter");

    base_layout->addWidget(drop_field, 1, 1, 1, 2, Qt::AlignCenter);
    base_layout->addWidget(cnt_files, 2, 2, 1, 1, Qt::AlignRight | Qt::AlignTop);

    _labels.push_back(std::move(drop_field));

    Loader::loadFont(":/fonts/Inter-Medium.ttf");
    setLayout(base_layout);
    setWindowTitle(tr("Converter"));

    upload_btn->installEventFilter(this);
    clear_queue_btn->installEventFilter(this);
    download_all_btn->installEventFilter(this);


    connect(upload_btn, &Button::clicked, this, &Converter::uploadFiles);
}

/**
 * @brief Converter::uploadFiles
 * Receiving files uploaded by the user.
 */
void Converter::uploadFiles()
{
    auto home_path = qgetenv("HOMEPATH");
    auto filenames = QFileDialog::getOpenFileNames(
                this, tr("Upload Files"),
                QString("c:%1").arg(QString::fromLocal8Bit(home_path)),
                tr("Document files (*.djvu *.doc *.docx *.pdf);;All Files (*.*)"));

    for (auto&& file : filenames)
        qDebug() << file;
}

/**
 * @brief Converter::eventFilter
 *
 * Handled click events on the "upload files", "clear queue", "download all".
 *
 * @param obj
 * @param ev
 * @return
 */
bool Converter::eventFilter(QObject* obj, QEvent* ev)
{
    auto btn = qobject_cast<Button*>(obj);
    if (ev->type() == QEvent::HoverEnter && btn->isEnabled())
    {
        btn->setCursor(Qt::PointingHandCursor);

        if (obj == _btns[Converter::UPLOAD_BTN])
        {
            btn->changeIconColor(btn, ":/icons/circle-arrow-up-solid.svg", "#116EBF", "black");
            btn->changeStyleButton(btn, btn->objectName(), "#116EBF");
        } else if (obj == _btns[Converter::CLEAR_QUEUE_BTN])
        {
            btn->changeIconColor(btn, ":/icons/circle-xmark-solid.svg", "#FC3B3B", "black");
            btn->changeStyleButton(btn, btn->objectName(), "#FC3B3B");
        } else if (obj == _btns[Converter::DOWNLOAD_ALL_BTN])
        {
            btn->changeIconColor(btn, ":/icons/circle-arrow-down-solid.svg", "#B0B0B0", "black");
            btn->changeStyleButton(btn, btn->objectName(), "#B0B0B0");
        }

        return 1;
    } else if (ev->type() == QEvent::HoverLeave)
    {
        auto btn = qobject_cast<Button*>(obj);
        btn->resetToDefault();

        return 1;
    }

    return QWidget::eventFilter(obj, ev);
}

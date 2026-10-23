#include "chesswidget.h"
#include "ui_chesswidget.h"
#include <QSignalMapper>
#include <QPushButton>
#include <QRegExp>
#include <QDebug>

ChessWidget::ChessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    signalMapper(new QSignalMapper(this))
{
    ui->setupUi(this);

    // соединение кнопок с signalMapper
    for (int i = 0; i < 64; ++i) {
        // формирование имени кнопки как в ui файле
        QString buttonName = QString("pushButton_%1").arg(i + 1);
        // поиск кнопок по имени
        QPushButton *button = this->findChild<QPushButton *>(buttonName);

        if (button) {
            // cоединение сигнала нажатия кнопки с map
            connect(button, &QPushButton::clicked, signalMapper, QOverload<>::of(&QSignalMapper::map));
            // связывание кнопкис её индексом
            signalMapper->setMapping(button, i);
        }
    }
    // соединение сигнала mapped с методом handleButtonClick
    connect(signalMapper, QOverload<int>::of(&QSignalMapper::mapped), this, &ChessWidget::handleButtonClick);
}

ChessWidget::~ChessWidget()
{
    delete ui;
}

// слот для обработки нажатий на кнопки
void ChessWidget::handleButtonClick(int buttonIndex)
{
    // вычисление индексов кнопок
    int row = buttonIndex / 8;
    int col = buttonIndex % 8;

    qDebug() << "Нажата кнопка с координатами:" << (row + 1) << (col + 1);

    // сигнал с координатами
    emit buttonClicked(row, col);
}

// метод для получения изображения и отображения его на кнопке
void ChessWidget::setImageOnButton(int buttonIndex, const QString &imagePath)
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));

    if (button) {
        // получение текущего стиля кнопки
        QString currentStyle = button->styleSheet();

        // добавление нового изображения к текущему стилю
        QString newStyle = QString("%1 border-image: url(%2);").arg(currentStyle).arg(imagePath);

        // установка нового стиля
        button->setStyleSheet(newStyle);
    }
}

// метод для удаления изображения с кнопки
void ChessWidget::removeImageFromButton(int buttonIndex)
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));

    if (button) {
        // получение текущего стиля кнопки
        QString currentStyle = button->styleSheet();

        // извлечение цвет фона, чтобы не теярлось
        QRegExp bgColorRegex("background-color: ([^;]+);");
        QString bgColor;
        if (bgColorRegex.indexIn(currentStyle) != -1) {
            bgColor = bgColorRegex.cap(1);
        }

        // установка нового стиля без изображения
        button->setStyleSheet(QString("background-color: %1;").arg(bgColor));
    }
}

// метод для получения изображения с кнопки
QString ChessWidget::getImageOnButton(int buttonIndex) const
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));

    if (button) {
        // получение текущего изображения
        QString styleSheet = button->styleSheet();
        QRegExp regex("border-image: url\\(([^)]+)\\);");
        if (regex.indexIn(styleSheet) != -1) {
            return regex.cap(1);
        }
    }
    return "";
}


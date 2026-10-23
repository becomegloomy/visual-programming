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

    // Соединение кнопок с signalMapper
    for (int i = 0; i < 64; ++i) {
        // Формирование имени кнопки как в ui файле
        QString buttonName = QString("pushButton_%1").arg(i + 1);
        // Поиск кнопок по имени
        QPushButton *button = this->findChild<QPushButton *>(buttonName);

        if (button) {
            // Соединение сигнала нажатия кнопки с map
            connect(button, &QPushButton::clicked, signalMapper, QOverload<>::of(&QSignalMapper::map));
            
// Связывание кнопки с её индексом
            signalMapper->setMapping(button, i);
        }
    }
    // Соединение сигнала mapped с методом handleButtonClick
    connect(signalMapper, QOverload<int>::of(&QSignalMapper::mapped), this, &ChessWidget::handleButtonClick);
}

ChessWidget::~ChessWidget()
{
    delete ui;
}

// Слот для обработки нажатий на кнопки
void ChessWidget::handleButtonClick(int buttonIndex)
{
    // Вычисление индексов кнопок
    int row = buttonIndex / 8;
    int col = buttonIndex % 8;
    qDebug() << "Нажата кнопка с координатами:" << (row + 1) << (col + 1);

    // Сигнал с координатами
    emit buttonClicked(row, col);
}

// Метод для получения изображения и отображения его на кнопке
void ChessWidget::setImageOnButton(int buttonIndex, const QString &imagePath)
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));

    if (button) {
        // Получение текущего стиля кнопки
        QString currentStyle = button->styleSheet();

        // Добавление нового изображения к текущему стилю
        QString newStyle = QString("%1 border-image: url(%2);").arg(currentStyle).arg(imagePath);

        // Установка нового стиля
        button->setStyleSheet(newStyle);
    }
}
// Метод для удаления изображения с кнопки
void ChessWidget::removeImageFromButton(int buttonIndex)
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));

    if (button) {
        // Получение текущего стиля кнопки
        QString currentStyle = button->styleSheet();

        // Извлечение цвет фона, чтобы не терялось
        QRegExp bgColorRegex("background-color: ([^;]+);");
        QString bgColor;
        
if (bgColorRegex.indexIn(currentStyle) != -1) {
            bgColor = bgColorRegex.cap(1);
        }

        // Установка нового стиля без изображения
        button->setStyleSheet(QString("background-color: %1;").arg(bgColor));
    }
}

// Метод для получения изображения с кнопки
QString ChessWidget::getImageOnButton(int buttonIndex) const
{
    QPushButton *button = this->findChild<QPushButton *>(QString("pushButton_%1").arg(buttonIndex + 1));
    if (button) {
        // Получение текущего изображения
        QString styleSheet = button->styleSheet();
        QRegExp regex("border-image: url\\(([^)]+)\\);");
        if (regex.indexIn(styleSheet) != -1) {
            return regex.cap(1);
        }
    }
    return "";
}

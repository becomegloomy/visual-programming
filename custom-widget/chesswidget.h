#ifndef CHESSWIDGET_H
#define CHESSWIDGET_H

#include <QWidget>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE

class ChessWidget : public QWidget
{
    Q_OBJECT

public:
    
explicit ChessWidget(QWidget *parent = nullptr);
    ~ChessWidget();
    // Метод для получения изображения и отображения его на кнопке
    void setImageOnButton(int buttonIndex, const QString &imagePath);

    // Метод для удаления изображения с кнопки
    void removeImageFromButton(int buttonIndex);

    // Метод для получения изображения с кнопки
    QString getImageOnButton(int buttonIndex) const;

signals:
    // Сигнал с координатами нажатой кнопки
    void buttonClicked(int row, int col);

private slots:
    // Слот для обработки нажатий на кнопки
    void handleButtonClick(int buttonIndex);

private:
    Ui::Form *ui;
    QSignalMapper *signalMapper; // Для управления сигналами
};

#endif // CHESSWIDGET_H

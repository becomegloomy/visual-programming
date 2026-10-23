#include <QApplication>
#include "chesswidget.h"
#include <QString>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChessWidget chessWidget;
    chessWidget.setWindowTitle("Chess");
    chessWidget.resize(717, 709);
    chessWidget.show();

    // переменные для отслеживания состояния (кнопки и изображения на ней)
    int firstButtonIndex = -1;
    QString firstButtonImage = "";

    // связывание сигнала нажатой кнопки с обработчиком
    QObject::connect(&chessWidget, &ChessWidget::buttonClicked, [&chessWidget, &firstButtonIndex, &firstButtonImage](int row, int col) {
        // вычисление индекса кнопки
        int buttonIndex = row * 8 + col;

        // проверка повторного нажатия одной и той же кнопки
        if (buttonIndex == firstButtonIndex)
            return;

        // получение изображения из первой нажатой кнопки
        if (firstButtonIndex == -1) {
            firstButtonIndex = buttonIndex;
            firstButtonImage = chessWidget.getImageOnButton(firstButtonIndex);
        }
        else { // нажатие на вторую кнопку (для передачи изображения в нее)
            // получение изображения на второй кнопке для избежания дальнейшей ошибки
            QString secondButtonImage = chessWidget.getImageOnButton(buttonIndex);
            if (!firstButtonImage.isEmpty()) {

                // если на второй кнопке было изображение, удаление его
                if (!secondButtonImage.isEmpty())
                    chessWidget.removeImageFromButton(buttonIndex);

                // устанавка изображения на вторую кнопку
                chessWidget.setImageOnButton(buttonIndex, firstButtonImage);
                // удаляение изображения с первой кнопки
                chessWidget.removeImageFromButton(firstButtonIndex);
            }

            // сбрасывание состояния
            firstButtonIndex = -1;
            firstButtonImage.clear();
        }
    });

    return app.exec();
}

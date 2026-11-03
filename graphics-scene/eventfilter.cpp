#include "eventfilter.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

EventFilter::EventFilter(QObject *parent) : QObject(parent) {}

bool EventFilter::eventFilter(QObject *watched, QEvent *event) {
    // Преобразование объекта в указатель на QGraphicsScene
    auto *scene = dynamic_cast<QGraphicsScene *>(watched);
    // Если объект не является сценой, то передается в стандартный механизм обработки событий
    if (!scene)
        return QObject::eventFilter(watched, event);
    // Обработка нажатия левой кнопки мыши
    if (event->type() == QEvent::GraphicsSceneMousePress) { // Проверка на клик
        auto *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event); // Преобразование события
        QGraphicsItem *item = scene->itemAt(mouseEvent->scenePos(), QTransform()); // Получение объекта на сцене, на котором был клик
        // Выделение объекта, если нажата левая кнопка мыши
        if (item && mouseEvent->button() == Qt::LeftButton)
            item->setSelected(true);
    }
    // Обработка передвижения мыши
    if (event->type() == QEvent::GraphicsSceneMouseMove) {
        auto *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        QGraphicsItem *item = scene->focusItem(); // Получение объекта на сцене, который выбран для взаимодействия
        // Изменение позиции объекта на основе разницы между текущими и предыдущими координатами мыши
        if (item)
            item->setPos(item->pos() + mouseEvent->scenePos() - mouseEvent->lastScenePos());
    }
    // Обработка отпуска левой кнопки мыши
    if (event->type() == QEvent::GraphicsSceneMouseRelease) {
        auto *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        QGraphicsItem *item = scene->focusItem();
        if (item && mouseEvent->button() == Qt::LeftButton)
            item->setSelected(false);
    }

    return QObject::eventFilter(watched, event);
}

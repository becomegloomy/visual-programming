#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

// Класс класс для фильтрации событий
class EventFilter : public QObject {
    Q_OBJECT

public:
    explicit EventFilter(QObject *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void itemMoved(QGraphicsItem *item);
};

#endif // EVENTFILTER_H

#ifndef PRINTQUEUEMODEL_H
#define PRINTQUEUEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "PrintJob.h"

// Модель для очереди заданий на печать
class PrintQueueModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit PrintQueueModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addJob(const PrintJob& job);
    void removeJob(int index);
    void updateJob(int index, const PrintJob& job);
    const PrintJob& getJob(int index) const;

private:
    QList<PrintJob> jobs;
};

#endif // PRINTQUEUEMODEL_H

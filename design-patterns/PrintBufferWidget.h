#ifndef PRINTBUFFERWIDGET_H
#define PRINTBUFFERWIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QRandomGenerator>
#include "PrintQueueModel.h"

namespace Ui {
class PrintBufferWidget;
}

class PrintBufferWidget : public QMainWindow {
    Q_OBJECT

public:
    explicit PrintBufferWidget(QWidget* parent = nullptr);
    ~PrintBufferWidget();

private slots:
    void startPrinting();
    void processPrintJobs();

private:
    Ui::PrintBufferWidget* ui;
    QTimer* timer;
    PrintQueueModel* pendingModel;
    PrintQueueModel* completedModel;
    PrintQueueModel* rejectedModel;
    int nextJobId;
    int startJobCount;
    int printSpeed;
    int maxQueueSize;
    double addJobProbability;
    void initializeModels();
    void addStartJobs();
    void addRandomJob();
    QString RandomFileName() const;
};

#endif // PRINTBUFFERWIDGET_H

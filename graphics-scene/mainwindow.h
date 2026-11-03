#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>
#include "eventfilter.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addCapybara();
    void addSquare();
    void addLogo();
    void deleteItem();

private:
    Ui::MainWindow *ui;
    EventFilter *eventFilter;
    QGraphicsScene *scene;
    QMap<QString, int> objectCounter;
};

#endif // MAINWINDOW_H

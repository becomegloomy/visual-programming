#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

// Слот для добавления новой строки в таблицу данных
void MainWindow::slot1()
{
    // Для хранения информации из строки ввода
    QString text1 = ui->lineEdit->text().trimmed();
    QString text2 = ui->lineEdit_2->text().trimmed();

    // Проверка на пустое поле
    if (text1.isEmpty() || text2.isEmpty()) {
        return;
    }

    // Добавление новой строки в таблицу данных
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    // Добавление введенной информации в нее
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(text1));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(text2));

    // Очищение строки ввода
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

// Слот для удаления последней строки в таблице данных
void MainWindow::slot2()
{
    // Определение кол-ва строк в таблице
    int rowCount = ui->tableWidget->rowCount();

    // Проверка на пустую таблицу
    if (rowCount > 0) {
        // Удаляние строки
        ui->tableWidget->removeRow(rowCount - 1);
    }
}

// Слот для очищения всей таблицы данных
void MainWindow::slot3()
{
    ui->tableWidget->clearContents(); // Очистка всех данных
    ui->tableWidget->setRowCount(0);  // Удаление строк
}

// Слот для добавления новой таблицы
void MainWindow::slot4()
{
    // Поиск папки "Таблицы" в иерархии
    QTreeWidgetItem* tablesFolder = ui->treeWidget->findItems("Таблицы", Qt::MatchExactly | Qt::MatchRecursive).first();

    if (tablesFolder) {
        // Создание названия новой таблицы
        int tableCount = tablesFolder->childCount();
        QString newTableName = QString("Таблица_%1").arg(tableCount + 1);

        // Добавление таблицы
        QTreeWidgetItem* newTableItem = new QTreeWidgetItem(tablesFolder, QStringList() << newTableName);
        tablesFolder->addChild(newTableItem);

        // Обновление иерархии
        ui->treeWidget->expandItem(tablesFolder);
    }
}

// Слот для удаления последней таблицы в папке
void MainWindow::slot5()
{
    QTreeWidgetItem* tablesFolder = ui->treeWidget->findItems("Таблицы", Qt::MatchExactly | Qt::MatchRecursive).first();
    // Поиск последнего элемента в папке
    if (tablesFolder) {
        int tableCount = tablesFolder->childCount();
        if (tableCount > 0) {
            QTreeWidgetItem* lastTableItem = tablesFolder->child(tableCount - 1);
            // Удаление таблицы
            delete lastTableItem;
        }
    }
}









#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QTreeWidget>
#include <QSplitter>
#include <QMap>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent), rowCounter(0) {
        setWindowTitle("Администратор СУБД");

        // Основной виджет
        QWidget *centralWidget = new QWidget(this);
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

        // Разделитель между панелями
        QSplitter *splitter = new QSplitter(this);

        // Левая панель с иерархией
        fileTree = new QTreeWidget(this);
        fileTree->setHeaderLabel("");

        // Корневой элемента иерархии
        QTreeWidgetItem *sqlDatabase = new QTreeWidgetItem(fileTree, QStringList("SQL Database"));
        sqlDatabase->setExpanded(true);

        // Дочерние элементы
        root = new QTreeWidgetItem(sqlDatabase, QStringList("Таблицы"));
        root->setExpanded(true);
        new QTreeWidgetItem(sqlDatabase, QStringList("Представления"));
        new QTreeWidgetItem(sqlDatabase, QStringList("Индексы"));
        new QTreeWidgetItem(sqlDatabase, QStringList("Последовательности"));
        new QTreeWidgetItem(sqlDatabase, QStringList("Триггеры таблиц"));
        new QTreeWidgetItem(sqlDatabase, QStringList("Типы данных"));

        // Правая панель с таблицей данных
        QWidget *rightWidget = new QWidget(this);
        QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

        // Панель для ввода данных
        QHBoxLayout *inputLayout = new QHBoxLayout();
        QLabel *dataLabel = new QLabel("Введите название:", this);
        dataInput = new QLineEdit(this);
        QLabel *typeLabel = new QLabel("Введите тип данных:", this);
        typeInput = new QLineEdit(this);

        // Создание кнопок
        addButton = new QPushButton("Добавить в базу данных", this);
        addButton->setEnabled(false);  // Изначально кнопка отключена, т.к. нет таблиц
        QPushButton *removeLastRowButton = new QPushButton("Удалить последнюю строку", this);

        // Добавление созданных кнопок и полей
        // Вертикальный компановщик кнопок
        QVBoxLayout *buttonLayout = new QVBoxLayout();
        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeLastRowButton);
        inputLayout->addWidget(dataLabel);
        inputLayout->addWidget(dataInput);
        inputLayout->addWidget(typeLabel);
        inputLayout->addWidget(typeInput);
        inputLayout->addLayout(buttonLayout);
        rightLayout->addLayout(inputLayout);

        // Таблица данных
        tableWidget = new QTableWidget(0, 3, this);
        tableWidget->setHorizontalHeaderLabels({"Название", "Тип", "Описание"});
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        rightLayout->addWidget(tableWidget);

        // Добавление созданных панелей между разделителем
        splitter->addWidget(fileTree);
        splitter->setSizes(QList<int>() << 160 << 500);
        splitter->addWidget(rightWidget);

        mainLayout->addWidget(splitter);
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);

        // Создание меню
        QMenuBar *menuBar = new QMenuBar(this);
        setMenuBar(menuBar);
        QMenu *editMenu = new QMenu("Изменить", menuBar);
        menuBar->addMenu(editMenu);

        //Создание действий и их добавление
        QAction *addTableAction = new QAction("Добавить новую таблицу", this);
        QAction *removeTableAction = new QAction("Удалить таблицу", this);
        QAction *clearAction = new QAction("Очистить таблицу", this);
        editMenu->addAction(addTableAction);
        editMenu->addAction(removeTableAction);
        editMenu->addAction(clearAction);

        // Подключение сигналов и слотов
        connect(addButton, &QPushButton::clicked, this, &MainWindow::addData);
        connect(clearAction, &QAction::triggered, this, &MainWindow::clearTable);
        connect(addTableAction, &QAction::triggered, this, &MainWindow::addTable);
        connect(removeTableAction, &QAction::triggered, this, &MainWindow::removeTable);
        connect(fileTree, &QTreeWidget::itemClicked, this, &MainWindow::loadTable);
        connect(removeLastRowButton, &QPushButton::clicked, this, &MainWindow::removeLastRow);
    }

private slots:
    //Добавление строки в таблицу
    void addData() {
        if (!dataInput->text().isEmpty() && !typeInput->text().isEmpty()) {
            tableWidget->insertRow(rowCounter);
            tableWidget->setItem(rowCounter, 0, new QTableWidgetItem(dataInput->text()));
            tableWidget->setItem(rowCounter, 1, new QTableWidgetItem(typeInput->text()));
            tableWidget->setItem(rowCounter, 2, new QTableWidgetItem(""));
            dataInput->clear();
            typeInput->clear();
            rowCounter++;
        }
    }

    // Очистка всей таблицы
    void clearTable() {
        tableWidget->clearContents();
        tableWidget->setRowCount(0);
        rowCounter = 0;
    }

    // Добавление новой таблицы
    void addTable() {
        bool flag;
        QString tableName = QInputDialog::getText(this, "Добавить таблицу", "Название таблицы:", QLineEdit::Normal, "", &flag);
        if (flag && !tableName.isEmpty()) {
            if (tableData.contains(tableName)) {
                QMessageBox::warning(this, "Ошибка", "Таблица уже существует");
                return;
            }
            new QTreeWidgetItem(root, QStringList(tableName));
            tableData[tableName] = {};
            addButton->setEnabled(true);
        }
    }

    // Удаление таблицы
    void removeTable() {
        QTreeWidgetItem *selectedItem = fileTree->currentItem();
        if (selectedItem && selectedItem->parent() == root) {
            QString tableName = selectedItem->text(0);
            if (tableName == currentTableName) {
                clearTable();
                currentTableName.clear();
            }
            delete selectedItem;
            tableData.remove(tableName);

            // Отключение кнопки, если таблиц нет
            if (tableData.isEmpty()) {
                addButton->setEnabled(false);
            }
        }
    }

    // Сохранение данных таблицы
    void saveTableData(const QString &tableName) {
        QList<QStringList> data;
        for (int row = 0; row < tableWidget->rowCount(); ++row) {
            QStringList rowData;
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                rowData.append(tableWidget->item(row, col)->text());
            }
            data.append(rowData);
        }
        tableData[tableName] = data;
    }

    // Загрузка сохраненных данных в таблицу
    void loadTable(QTreeWidgetItem *item, int column) {
        // Игнорирование корневого элемена
        if (item->parent() == nullptr) return;
        QString tableName = item->text(0);

        // Сохранение текущих данных
        if (!currentTableName.isEmpty()) {
            saveTableData(currentTableName);
        }

        // Загрузка данных новой таблицы
        clearTable();
        currentTableName = tableName;
        if (tableData.contains(tableName)) {
            const auto &data = tableData[tableName];
            for (const QStringList &rowData : data) {
                int row = tableWidget->rowCount();
                tableWidget->insertRow(row);
                for (int col = 0; col < rowData.size(); ++col) {
                    tableWidget->setItem(row, col, new QTableWidgetItem(rowData[col]));
                }
            }
            rowCounter = tableWidget->rowCount();
        }
    }

    // Удаление последней строки таблицы
    void removeLastRow() {
        if (rowCounter > 0) {
            tableWidget->removeRow(rowCounter - 1);
            rowCounter--;
        }
    }

private:
    QLineEdit *dataInput;
    QLineEdit *typeInput;
    QTableWidget *tableWidget;
    QTreeWidget *fileTree;
    QTreeWidgetItem *root;
    QPushButton *addButton;
    int rowCounter;
    QString currentTableName;
    QMap<QString, QList<QStringList>> tableData;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(1100, 600);
    mainWindow.show();
    return app.exec();
}

// Подключение файла для обеспечения работы сигналов и слотов
#include "main.moc"

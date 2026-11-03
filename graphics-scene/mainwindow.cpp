#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), eventFilter(new EventFilter(this)) {
    ui->setupUi(this);
    scene = new QGraphicsScene(this);  // Создание сцены
    ui->graphicsView->setScene(scene); // Связка сцены с QGraphicsView
    scene->installEventFilter(eventFilter); // Установка фильтра событий на сцену
    // Подключение кнопок
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addCapybara);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::addSquare);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::addLogo);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::deleteItem);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Метод для добавления изображения капибары на сцену
void MainWindow::addCapybara() {
    // Счетчик для нумерации объектов
    int count = objectCounter["Капибара"] + 1;
    objectCounter["Капибара"] = count;

    QGraphicsPixmapItem *capybara = new QGraphicsPixmapItem(); // Создание графического объекта
    QPixmap pixmap(170, 120);  // Создание изображения с размером
    pixmap.fill(Qt::transparent); // Прозрачность
    QPainter painter(&pixmap); // Создание объекта для рисования на изображении
    // Рисование
    painter.setBrush(QColor(139, 69, 19)); // Цвет заливки
    painter.setPen(Qt::black); // Цвет линии
    // Голова
    QPolygonF head;
    head << QPointF(0, 70)
         << QPointF(110, 30)
         << QPointF(166, 45)
         << QPointF(162, 119)
         << QPointF(0, 119);
    painter.drawPolygon(head);
    // Ухо
    painter.drawPie(140, 20, 20, 40, 16 * -8, 16 * 180);
    // Глаз
    painter.setPen(QPen(Qt::black, 4));
    painter.drawArc(100, 60, 20, 10, 0, 16 * 180);
    // Рот
    painter.drawArc(-10, 113, 20, 5, 16 * 270, 16 * 90);
    // Нос
    painter.drawEllipse(7, 80, 3, 3);

    capybara->setPixmap(pixmap); // Установка изображения в объект
    capybara->setFlag(QGraphicsItem::ItemIsMovable); // Флаг для возможности перемещения объекта
    capybara->setFlag(QGraphicsItem::ItemIsSelectable); // Флаг для возможности выделения/выбора объекта
    capybara->setData(0, "Капибара_" + QString::number(count)); // Добавление имени объекту
    scene->addItem(capybara); // Добавление объекта на сцену
    ui->listWidget->addItem("Капибара_" + QString::number(count)); // Добавление объекта в список
}

// Метод для добавления квадрата на сцену
void MainWindow::addSquare() {
    int count = objectCounter["Квадрат"] + 1;
    objectCounter["Квадрат"] = count;
    // Создание квадрата
    QGraphicsRectItem *square = new QGraphicsRectItem(0, 0, 100, 100);
    square->setBrush(Qt::red);
    square->setFlag(QGraphicsItem::ItemIsMovable);
    square->setFlag(QGraphicsItem::ItemIsSelectable);
    square->setData(0, "Квадрат_" + QString::number(count));
    // Создание подписи
    QGraphicsTextItem *text = new QGraphicsTextItem("Синий", square); // Дочерний элемент квадрата
    text->setPos(25, 110);  // Перемещение относительно квадрата
    text->setDefaultTextColor(Qt::blue); // Цвет

    scene->addItem(square);
    ui->listWidget->addItem("Квадрат_" + QString::number(count));
}

// Метод для добавления логотипа на сцену
void MainWindow::addLogo() {
    int count = objectCounter["Логотип"] + 1;
    objectCounter["Логотип"] = count;

    QGraphicsPixmapItem *logo = new QGraphicsPixmapItem();
    QPixmap pixmap(":/new/prefix1/i5.png"); // Загрузка изображения из файла
    // Масштабирование
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio);
    logo->setPixmap(scaledPixmap);

    logo->setFlag(QGraphicsItem::ItemIsMovable);
    logo->setFlag(QGraphicsItem::ItemIsSelectable);
    logo->setData(0, "Логотип_" + QString::number(count));
    scene->addItem(logo);
    ui->listWidget->addItem("Логотип_" + QString::number(count));
}

// Метод для удаления объектов со сцены
void MainWindow::deleteItem() {
    // Получение выбранного элемента из списка
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if (!selectedItems.isEmpty()) {
        // Удаление элемента из списка
        QListWidgetItem *item = selectedItems.first();
        QString itemName = item->text();
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
        // Поиск выбранного элемента на сцене
        QGraphicsItem *sceneItem = nullptr;
        foreach (QGraphicsItem *obj, scene->items()) {
            if (obj->data(0).toString() == itemName) {
                sceneItem = obj;
                break;
            }
        }
        // Удаление объекта со сцены
        if (sceneItem) {
            scene->removeItem(sceneItem);
            delete sceneItem; // Для удаления в том числе дочерних элементов
        }
    }
}


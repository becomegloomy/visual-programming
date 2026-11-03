#include "PrintBufferWidget.h"
#include "ui_PrintBufferWidget.h"
#include <QTime>
#include <QDateTime>
#include <QRandomGenerator>

// Конструктор PrintBufferWidget
PrintBufferWidget::PrintBufferWidget(QWidget* parent): QMainWindow(parent), ui(new Ui::PrintBufferWidget), timer(new QTimer(this)),
    // Три модели: очередь на печать, завершенные задания и отклоненные
    pendingModel(new PrintQueueModel(this)), completedModel(new PrintQueueModel(this)), rejectedModel(new PrintQueueModel(this)),
    nextJobId(1) { // переменная для нумерации заданий
    ui->setupUi(this);
    // Подключение кнопки для начала печати
    connect(ui->pushButton, &QPushButton::clicked, this, &PrintBufferWidget::startPrinting);
    // Подключение таймера
    connect(timer, &QTimer::timeout, this, &PrintBufferWidget::processPrintJobs);
    initializeModels();
}

PrintBufferWidget::~PrintBufferWidget() {
    delete ui;
}

// Метод для инициализации моделей
void PrintBufferWidget::initializeModels() {
    // Связывание моделей с таблицами для отображения данных
    ui->tableView->setModel(pendingModel);
    ui->tableView_2->setModel(completedModel);
    ui->tableView_3->setModel(rejectedModel);

    // Настройка отображения столбцов (растягивание)
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

// Метод для инициализации параметров печати и запуска таймера
void PrintBufferWidget::startPrinting() {
    // Получение параметров введенных пользователем
    startJobCount = ui->spinBox_1->value(); // Кол-во начальных заданий на печать
    printSpeed = ui->spinBox_2->value();    // Скорость печати страниц
    maxQueueSize = ui->spinBox_3->value();  // Максимальный размер очереди
    addJobProbability = ui->spinBox_4->value() / 100.0; // Вероятность добавления новых заданий
    // Добавление начальных задайний на печать в очередь
    addStartJobs();
    // Запуск таймера
    timer->start(1000);
}

// Метод для добавления в очередь начальных заданий
void PrintBufferWidget::addStartJobs() {
    for (int i = 0; i < startJobCount; ++i) {
        addRandomJob();
    }
}

// Метод для генерации случайных заданий
void PrintBufferWidget::addRandomJob() {
    QString fileName = RandomFileName(); // Имя файла
    QString time = QTime::currentTime().toString("HH:mm:ss"); // Время поступления
    int page = QRandomGenerator::global()->bounded(1, 20); // Кол-во страниц
    // Создание задания
    PrintJob newJob(nextJobId++, fileName, time, page);
    newJob.startPages = page; // Сохранение начального кол-ва страниц
    // Проверка на заполненность очереди, если заполнена перенос в отмененные задания
    if (pendingModel->rowCount() < maxQueueSize) {
        pendingModel->addJob(newJob);
    } else {
        rejectedModel->addJob(newJob);
    }
}

// Метод для генерация случайного имени файла
QString PrintBufferWidget::RandomFileName() const {
    static int fileCounter = 1;  // Счетчик для нумерации файлов
    return QString("file_%1").arg(fileCounter++);
}

// Метод для обработки заданий в очереди на печать
void PrintBufferWidget::processPrintJobs() {
    // Добавление новых заданий с заданной вероятностью
    if (QRandomGenerator::global()->bounded(100) < addJobProbability * 100) {
        addRandomJob();
    }
    // Печать текущего задания
    if (pendingModel->rowCount() > 0) {
        auto job = pendingModel->getJob(0); // Получение первого задания из очереди
        int pagesPrinted = printSpeed; // Кол-во страниц для печати
        // Проверка, сколько страниц осталось
        if (pagesPrinted >= job.page) { // Если все страницы напечатаны
            pendingModel->removeJob(0); // Удаление задания из очереди
            // Добавление задания в завершенные с начальным кол-м страниц
            job.page = job.startPages;
            completedModel->addJob(job);
        } else { // Если не все распечатаны
            job.page -= pagesPrinted;   // Уменьшение кол-ва оставшихся страниц
            pendingModel->updateJob(0, job); // Обновление задания в очереди
        }
    }
}


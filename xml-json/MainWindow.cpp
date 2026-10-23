#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->Author, &QComboBox::currentTextChanged, this, &MainWindow::loadAlbums);
    connect(ui->Album, &QComboBox::currentTextChanged, this, &MainWindow::loadTracks);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchTracks);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::resetSelections);

    loadMusicData();
    resetSelections();
}

MainWindow::~MainWindow() {
    delete ui;
}

// Метод для добавления треков в таблицу
void MainWindow::addTrackToTable(const Track &track) {
    // Получаение количества строк в таблице
    int row = ui->tableWidget->rowCount();
    // Добавление новой строки в таблицу
    ui->tableWidget->insertRow(row);
    // Загрузка данных трека
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(track.title)); // Название
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(track.year))); // Год выпуска
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(track.genre)); // Жанр
}

// Метод для загрузки альбомов для выбранного автора
void MainWindow::loadAlbums() {
    // Очистка списка альбомов
    ui->Album->clear();
    // Получение имени выбранного автора
    QString selectedAuthor = ui->Author->currentText();
    // Поиск автора по имени
    QList<Author>::const_iterator author = std::find_if(authors.begin(), authors.end(), [&selectedAuthor](const Author &a) { return a.name == selectedAuthor; });
    // Добавление всех альбомов выбранного автора в выпадающий список
    if (author != authors.end()) {
        for (const auto &album : author->albums) {
            ui->Album->addItem(album.name);
        }
    }
    // Сброс выбора альбома
    ui->Album->setCurrentIndex(-1);
}

// Метод для загрузки треков для выбранного альбома
void MainWindow::loadTracks() {
    ui->tableWidget->setRowCount(0);
    // Получение выбранного автора
    QString selectedAuthor = ui->Author->currentText();
    // Поиск автора по имени
    QList<Author>::const_iterator author = std::find_if(authors.begin(), authors.end(), [&selectedAuthor](const Author &a) { return a.name == selectedAuthor; });
    if (author != authors.end()) {
        // Получение имени выбранного альбома
        QString selectedAlbum = ui->Album->currentText();
        if (selectedAlbum.isEmpty()) {
            // Если альбом не выбран, загрузка всех треков автора
            for (const auto &album : author->albums) {
                for (const auto &track : album.tracks) {
                    addTrackToTable(track);
                }
            }
        } else {
            // Если альбом выбран, загрузка треков альбома
            QList<Album>::const_iterator album = std::find_if(author->albums.begin(), author->albums.end(), [&selectedAlbum](const Album &a) { return a.name == selectedAlbum; });
            if (album != author->albums.end()) {
                for (const auto &track : album->tracks) {
                    addTrackToTable(track);
                }
            }
        }
    }
    // Выравнивание таблицы
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


// Метод для поиска треков по названию
void MainWindow::searchTracks() {
    // Получение название треков с игнорированием регистра
    QString searchQuery = ui->lineEdit->text().toLower();
    ui->tableWidget->setRowCount(0);
    // Поиск трека по названию и загрузка его в таблицу
    for (const auto &author : authors) {
        for (const auto &album : author.albums) {
            for (const auto &track : album.tracks) {
                if (track.title.toLower().contains(searchQuery)) {
                    addTrackToTable(track);
                }
            }
        }
    }
}

// Метод для загрузки данных из XML файла
void MainWindow::loadMusicData() {
    QFile file("C:\\Users\\sofys\\OneDrive\\Рабочий стол\\школа\\вп\\3\\Vp3-1\\music_catalog.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл");
        return;
    }
    // Объекты для хранения данных из файла
    QXmlStreamReader xml(&file);
    Author currentAuthor; // Автор
    Album currentAlbum; // Альбом
    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext(); // Чтение следующего элемента
        // Поиск и извлечение из файла автора, альбома и треков
        if (xml.isStartElement()) { // Проверка на начальный элемент xml
            if (xml.name() == "author") {
                currentAuthor.name = xml.attributes().value("name").toString();
            } else if (xml.name() == "album") {
                currentAlbum.name = xml.attributes().value("name").toString();
            } else if (xml.name() == "track") {
                Track track;
                track.title = xml.attributes().value("title").toString();
                track.year = xml.attributes().value("year").toInt();
                track.genre = xml.attributes().value("genre").toString();
                currentAlbum.tracks.append(track);
            }
        } else if (xml.isEndElement()) { // Проверка на конечный элемент xml
            if (xml.name() == "album") {
                currentAuthor.albums.append(currentAlbum);
                currentAlbum = Album();  // Сброс объекта
            } else if (xml.name() == "author") {
                authors.append(currentAuthor);
                currentAuthor = Author();
            }
        }
    }
    file.close();
    // Добавление авторов в выпадающий список
    for (const auto &author : authors) {
        ui->Author->addItem(author.name);
    }
    // Загрузка альбомов
    loadAlbums();
}

// Метод для сброса всех фильтров
void MainWindow::resetSelections() {
    ui->Author->setCurrentIndex(-1);
    ui->Album->clear();
    // Очистка строки поиска треков
    ui->lineEdit->clear();
    ui->tableWidget->setRowCount(0);
    // Загрузка всех имеющихся треков в таблицу
    for (const auto &author : authors) {
        for (const auto &album : author.albums) {
            for (const auto &track : album.tracks) {
                addTrackToTable(track);
            }
        }
    }
}


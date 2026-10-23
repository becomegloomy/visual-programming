#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>

// Структура трек
struct Track {
    QString title; // Название
    int year; // Год выпуска
    QString genre; // Жанр
};

// Структура альбом
struct Album {
    QString name; // Название альбома
    QList<Track> tracks; // Список треков
};

// Структура автор
struct Author {
    QString name; // Имя автора
    QList<Album> albums; // Список альбомов
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadAlbums(); // Загрузка альбомов
    void loadTracks(); // Загрузка треков
    void searchTracks(); // Поиск трека по названию
    void resetSelections(); // Сброс фильтров

private:
    QList<Author> authors;

    Ui::MainWindow *ui;

    void loadMusicData(); // Загрузка данных из файла xml
    void addTrackToTable(const Track &track); // Добавление трека в таблицу
};

#endif // MAINWINDOW_H

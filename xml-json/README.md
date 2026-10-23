# xml-json

Приложение с графическим интерфейсом на Qt Widgets - **каталог музыки**. Данные хранятся в XML-файле и загружаются при старте программы.

Каталог разбит на **авторов → альбомы → треки**. Для каждого трека хранится название, год выпуска и жанр. В интерфейсе можно:

- выбрать автора и увидеть все его треки;
- выбрать альбом выбранного автора и увидеть только треки из него;
- искать треки по **неполному названию** (без учёта регистра);
- сбросить все фильтры одной кнопкой.

## Структура

```
xml-json/
├── Vp3-1.pro           # qmake-проект
├── main.cpp            # точка входа
├── MainWindow.h        # структуры Track/Album/Author + класс окна
├── MainWindow.cpp      # логика: парсинг XML, фильтрация, поиск
├── MainWindow.ui       # интерфейс (Qt Designer)
├── music_catalog.xml   # данные каталога
└── README.md
```

## Сборка и запуск

Требуется **Qt 5.15+** или **Qt 6** с компонентами *Qt Widgets* и компилятор C++17.

```bash
qmake
make            # Linux/macOS
# mingw32-make  # Windows + MinGW
# nmake         # Windows + MSVC
./Vp3-1         # Linux/macOS
# Vp3-1.exe     # Windows
```

## Внутреннее устройство

### Структуры данных

Иерархия описана тремя `struct` в `MainWindow.h`:

| `Track` | `Album` | `Author` |
|---|---|---|
| `title`, `year`, `genre` | `name`, `QList<Track> tracks` | `name`, `QList<Album> albums` |

Всё дерево хранится в `QList<Author> authors` - поле класса `MainWindow`.

### Парсинг XML

`MainWindow::loadMusicData()` читает файл через **`QXmlStreamReader`** (потоковый парсер из Qt Core, без внешних зависимостей):

- на `<author start>` - запоминает имя в `currentAuthor`;
- на `<album start>` - запоминает имя в `currentAlbum`;
- на `<track start>` - создаёт `Track` и добавляет в `currentAlbum.tracks`;
- на `</album>` - добавляет `currentAlbum` в `currentAuthor.albums`;
- на `</author>` - добавляет `currentAuthor` в `authors`.

После парсинга имена авторов загружаются в `QComboBox Author`, затем вызывается `resetSelections()`.

### Фильтрация и поиск

Все слоты подключаются в конструкторе:

| Сигнал | Слот | Что делает |
|---|---|---|
| `Author::currentTextChanged` | `loadAlbums()` | Заполняет `Album` альбомами выбранного автора, сбрасывает выбор альбома |
| `Album::currentTextChanged` | `loadTracks()` | Показывает треки выбранного альбома; если альбом не выбран - все треки автора |
| `lineEdit::textChanged` | `searchTracks()` | Ищет треки по подстроке в названии (без учёта регистра) среди **всех** авторов и альбомов |
| `pushButton::clicked` | `resetSelections()` | Сбрасывает оба `QComboBox`, очищает строку поиска и выводит весь каталог |

Поиск регистронезависимый: `track.title.toLower().contains(searchQuery)`.

### Добавление строки в таблицу

Единая точка входа — `addTrackToTable(const Track &track)`: создаёт новую строку в `tableWidget` и заполняет три колонки (название, год, жанр). Используется и в `loadTracks()`, и в `searchTracks()`, и в `resetSelections()`.

## Стек

- **C++17**
- **Qt Widgets** - `QMainWindow`, `QComboBox`, `QLineEdit`, `QTableWidget`, `QPushButton`, `QMessageBox`
- **Qt XML** - `QXmlStreamReader` (потоковый парсер без внешних зависимостей)
- **Qt Core** - `QFile`, `QList`, `QString`, `std::find_if` для поиска
- **Qt Designer** - `MainWindow.ui`
- **Сигналы/слоты** - `QObject::connect`, `Q_OBJECT`, лямбды в `std::find_if`

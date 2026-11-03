# visual-programming

Репозиторий содержит пять независимых проектов: визуальное построение интерфейсов, собственные элементы управления, работу с файлами, паттерны проектирования и графическую сцену.

## Структура

```
visual-programming/
├── qt-interfaces/       # интерфейс администратора СУБД (3 реализации)
├── custom-widget/       # собственный виджет «шахматная доска» (DLL + тест)
├── xml-json/            # каталог музыки, данные в XML
├── design-patterns/     # каталог задач печати на паттернах Model/View
└── graphics-scene/      # интерактивная графическая сцена (QGraphicsScene)
```

## Проекты

### 1. `qt-interfaces/`

Интерфейс администратора СУБД, реализованный **тремя разными способами** - чтобы сравнить подходы Qt к построению GUI.

| Папка | Технология |
|---|---|
| `qt-designer/` | Qt Designer - интерфейс строится из `.ui`-файла |
| `pure-code/` | Qt Widgets - интерфейс собирается вручную в C++ коде |
| `qml/` | Qt Quick / QML - декларативный интерфейс |

### 2. `custom-widget/`

Собственный элемент управления - **шахматная доска** из 64 `QPushButton`, оформленная как **динамическая библиотека**, плюс тестовая программа, демонстрирующая работу с ней через **сигналы и слоты**.

| Папка | Что это |
|---|---|
| `lib_chess/` | Библиотека с виджетом `ChessWidget` (`TEMPLATE = lib`) |
| `project_2/` | Тестовая программа: перемещение фигуры по доске |

**API виджета:**
- сигнал `buttonClicked(int row, int col)`;
- метод `setImageOnButton(int index, const QString &path)`;
- метод `removeImageFromButton(int index)`;
- метод `getImageOnButton(int index) const`.

### 3. `xml-json/`

**Каталог музыки**: авторы → альбомы → треки. Данные хранятся в XML-файле и загружаются при старте.

**Что умеет:**
- выбор автора и просмотр всех его треков;
- выбор альбома и просмотр треков только из него;
- поиск по неполному названию (без учёта регистра);
- сброс всех фильтров одной кнопкой.

### 4. `design-patterns/`

Приложение «каталог задач печати», демонстрирующее применение паттернов проектирования в реальном Qt-проекте.

**Паттерны:**
- **Model/View** - `PrintQueueModel` (наследник `QAbstractTableModel`) отделён от представления `QTableView`;
- **Composite** - `PrintBufferWidget` собирает в себе таблицу, кнопки и поля ввода в единый переиспользуемый виджет;
- **Observer** - через сигналы/слоты Qt (`dataChanged`, `beginInsertRows` / `endInsertRows`);
- **Single Responsibility** - каждый класс отвечает за своё.

### 5. `graphics-scene/`

Интерактивная **графическая сцена** на `QGraphicsScene` / `QGraphicsView` с пользовательскими элементами `QGraphicsItem`.

**Что внутри:**
- сцена с элементами, которые умеют перемещаться, выделяться и реагировать на мышь/клавиатуру;
- отрисовка через `QPainter`;
- обмен информацией между элементами и главным окном через сигналы/слоты.

## Общие требования

Все проекты используют **qmake** и собираются стандартным образом:

```bash
cd <проект>
qmake
make            # Linux/macOS
# mingw32-make  # Windows + MinGW
# nmake         # Windows + MSVC
./<target>      # Linux/macOS
# <target>.exe  # Windows
```

**Требования:**
- **Qt 5.15+** или **Qt 6**;
- компилятор с поддержкой **C++17**;
- для `qt-interfaces/qml/` - компонент *Qt Quick*;
- для `custom-widget/` - собранная библиотека `lib_chess`.

## Общий стек

- **C++17**
- **Qt Widgets** - `QMainWindow`, `QWidget`, `QTableWidget`, `QTreeWidget`, `QComboBox`, `QLineEdit`, `QPushButton` и др.
- **Qt Quick / QML** - `ApplicationWindow`, `StackView`, `ColumnLayout` / `RowLayout`, `Slider`, `ComboBox`
- **Qt XML** - `QXmlStreamReader`
- **Qt Graphics View Framework** - `QGraphicsScene`, `QGraphicsView`, `QGraphicsItem`
- **Qt Designer** - `.ui`-файлы
- **Qt Resource System** - `.qrc`, ресурсы `:/...`
- **Динамические библиотеки Qt** - `TEMPLATE = lib`, `Q_DECL_EXPORT` / `Q_DECL_IMPORT`
- **Сигналы/слоты** - `QObject::connect`, `Q_OBJECT`, `QSignalMapper`
- **qmake** - `QT += core gui widgets`, `CONFIG += c++17`
## 👤 Автор

Практические работы по дисциплине «Визуальное программирование» (кафедра О7, группа 0722Б), вариант №17.

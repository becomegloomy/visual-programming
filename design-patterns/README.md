# design-patterns

Приложение с графическим интерфейсом на Qt Widgets, демонстрирующее применение **паттернов проектирования** в реальном проекте: каталог задач печати с моделью данных, отделённой от представления.

Приложение хранит список задач печати (`PrintJob`), отображает его в таблице через кастомную модель (`PrintQueueModel`) и позволяет управлять очередью через отдельный виджет (`PrintBufferWidget`).

## Структура

```
design-patterns/
├── Vp4-1.pro                # qmake-проект
├── main.cpp                 # точка входа
├── PrintJob.h               # структура одной задачи печати
├── PrintQueueModel.h        # модель данных (Model/View)
├── PrintQueueModel.cpp
├── PrintBufferWidget.h      # составной виджет (Composite)
├── PrintBufferWidget.cpp
└── PrintBufferWidget.ui     # форма виджета (Qt Designer)
```

## Сборка и запуск

Требуется **Qt 5.15+** или **Qt 6** с компонентами *Qt Widgets* и компилятор C++17.

```bash
qmake
make            # Linux/macOS
# mingw32-make  # Windows + MinGW
# nmake         # Windows + MSVC
./Vp4-1         # Linux/macOS
# Vp4-1.exe     # Windows
```

## Архитектура и паттерны

### Model/View

Данные отделены от представления:

- **`PrintJob`** - простая структура одной задачи (что печатать, сколько копий, статус и т.п.).
- **`PrintQueueModel`** - наследник `QAbstractTableModel` / `QAbstractListModel`. Хранит `QList<PrintJob>` и реализует обязательный интерфейс модели:
  - `rowCount()` - количество задач в очереди;
  - `columnCount()` - количество колонок;
  - `data(index, role)` - отдаёт данные для отображения и редактирования;
  - `headerData(section, orientation, role)` - заголовки колонок.
- **`QTableView`** (внутри `PrintBufferWidget`) - стандартное представление, которое берёт данные из модели через `setModel()`.

### Composite (составной виджет)

`PrintBufferWidget` - это самостоятельный виджет, который **собирает** в себе несколько дочерних (`QTableView`, кнопки, поля ввода), объединяя их в единый компонент. Такой виджет можно переиспользовать в любом окне как обычный `QWidget`.

### Observer через сигналы/слоты

Qt-сигналы - это встроенная реализация паттерна «Наблюдатель». В проекте это используется так:

- изменение данных в модели → модель испускает `dataChanged()` → `QTableView` перерисовывается автоматически;
- изменение количества строк → `beginInsertRows()` / `endInsertRows()` → представление добавляет/удаляет строки;
- нажатие кнопки в `PrintBufferWidget` → сигнал `clicked()` → слот, который вызывает `insertRows()` / `removeRows()` в модели.

### Разделение ответственности (Single Responsibility)

| Класс | Ответственность |
|---|---|
| `PrintJob` | Только хранение полей одной задачи |
| `PrintQueueModel` | Хранение списка задач + оповещение об изменениях |
| `PrintBufferWidget` | UI и пользовательские действия |
| `main.cpp` | Сборка приложения и запуск |

## Стек

- **C++17**
- **Qt Widgets** - `QWidget`, `QTableView`, `QPushButton`, `QLineEdit`
- **Model/View** - `QAbstractTableModel`, `QModelIndex`, `QTableView::setModel()`
- **Сигналы/слоты** - `QObject::connect`, `Q_OBJECT`, `dataChanged`, `beginInsertRows` / `endInsertRows`
- **Qt Designer** - `PrintBufferWidget.ui`
- **qmake** - `QT += core gui widgets`, `CONFIG += c++17`

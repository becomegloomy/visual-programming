# graphics-scene

Приложение на Qt Widgets, демонстрирующее работу с **`QGraphicsScene` / `QGraphicsView`**: пользовательская сцена с графическими элементами, обработкой мыши и клавиатуры.

В приложении отображается интерактивная графическая сцена (`QGraphicsScene`) с пользовательскими элементами (`QGraphicsItem`). Элементы должны реагировать на действия пользователя - перемещение, выделение, изменение состояния - и передавать информацию обратно в программу через сигналы и слоты.

## Структура

```
graphics-scene/
├── graphics-scene.pro         # qmake-проект
├── main.cpp                   # точка входа
├── scene.h                    # класс сцены (наследник QGraphicsScene)
├── scene.cpp
├── item.h                     # пользовательский элемент (наследник QGraphicsItem)
├── item.cpp
├── view.h                     # класс представления (наследник QGraphicsView)
├── view.cpp
├── mainwindow.h               # главное окно
├── mainwindow.cpp
├── mainwindow.ui              # интерфейс (Qt Designer)
└── README.md
```

## Сборка и запуск

Требуется **Qt 5.15+** или **Qt 6** с компонентами *Qt Widgets* и компилятор C++17.

```bash
qmake
make            # Linux/macOS
# mingw32-make  # Windows + MinGW
# nmake         # Windows + MSVC
./graphics-scene         # Linux/macOS
# graphics-scene.exe     # Windows
```

## Архитектура

### Модель `QGraphicsScene` / `QGraphicsView` / `QGraphicsItem`

Qt предоставляет готовую архитектуру для отрисовки и взаимодействия с большим числом объектов:

- **`QGraphicsScene`** - контейнер для графических элементов. Хранит их в дереве, управляет отрисовкой, обработкой событий и коллизиями.
- **`QGraphicsView`** - виджет, через который сцена отображается. Может масштабироваться, прокручиваться, задавать трансформацию.
- **`QGraphicsItem`** - базовый класс для любого элемента сцены. Каждый элемент умеет:
  - рисовать себя в `paint(painter, option, widget)`;
  - возвращать свои границы в `boundingRect()`;
  - обрабатывать события мыши (`mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`) и клавиатуры (`keyPressEvent`);
  - взаимодействовать с другими элементами и со сценой.

### Пользовательский элемент

Класс `Item` (имя может отличаться — см. реальный код) наследуется от `QGraphicsItem` и переопределяет:

- `boundingRect()` - прямоугольник, в котором рисуется элемент;
- `paint()` - отрисовку через `QPainter`;
- обработчики событий мыши - для перемещения / выделения / реакции на клик.

### Сигналы и слоты

`QGraphicsItem` не наследуется от `QObject`, поэтому для сигналов нужен либо:

- промежуточный `QObject`-класс (например, `QGraphicsObject` вместо `QGraphicsItem`), либо
- проброс через сцену: элемент вызывает метод сцены, сцена испускает сигнал, на который подписано главное окно.

## Взаимодействие с пользователем

| Действие | Что происходит |
|---|---|
| Клик по элементу | Элемент выделяется / реагирует |
| Перетаскивание | Элемент перемещается (если включён флаг `ItemIsMovable`) |
| Клавиши | Обрабатываются в `keyPressEvent` (если элемент в фокусе) |
| Прокрутка / масштаб | Настраивается через `QGraphicsView` |

## Стек

- **C++17**
- **Qt Widgets** - `QMainWindow`, `QWidget`
- **Qt Graphics View Framework** - `QGraphicsScene`, `QGraphicsView`, `QGraphicsItem`, `QGraphicsObject`
- **Отрисовка** - `QPainter`, `QPen`, `QBrush`, `QPixmap`
- **События** - `mousePressEvent`, `mouseMoveEvent`, `mouseReleaseEvent`, `keyPressEvent`
- **Сигналы/слоты** - `QObject::connect`, `Q_OBJECT`
- **qmake** - `QT += core gui widgets`, `CONFIG += c++17`

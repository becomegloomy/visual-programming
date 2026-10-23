# custom-widget

Собственный элемент управления, выполненный в виде динамической библиотеки, и тестовая программа, демонстрирующая его использование. Элемент управления передает в тестовую программу данные и принимает из неё команды в формате **слотов и сигналов**.

Виджет представляет собой **64 `QPushButton`**, расположенных квадратом 8×8 чередующихся белого и чёрного цвета - шахматная доска, действия соотвествующие игре:

- **сигнал** с координатами нажатой кнопки;
- **слот/метод**, который получает изображение и номер `QPushButton` и рисует на указанном `QPushButton` переданное изображение;
- **слот/метод**, который принимает номер `QPushButton` и удаляет нарисованное на нём.

## Структура

```
custom-widget/
├── lib_chess/                  # Виджет (динамическая библиотека)
│   ├── lib_chess.pro
│   ├── lib_chess_global.h      
│   ├── chesswidget.h
│   ├── chesswidget.cpp
│   ├── chesswidget.ui          # Форма с 64 кнопками (Qt Designer) - шахматная доска
│   ├── pick.qrc                
│   └── *.png                   # Картинки шахматных фигур
│
└── project_2/                  # Тестовая программа
    ├── project_2.pro
    └── main.cpp
```

## Сборка и запуск

Требуется **Qt 5.15+** или **Qt 6** с компонентами *Qt Widgets* и компилятор C++17.

### Сборка библиотеки `lib_chess`

```bash
cd lib_chess
qmake
make            # Linux/macOS
# mingw32-make  # Windows + MinGW
# nmake         # Windows + MSVC
```

### Сборка тестовой программы

```qmake
macx: LIBS += -L$$PWD/../lib_chess/ -llib_chess.1.0.0
INCLUDEPATH += $$PWD/../lib_chess/
DEPENDPATH  += $$PWD/../lib_chess/
```

```bash
cd ../project_2
qmake
make
./project_2      # Linux/macOS
# project_2.exe  # Windows
```

## Стек

- **C++17**
- **Qt Widgets** - `QWidget`, `QPushButton`, `QSignalMapper`
- **Qt Designer** - файл `chesswidget.ui` (64 кнопки)
- **Qt Resource System** - `pick.qrc`, `:/new/prefix1/*.png`
- **Динамическая библиотека Qt** - `TEMPLATE = lib`, макросы `Q_DECL_EXPORT` / `Q_DECL_IMPORT`
- **Qt Meta-Object System** - сигналы/слоты, `Q_OBJECT`
- **Стилизация** - `QWidget::setStyleSheet()` (`background-color`, `border-image`)

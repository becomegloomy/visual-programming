# custom-widget

Виджет `ChessWidget` (динамическая библиотека) и тестовая программа, которая показывает работу с ним через **сигналы и слоты**.

Виджет - шахматная доска 8×8 из 64 `QPushButton` с чередующимся цветом клеток. Умеет:

- испускать **сигнал** с координатами нажатой клетки;
- **рисовать изображение** на указанной кнопке по её индексу;
- **удалять изображение** с указанной кнопки, сохраняя цвет фона.

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

## API виджета `ChessWidget`

### Публичные методы

| Метод | Назначение |
|---|---|
| `setImageOnButton(int index, const QString &path)` | Рисует изображение `path` на кнопке `index` (0…63) |
| `removeImageFromButton(int index)` | Удаляет изображение с кнопки, сохраняя цвет фона |
| `getImageOnButton(int index) const` | Возвращает текущее изображение с кнопки (или пустую строку) |

### Сигналы

| Сигнал | Параметры | Назначение |
|---|---|---|
| `buttonClicked(int row, int col)` | `row`, `col` ∈ 0…7 | Координаты нажатой клетки |

### Внутреннее устройство

- виджет хранит 64 `QPushButton`, созданных в Qt Designer (`chesswidget.ui`), с именами `pushButton_1` … `pushButton_64`;
- в конструкторе кнопки связываются с индексами 0…63 через **`QSignalMapper`**: каждой кнопке через `setMapping()` присваивается индекс, а сигнал `mapped(int)` идёт в слот `handleButtonClick(int)`;
- слот `handleButtonClick(int index)` вычисляет `row = index / 8`, `col = index % 8` и испускает сигнал `buttonClicked(row, col)`;
- изображение ставится через `border-image: url(...)` в `styleSheet` кнопки; при удалении фон (`background-color`) извлекается регуляркой `QRegExp` и восстанавливается, чтобы клетка не «теряла» цвет.

## Тестовая программа

`main.cpp` демонстрирует перемещение фигуры по доске:

1. Нажатие на первую клетку запоминает её индекс и изображение.
2. Нажатие на вторую клетку:
   - если на второй уже стоит фигура - она удаляется;
   - изображение переносится с первой клетки на вторую;
   - с первой клетки изображение удаляется.
3. Повторное нажатие на ту же клетку игнорируется.

Так задействуются все три метода виджета (`setImageOnButton`, `removeImageFromButton`, `getImageOnButton`) и его сигнал `buttonClicked`.

## Стек

- **C++17**
- **Qt Widgets** - `QWidget`, `QPushButton`, `QSignalMapper`
- **Qt Designer** - `chesswidget.ui`
- **Qt Resource System** - `pick.qrc`, `:/new/prefix1/*.png`
- **Динамическая библиотека Qt** - `TEMPLATE = lib`, `Q_DECL_EXPORT` / `Q_DECL_IMPORT`
- **Qt Meta-Object System** - сигналы/слоты, `Q_OBJECT`
- **Стилизация** - `QWidget::setStyleSheet()` (`background-color`, `border-image`)

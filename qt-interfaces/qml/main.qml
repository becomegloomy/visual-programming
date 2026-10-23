import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: "Бортовая система автомобиля"

    StackView {
        id: stackView
        // Определение начального экрана
        initialItem: mainScreen
        // Заполнение всего родительского элемента
        anchors.fill: parent
    }

    // Главное меню
    Component {
        id: mainScreen
        // Контейнер
        Item {
            // Визуальный элемент - прямоугольник
            Rectangle {
                color: "#333"
                anchors.fill: parent

                // Верхние надписи
                // Контейнер для вертикального размещения дочерних элементов
                ColumnLayout {
                    // Границы по верхнему и левому краю
                    anchors.left: parent.left
                    anchors.top: parent.top
                    // Отступ от указанных краев
                    anchors.margins: 20
                    // Расстояние между элементами в контейнере
                    spacing: 5

                    Text {
                        text: "Скорость"
                        color: "lightgray"
                        font.pointSize: 20
                    }
                    Text {
                        text: "100 км/ч"
                        color: "white"
                        font.pointSize: 30
                        font.bold: true
                    }
                }

                ColumnLayout {
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.margins: 20
                    spacing: 5

                    Text {
                        text: "Погода"
                        color: "lightgray"
                        font.pointSize: 20
                    }
                    Text {
                        text: "Пасмурно, 4°C"
                        color: "white"
                        font.pointSize: 24
                        font.bold: true
                    }
                }

                Text {
                    text: "BMW X6 M"
                    font.pointSize: 24
                    color: "white"
                    // Центрирование по горизонтали в пределах родительского элемента
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 100
                }

                Image {
                    source: "qrc:/new/prefix1/car.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 80
                    width: 500
                    height: 400
                    fillMode: Image.PreserveAspectFit
                }

                // Нижние кнопки
                // Контейнер для размещения элементов в строку
                RowLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    //  Привязка нижней границы элемента к нижней границе родительского элемента
                    anchors.bottom: parent.bottom
                    spacing: 10
                    width: parent.width

                    Button {
                        text: "Информация"
                        font.pointSize: 20
                        Layout.fillWidth: true
                        // Обработка события нажатия
                        onClicked: stackView.push(infoScreen)
                    }
                    Button {
                        text: "Настройки"
                        font.pointSize: 20
                        Layout.fillWidth: true
                        onClicked: stackView.push(settingsScreen)
                    }
                }
            }
        }
    }

    // Экран с информацией
    Component {
        id: infoScreen
        Item {
            Rectangle {
                color: "#222"
                anchors.fill: parent

                ColumnLayout {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 100
                    spacing: 25

                    // Заголовок
                    Text {
                        text: "Информация об автомобиле"
                        font.pointSize: 35
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.horizontalCenterOffset: -90
                    }

                    // Характеристики
                    RowLayout {
                        anchors.horizontalCenter: parent.horizontalCenter
                        spacing: 40

                        ColumnLayout {
                            spacing: 20
                            Text {
                                text: "Марка: BMW"
                                color: "lightgray"
                                font.pointSize: 25
                            }
                            Text {
                                text: "Мощность: 625 л.с."
                                color: "lightgray"
                                font.pointSize: 25
                            }
                            Text {
                                text: "Объем двигателя: 4,4 л"
                                color: "lightgray"
                                font.pointSize: 25
                            }
                        }

                        ColumnLayout {
                            spacing: 20
                            Text {
                                text: "Модель: X6 M"
                                color: "lightgray"
                                font.pointSize: 25
                            }
                            Text {
                                text: "Расход топлива: 35 л/100 км"
                                color: "lightgray"
                                font.pointSize: 25
                            }
                            Text {
                                text: "Пробег: 52,000 км"
                                color: "lightgray"
                                font.pointSize: 25
                            }
                        }
                    }
                }

                // Кнопка возвращения в главное меню
                Button {
                    text: "Вернуться в главное меню"
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    font.pointSize: 20
                    onClicked: stackView.pop()
                }
            }
        }
    }

    // Экран настроек
    Component {
        id: settingsScreen
        Item {
            Rectangle {
                color: "#111"
                anchors.fill: parent

                ColumnLayout {
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.leftMargin: 80
                    anchors.topMargin: 90
                    spacing: 20

                    // Заголовок
                    Text {
                        text: "Настройки"
                        font.pointSize: 35
                        color: "white"
                        horizontalAlignment: Text.AlignLeft
                    }

                    // Настройки с ползунками
                    // Ползунок для яркости фар
                    RowLayout {
                        spacing: 10
                        Text {
                            text: "Яркость фар"
                            color: "lightgray"
                            font.pointSize: 22
                            horizontalAlignment: Text.AlignLeft
                        }
                        Item {
                            // Заполнение элементом доступнго пространство по ширине
                            Layout.fillWidth: true
                        }

                        // Ползунок
                        Slider {
                            id: brightnessSlider
                            from: 0
                            to: 100
                            width: 200

                            // Ручка ползунка
                            handle: Rectangle {
                                width: 28
                                height: 28
                                color: "white"
                                radius: 20
                                anchors.verticalCenter: parent.verticalCenter
                                // Перемещение ручки в соответсвии с курсором
                                x: (brightnessSlider.value - brightnessSlider.from) / (brightnessSlider.to - brightnessSlider.from) * (brightnessSlider.width - width)
                            }

                            // Фон ползунка
                            background: Rectangle {
                                implicitWidth: 200
                                implicitHeight: 10
                                color: "gray"
                                radius: 5
                            }

                            // Заполнение
                            Rectangle {
                                id: fill
                                height: 10
                                color: "white"
                                radius: 5
                            }

                            // Обработчик события использования ползунка
                            onValueChanged: {
                                // Вычисление ширины заполненной части
                                var fillWidth = (value - from) / (to - from) * width;
                                fill.width = fillWidth;
                            }
                        }
                    }

                    // Ползунок для громкости звука
                    RowLayout {
                        spacing: 10
                        Text {
                            text: "Громкость звука"
                            color: "lightgray"
                            font.pointSize: 22
                            horizontalAlignment: Text.AlignLeft
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        Slider {
                            id: volumeSlider
                            from: 0
                            to: 100
                            width: 200

                            handle: Rectangle {
                                width: 28
                                height: 28
                                color: "white"
                                radius: 20
                                anchors.verticalCenter: parent.verticalCenter
                                x: (volumeSlider.value - volumeSlider.from) / (volumeSlider.to - volumeSlider.from) * (volumeSlider.width - width)
                            }

                            background: Rectangle {
                                implicitWidth: 200
                                implicitHeight: 10
                                color: "gray"
                                radius: 5
                            }

                            Rectangle {
                                id: fillVolume
                                height: 10
                                color: "white"
                                radius: 5
                            }

                            onValueChanged: {
                                var fillWidth = (value - from) / (to - from) * width;
                                fillVolume.width = fillWidth;
                            }
                        }
                    }

                    // Ползунок для температуры
                    RowLayout {
                        spacing: 10
                        Text {
                            text: "Температура в салоне"
                            color: "lightgray"
                            font.pointSize: 22
                            horizontalAlignment: Text.AlignLeft
                        }
                        Item {
                            Layout.fillWidth: true
                        }
                        Slider {
                            id: temperatureSlider
                            from: 15
                            to: 30
                            width: 200

                            handle: Rectangle {
                                width: 28
                                height: 28
                                color: "white"
                                radius: 20
                                anchors.verticalCenter: parent.verticalCenter
                                x: (temperatureSlider.value - temperatureSlider.from) / (temperatureSlider.to - temperatureSlider.from) * (temperatureSlider.width - width)
                            }

                            background: Rectangle {
                                implicitWidth: 200
                                implicitHeight: 10
                                color: "gray"
                                radius: 5
                            }

                            Rectangle {
                                id: fillTemperature
                                height: 10
                                color: "white"
                                radius: 5
                            }

                            onValueChanged: {
                                var fillWidth = (value - from) / (to - from) * width;
                                fillTemperature.width = fillWidth;
                            }
                        }
                    }

                    // Настройка подсветки
                    RowLayout {
                        spacing: 10
                        Text {
                            text: "Цвет подсветки"
                            color: "lightgray"
                            font.pointSize: 22
                            horizontalAlignment: Text.AlignLeft
                        }

                        // Элемент управления для выбира значения из списка
                        ComboBox {
                            model: ["Фиолетовый", "Белый", "Красный", "Мерцающий"]
                            currentIndex: 0
                            width: 200
                        }
                    }
                }

                // Кнопка возвращения в главное меню
                Button {
                    text: "Вернуться в главное меню"
                    font.pointSize: 20
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    onClicked: stackView.pop()
                }
            }
        }
    }
}

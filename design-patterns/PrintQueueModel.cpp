#include "PrintQueueModel.h"

PrintQueueModel::PrintQueueModel(QObject* parent) : QAbstractListModel(parent) {}

// Метод для указания кол-ва строк в модели
int PrintQueueModel::rowCount(const QModelIndex& parent) const {
    // Проверка на валидность индекса
    if (parent.isValid()) return 0;
    // Кол-во заданий
    return jobs.size();
}

// Метод для указания кол-ва столбцов в модели
int PrintQueueModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 4;
}

// Метод для отображения данных модели
QVariant PrintQueueModel::data(const QModelIndex& index, int role) const {
    // Проверка на валидность индексов
    if (!index.isValid() || index.row() >= jobs.size()) return QVariant();
    // Извлечение задания на печать по индексу строки
    const auto& job = jobs[index.row()];
    switch (role) {
    case Qt::DisplayRole: // Роль, отвечающая за отображение данных в ячейке
        switch (index.column()) {
        case 0: return job.id;       // Если первый столбец - номер задания
        case 1: return job.fileName; // Имя файла
        case 2: return job.time;     // Время поступления
        case 3: return job.page;     // Кол-во страниц
        default: return QVariant();
        }
    default:
        return QVariant();
    }
}

// Метод для определения заголовков столбцов
QVariant PrintQueueModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "№";
        case 1: return "Имя файла";
        case 2: return "Время поступления";
        case 3: return "Кол-во страниц";
        default: return QVariant();
        }
    }
    return QVariant();
}

// Метод для добавления нового задания
void PrintQueueModel::addJob(const PrintJob& job) {
    // Сообщение о вставке строк в модель
    beginInsertRows(QModelIndex(), jobs.size(), jobs.size());
    // Добавление нового задания (строки)
    jobs.append(job);
    // Сообщение о завершении вставки
    endInsertRows();
}

// Метод для удаления задания
void PrintQueueModel::removeJob(int index) {
    if (index < 0 || index >= jobs.size()) return;
    // Сообщение об удалении строк из модели
    beginRemoveRows(QModelIndex(), index, index);
    // Удаление задания
    jobs.removeAt(index);
    // Сообщение о завершении удаления
    endRemoveRows();
}

// Метод для обновления кол-ва старниц задания
void PrintQueueModel::updateJob(int index, const PrintJob& job) {
    // Обновление задания
    jobs[index] = job;
    // Сообщение об изменении данных
    emit dataChanged(createIndex(index, 0), createIndex(index, columnCount() - 1));
}

// Метод для получения задания по индексу
const PrintJob& PrintQueueModel::getJob(int index) const {
    return jobs[index];
}

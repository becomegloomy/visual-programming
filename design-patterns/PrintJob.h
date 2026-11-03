#ifndef PRINTJOB_H
#define PRINTJOB_H

#include <QString>

// Структура задания на печать
struct PrintJob {
    int id;           // Номер задания
    QString fileName; // Имя файла
    QString time;     // Время поступления
    int page;         // Кол-во страниц
    int startPages;   // Начальное кол-во страниц

    PrintJob(int id, const QString& fileName, const QString& time, int page): id(id), fileName(fileName), time(time), page(page) {}
};

#endif // PRINTJOB_H

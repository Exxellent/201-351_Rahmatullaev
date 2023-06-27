#include "promocodes.h"
#include "ui_promocodes.h"
#include <QRandomGenerator>
#include <qDebug>
#include <QString>



promocodes::promocodes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::promocodes)
{
    ui->setupUi(this);
    initPromo();
}

promocodes::~promocodes()
{
    delete ui;
}



QString promocodes::generateRandomString(int length)
{
    QString randomString;
    randomString.reserve(length);

    for (int i = 0; i < length; ++i) {
        // Генерируем случайное число от 0 до 36
        int randomValue = QRandomGenerator::global()->bounded(36);
        // Преобразуем случайное число в символ
        QChar randomChar;
        if (randomValue < 10) {
            randomChar = QChar('0' + randomValue); // цифры 0-9
        } else {
            randomChar = QChar('A' + (randomValue - 10)); // буквы A-Z
        }
        // Добавляем символ к строке
        randomString.append(randomChar);
    }
    return randomString;
}

void promocodes::initPromo() {
    ui->listWidget->clear();  // Очистка списка промокодов на пользовательском интерфейсе
    for (uint i = 0; i < fieldSize; i++) {
        addpromo();  // Добавление промокода в список
    }
}


void promocodes::addpromo() {
    auto promo = generateRandomString(4);  // Генерация случайного промокода

    promos.append(promo);  // Добавление зашифрованного промокода в список `promos`
    addCard(promo);  // Добавление карточки с промокодом в список `listWidget`
}

void promocodes::addCard(QString promo) {
    auto listItemW = new QListWidgetItem();  // Создание элемента списка
    auto itemW = new CardWidget(promo, this);  // Создание виджета карточки с промокодом

    listItemW->setSizeHint(itemW->sizeHint());  // Установка размера элемента списка на основе размера виджета карточки

    ui->listWidget->addItem(listItemW);  // Добавление элемента списка в `listWidget`
    ui->listWidget->setItemWidget(listItemW, itemW);  // Установка виджета карточки для элемента списка
}

void promocodes::on_pushButton_clicked() {
    while (true) {
        auto randomIndex = QRandomGenerator::global()->bounded(uint(0), fieldSize);  // Генерация случайного индекса

        if (openedPromos.contains(randomIndex)) continue;  // Если промокод с данным индексом уже открыт, перейти к следующей итерации цикла

        auto item = ui->listWidget->item(randomIndex);  // Получение элемента списка с соответствующим индексом
        auto itemWidget = dynamic_cast<CardWidget*>(ui->listWidget->itemWidget(item));  // Получение виджета карточки из элемента списка

        itemWidget->showPromo();  // Показать промокод на карточке
        openedPromos.append(randomIndex);  // Добавить индекс в список открытых промокодов
        fieldSize++;  // Увеличить размер поля промокодов

        addpromo();  // Добавить новый промокод

        break;  // Прервать цикл
    }
}



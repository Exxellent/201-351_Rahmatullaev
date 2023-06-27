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
        int randomValue = QRandomGenerator::global()->bounded(36);

        QChar randomChar;
        if (randomValue < 10) {
            randomChar = QChar('0' + randomValue); // цифры 0-9
        } else {
            randomChar = QChar('A' + (randomValue - 10)); // буквы A-Z
        }

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
    auto promo = generateRandomString(4);
    promos.append(promo);
    addCard(promo);
}

void promocodes::addCard(QString promo) {
    auto listItemW = new QListWidgetItem();  // Создание элемента списка
    auto itemW = new CardWidget(promo, this);  // Создание виджета карточки с промокодом

    listItemW->setSizeHint(itemW->sizeHint());  // Установка размера элемента списка на основе размера виджета карточки

    ui->listWidget->addItem(listItemW);
    ui->listWidget->setItemWidget(listItemW, itemW);
}

void promocodes::on_pushButton_clicked() {
    while (true) {
        auto randomIndex = QRandomGenerator::global()->bounded(uint(0), fieldSize);

        if (openedPromos.contains(randomIndex)) continue;

        auto item = ui->listWidget->item(randomIndex);
        auto itemWidget = dynamic_cast<CardWidget*>(ui->listWidget->itemWidget(item));

        itemWidget->showPromo();
        openedPromos.append(randomIndex);

        fieldSize++;

        addpromo();

        break;
    }
}



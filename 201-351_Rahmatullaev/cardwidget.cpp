#include "cardwidget.h"
#include "ui_cardwidget.h"

CardWidget::CardWidget(const QString promo, QWidget* parent)
    : QWidget(parent), ui(new Ui::CardWidget) {
    ui->setupUi(this);
    ui->promoButton->setText("");
    this->promo = promo;
}

CardWidget::~CardWidget() {
    delete ui;
}

void CardWidget::showPromo() {
    ui->promoButton->setText(promo);
    ui->promoButton->setStyleSheet("background-color:green; border-radius: 5px;");
}

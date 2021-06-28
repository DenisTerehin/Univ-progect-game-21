#include "playwindow.h"
#include "ui_playwindow.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <QDebug>
#include <QList>
#include <map>

PlayWindow::PlayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/images/images/blackjack-cards.jpg");
    ui->tableLabel->setPixmap(pix);
    ui->tableLabel->lower();
    ui->stickButton->setEnabled(false);
    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(800,600);

    loadList();
}

static int player_score = 0;
static int computer_score = 0;
int computer_wins = 0;
int player_wins = 0;
int holdingCardCount = 1;
int holdingCardCountComputer = 1;

void PlayWindow::loadList(){
    // Очищаем колоду
    cardHolder.clear();

    // Добавляем пики
    QPixmap card1(":/images/images/cards/ace_of_spades.png");
    QPixmap card2(":/images/images/cards/6_of_spades.png");
    QPixmap card3(":/images/images/cards/7_of_spades.png");
    QPixmap card4(":/images/images/cards/8_of_spades.png");
    QPixmap card5(":/images/images/cards/9_of_spades.png");
    QPixmap card6(":/images/images/cards/10_of_spades.png");
    QPixmap card7(":/images/images/cards/jack_of_spades.png");
    QPixmap card8(":/images/images/cards/queen_of_spades.png");
    QPixmap card9(":/images/images/cards/king_of_spades.png");

    // Добавляем черви
    QPixmap card10(":/images/images/cards/ace_of_hearts.png");
    QPixmap card11(":/images/images/cards/6_of_hearts.png");
    QPixmap card12(":/images/images/cards/7_of_hearts.png");
    QPixmap card13(":/images/images/cards/8_of_hearts.png");
    QPixmap card14(":/images/images/cards/9_of_hearts.png");
    QPixmap card15(":/images/images/cards/10_of_hearts.png");
    QPixmap card16(":/images/images/cards/jack_of_hearts.png");
    QPixmap card17(":/images/images/cards/queen_of_hearts.png");
    QPixmap card18(":/images/images/cards/king_of_hearts.png");

    // Добавляем крести
    QPixmap card19(":/images/images/cards/ace_of_clubs.png");
    QPixmap card20(":/images/images/cards/6_of_clubs.png");
    QPixmap card21(":/images/images/cards/7_of_clubs.png");
    QPixmap card22(":/images/images/cards/8_of_clubs.png");
    QPixmap card23(":/images/images/cards/9_of_clubs.png");
    QPixmap card24(":/images/images/cards/10_of_clubs.png");
    QPixmap card25(":/images/images/cards/jack_of_clubs.png");
    QPixmap card26(":/images/images/cards/queen_of_clubs.png");
    QPixmap card27(":/images/images/cards/king_of_clubs.png");

    // Добавляем буби
    QPixmap card28(":/images/images/cards/ace_of_diamonds.png");
    QPixmap card29(":/images/images/cards/6_of_diamonds.png");
    QPixmap card30(":/images/images/cards/7_of_diamonds.png");
    QPixmap card31(":/images/images/cards/8_of_diamonds.png");
    QPixmap card32(":/images/images/cards/9_of_diamonds.png");
    QPixmap card33(":/images/images/cards/10_of_diamonds.png");
    QPixmap card34(":/images/images/cards/jack_of_diamonds.png");
    QPixmap card35(":/images/images/cards/queen_of_diamonds.png");
    QPixmap card36(":/images/images/cards/king_of_diamonds.png");

    // Добавляем пики в колоду
    cardHolder.append(card1);
    cardHolder.append(card2);
    cardHolder.append(card3);
    cardHolder.append(card4);
    cardHolder.append(card5);
    cardHolder.append(card6);
    cardHolder.append(card7);
    cardHolder.append(card8);
    cardHolder.append(card9);

    // Добавляем черви в колоду
    cardHolder.append(card10);
    cardHolder.append(card11);
    cardHolder.append(card12);
    cardHolder.append(card13);
    cardHolder.append(card14);
    cardHolder.append(card15);
    cardHolder.append(card16);
    cardHolder.append(card17);
    cardHolder.append(card18);

    // Добавляем крести в колоду
    cardHolder.append(card19);
    cardHolder.append(card20);
    cardHolder.append(card21);
    cardHolder.append(card22);
    cardHolder.append(card23);
    cardHolder.append(card24);
    cardHolder.append(card25);
    cardHolder.append(card26);
    cardHolder.append(card27);

    // Добавляем буби в колоду
    cardHolder.append(card28);
    cardHolder.append(card29);
    cardHolder.append(card30);
    cardHolder.append(card31);
    cardHolder.append(card32);
    cardHolder.append(card33);
    cardHolder.append(card34);
    cardHolder.append(card35);
    cardHolder.append(card36);
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::on_twistButton_clicked()
{
    srand(time(NULL));
    int deckValues[36] = {11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4};
    int number = (rand() % 36);
    ui->playercurrentLabel->setText("Текущая карта: " + QString::number(deckValues[number]));
    player_score += deckValues[number];
    ui->playertotalLabel->setText("Счет: " + QString::number(player_score));

    // Номер карты, которая будет выставлена
    switch(holdingCardCount){
    case 1:
        ui->card1Label->setPixmap(cardHolder.at(number));
        break;
    case 2:
        ui->card2Label->setPixmap(cardHolder.at(number));
        break;
    case 3:
        ui->card3Label->setPixmap(cardHolder.at(number));
        break;
    case 4:
        ui->card4Label->setPixmap(cardHolder.at(number));
        break;
    case 5:
        ui->card5Label->setPixmap(cardHolder.at(number));
        break;
    case 6:
        ui->card6Label->setPixmap(cardHolder.at(number));
        break;
    case 7:
        ui->card7Label->setPixmap(cardHolder.at(number));
        break;
    }
    ++holdingCardCount;

    if (player_score > 21){
        ui->statusLabel->setText("Перебор!");
        ui->twistButton->setEnabled(false);
        computerTurn();
    }
    if (player_score > 2 && player_score < 22){
        ui->stickButton->setEnabled(true);
    }
    else {
        ui->stickButton->setEnabled(false);
        ui->playagainButton->setEnabled(true);
    }
}

void PlayWindow::on_stickButton_clicked()
{
    this->setEnabled(false);
    ui->playagainButton->setEnabled(true);
    ui->twistButton->setEnabled(false);
    ui->stickButton->setEnabled(false);
    computerTurn();
}

void PlayWindow::computerTurn(){
    QPixmap win(":/images/images/win.png");
    QPixmap lose(":/images/images/lose.png");
    QPixmap draw(":/images/images/draw.png");

    int deckValues2[36] = {11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4,11,6,7,8,9,10,2,3,4};
    srand(time(NULL));
    int computer_score = 0;
    int number = 0;
    while (computer_score < 16) {
        number = (rand() % 36);
        computer_score += deckValues2[number];
            switch(holdingCardCountComputer){
                case 1:
                    ui->card7Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 2:
                    ui->card6Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 3:
                    ui->card5Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 4:
                    ui->card4Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 5:
                    ui->card3Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 6:
                    ui->card2Label_2->setPixmap(cardHolder.at(number));
                    break;
                case 7:
                    ui->card1Label_2->setPixmap(cardHolder.at(number));
                break;
            }
            ++holdingCardCountComputer;
    }
    ui->computerScoreLabel->setText("Компьютер: " + QString::number(computer_score));

    if (computer_score > 21){
        ui->computerStatusLabel->setText("Перебор!");
    }

    if ((computer_score == player_score) || ((computer_score > 21) && (player_score > 21))){
        ui->outcomeLabel->setPixmap(draw);
    }
    else
        if (((computer_score < 22) && (player_score < 22) && (computer_score > player_score)) || ((player_score > 21) && computer_score < 22 )){
        ui->outcomeLabel->setPixmap(lose);;
        ++computer_wins;
    }
    else{
        ui->outcomeLabel->setPixmap(win);
        ++player_wins;
    }
    ui->statusbar->showMessage("Игрок " + QString::number(player_wins) + " - Игровой счет - " + "Компьютер " + QString::number(computer_wins));
    this->setEnabled(true);
}

void PlayWindow::on_playagainButton_clicked()
{
    player_score = 0;
    computer_score = 0;
    holdingCardCount = 1;
    holdingCardCountComputer = 1;

    ui->playercurrentLabel->setText("Карта: " + QString::number(0));
    ui->playertotalLabel->setText("Счет: " + QString::number(0));

    ui->twistButton->setEnabled(true);
    ui->playagainButton->setEnabled(false);
    ui->stickButton->setEnabled(false);
    ui->outcomeLabel->clear();
    ui->computerStatusLabel->setText("");
    ui->statusLabel->setText("");
    ui->computerScoreLabel->setText("Компьютер: " + QString::number(0));

    // Очищаем стол игрока и компьютера
    ui->card1Label->clear();
    ui->card2Label->clear();
    ui->card3Label->clear();
    ui->card4Label->clear();
    ui->card5Label->clear();
    ui->card6Label->clear();
    ui->card7Label->clear();

    ui->card7Label_2->clear();
    ui->card6Label_2->clear();
    ui->card5Label_2->clear();
    ui->card4Label_2->clear();
    ui->card3Label_2->clear();
    ui->card2Label_2->clear();
    ui->card1Label_2->clear();
}

void PlayWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

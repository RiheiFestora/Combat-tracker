#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_combat_tracker_main.h"
#include "Participant.h"
#include <QStandardItemModel>
#include <Qlabel.h>
#include <QListWidgetItem>
#include <QLineEdit>
#include <Qtimer.h>
#include <qpointer.h>
#include <QPushButton>
#include <QDebug>
#include <QStandardItem>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>

#include <QMouseEvent>

class combat_tracker_main : public QMainWindow
{
    Q_OBJECT

public:
    combat_tracker_main(QWidget *parent = nullptr);
    ~combat_tracker_main();

private:
    Ui::combat_tracker_mainClass ui;
    QStandardItemModel* model;
    QPushButton* previousParticipantButton = nullptr;
    QPushButton* nextParticipantButton = nullptr;
    QList<QSharedPointer<Participant>> participants;
    QWidget* createRowWidget(QSharedPointer<Participant> participant);
    void setupTimer(QSharedPointer<Participant> participant, QLineEdit* timeEdit, QLineEdit* currentTurn);
    int current_round_integer;
    QLabel* current_round_integer_label;
    bool isCombatStarted = false;
    QVector<QSharedPointer<Participant>> collectParticipantsToList();
    void addParticipantWidgetToList(QSharedPointer<Participant>& participant);

    QPoint dragPosition;
    bool dragging = false;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    void addWidgetToList();
    void startCombat();
    void previousParticipant();
    void nextParticipant();
    void addTurnButtons();
    void removeTurnButtons();
    void sortParticipants();
    void saveParticipants();
    void loadParticipants();
    void onQuitButtonClicked();

};

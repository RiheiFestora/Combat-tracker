/********************************************************************************
** Form generated from reading UI file 'combat_tracker_main.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBAT_TRACKER_MAIN_H
#define UI_COMBAT_TRACKER_MAIN_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_combat_tracker_mainClass
{
public:
    QAction *actionSave_participants;
    QAction *actionLoad_participants;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *contentArea;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLabel *current_round_integer_label;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout_2;
    QPushButton *startCombatButton;
    QPushButton *addParticipant;
    QPushButton *sortParticipantsButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *quitButton;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *combat_tracker_mainClass)
    {
        if (combat_tracker_mainClass->objectName().isEmpty())
            combat_tracker_mainClass->setObjectName(QString::fromUtf8("combat_tracker_mainClass"));
        combat_tracker_mainClass->resize(600, 500);
        actionSave_participants = new QAction(combat_tracker_mainClass);
        actionSave_participants->setObjectName(QString::fromUtf8("actionSave_participants"));
        actionLoad_participants = new QAction(combat_tracker_mainClass);
        actionLoad_participants->setObjectName(QString::fromUtf8("actionLoad_participants"));
        centralWidget = new QWidget(combat_tracker_mainClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        contentArea = new QWidget(centralWidget);
        contentArea->setObjectName(QString::fromUtf8("contentArea"));
        gridLayout = new QGridLayout(contentArea);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(contentArea);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(contentArea);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        current_round_integer_label = new QLabel(contentArea);
        current_round_integer_label->setObjectName(QString::fromUtf8("current_round_integer_label"));

        horizontalLayout_6->addWidget(current_round_integer_label);


        gridLayout->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        startCombatButton = new QPushButton(contentArea);
        startCombatButton->setObjectName(QString::fromUtf8("startCombatButton"));

        gridLayout_2->addWidget(startCombatButton, 3, 0, 1, 2);

        addParticipant = new QPushButton(contentArea);
        addParticipant->setObjectName(QString::fromUtf8("addParticipant"));

        gridLayout_2->addWidget(addParticipant, 1, 0, 1, 1);

        sortParticipantsButton = new QPushButton(contentArea);
        sortParticipantsButton->setObjectName(QString::fromUtf8("sortParticipantsButton"));

        gridLayout_2->addWidget(sortParticipantsButton, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        quitButton = new QPushButton(contentArea);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        horizontalLayout->addWidget(quitButton);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(contentArea);

        combat_tracker_mainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(combat_tracker_mainClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        combat_tracker_mainClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionSave_participants);
        menuFile->addAction(actionLoad_participants);

        retranslateUi(combat_tracker_mainClass);

        QMetaObject::connectSlotsByName(combat_tracker_mainClass);
    } // setupUi

    void retranslateUi(QMainWindow *combat_tracker_mainClass)
    {
        combat_tracker_mainClass->setWindowTitle(QCoreApplication::translate("combat_tracker_mainClass", "combat_tracker_main", nullptr));
        actionSave_participants->setText(QCoreApplication::translate("combat_tracker_mainClass", "Save participants", nullptr));
        actionLoad_participants->setText(QCoreApplication::translate("combat_tracker_mainClass", "Load participants", nullptr));
        label_2->setText(QCoreApplication::translate("combat_tracker_mainClass", "Current Round", nullptr));
        current_round_integer_label->setText(QCoreApplication::translate("combat_tracker_mainClass", "PLACEHOLDER", nullptr));
        startCombatButton->setText(QCoreApplication::translate("combat_tracker_mainClass", "Start combat", nullptr));
        addParticipant->setText(QCoreApplication::translate("combat_tracker_mainClass", "Add a participant", nullptr));
        sortParticipantsButton->setText(QCoreApplication::translate("combat_tracker_mainClass", "Sort participants", nullptr));
        quitButton->setText(QCoreApplication::translate("combat_tracker_mainClass", "X", nullptr));
        menuFile->setTitle(QCoreApplication::translate("combat_tracker_mainClass", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class combat_tracker_mainClass: public Ui_combat_tracker_mainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBAT_TRACKER_MAIN_H

#include "widgetStyler.h"


void widgetStyler::applyStartCombatStyle(QPushButton* button) 
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/start_combat_button.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 20px;
            color: white;
            font-weight: bold;
            min-height: 40px;
            max-height: 40px;
        }

        QPushButton:hover {

        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applyAddParticipantStyle(QPushButton* button)
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/slim_button1.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 16px;
            color: white;
            min-height: 40px;
            max-height: 40px;
        }

        QPushButton:hover {

        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applySortParticipantsStyle(QPushButton* button)
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/slim_button2.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 16px;
            color: white;
            min-height: 50px;
            max-height: 50px;
        }

        QPushButton:hover {

        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applyNextParticipantStyle(QPushButton* button)
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/slim_button3.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 16px;
            color: white;
            min-height: 40px;
            max-height: 40px;
        }

        QPushButton:hover {

        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applypreviousParticipantStyle(QPushButton* button)
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/slim_button4.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 16px;
            color: white;
            min-height: 40px;
            max-height: 40px;
        }

        QPushButton:hover {

        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applyRowBackground(QWidget* rowWidget)
{
    int imageIndex = QRandomGenerator::global()->bounded(1, 9);  // 1 to 8
    QString imagePath = QString(":/combat_tracker/images/rowwidget%1.png").arg(imageIndex);

    QString style = QString(R"(
        QWidget {
            background-image: url(%1);
            background-repeat: stretch;
            background-position: center;

            min-height: 50px;
            max-height: 50px;
        }
    )").arg(imagePath);

    rowWidget->setStyleSheet(style);
}

void widgetStyler::applyRowWidgetStyle(QLineEdit* nameEdit, QLineEdit* iniEdit, QLineEdit* timeEdit, QLineEdit* currentTurn, QPushButton* deleteButton) 
{
    QString transparentLineEditStyle = R"(
        QLineEdit {
            background: transparent;
            border: none;
            font-size: 20px;
            color: white;
        }
    )";

    nameEdit->setStyleSheet(transparentLineEditStyle);
    iniEdit->setStyleSheet(transparentLineEditStyle);
    timeEdit->setStyleSheet(transparentLineEditStyle);
    currentTurn->setStyleSheet(transparentLineEditStyle);

    deleteButton->setStyleSheet(R"(
        QPushButton {
            background: transparent;
            border: none;
            color: white;
            font-weight: bold;
        }

        QPushButton:hover {
            color: red;
        }
    )");
}

void widgetStyler::applyListWidgetTransparentStyle(QListWidget* listWidget)
{
    listWidget->setStyleSheet(R"(
        QListWidget {
            background: transparent;
            border: none;
        }

        QListWidget::item {
            background: transparent;
            border: none;
        }

        QListWidget::item:selected {
            background: transparent;
            border: none;
        }
    )");
}

void widgetStyler::applyApplicationBackground(QWidget* mainWindow)
{
    mainWindow->setStyleSheet(R"(
        QWidget {
            background-color: transparent;
            background-image: url(:/combat_tracker/images/app_background_transparent2.png);
            background-repeat: no-repeat;

            background-position: center;
            background-attachment: fixed;
        }
    )");
}

void widgetStyler::applyMenuBarStyle(QMenuBar* menuBar) 
{
    menuBar->setStyleSheet(R"(
        QMenuBar {
            background-image: url(:/combat_tracker/images/menubar3.png);
            background-repeat: stretch;
            background-position: left;
            color: white;
        }

        QMenuBar::item {
            background: transparent;

        }

        QMenuBar::item:selected {
            background: #444444;
        }

        QMenu {
            background-color: #333;
            color: white;
        }

        QMenu::item:selected {
            background-color: #555;
        }
    )");
}

void widgetStyler::applyRoundLabelStyle(QLabel* label)
{
    label->setStyleSheet(R"(
        QLabel {
            border: none;
            background-image: url(:/combat_tracker/images/roundbackground.png);
            background-repeat: no-repeat;
            background-position: left;
            font-size: 16px;
            color: white;
            min-height: 40px;
            max-height: 40px;
        }
    )");
}

void widgetStyler::applyQuitButtonStyle(QPushButton* button)
{
    button->setStyleSheet(R"(
        QPushButton {
            border: none;
            background-image: url(:/combat_tracker/images/xmarker.png);
            background-repeat: no-repeat;
            background-position: center;
            color: transparent;
            min-height: 40px;
            max-height: 40px;
            min-width: 40px;
            max-width: 40px;
        }

        QPushButton:hover {
            background-image: url(:/combat_tracker/images/xmarkerbright.png);
        }

        QPushButton:pressed {
            color: red;
        }
    )");
}

void widgetStyler::applyRoundCounterLabelStyle(QLabel* label)
{
    label->setStyleSheet(R"(
        QLabel {
            border: none;
            background-image: url(:/combat_tracker/images/roundcounterbackground.png);
            background-repeat: no-repeat;
            background-position: center;
            font-size: 16px;
            color: white;
            min-height: 40px;
            max-height: 40px;
        }
    )");
}
#pragma once
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QRandomGenerator>
#include <qlistwidget.h>
#include <qmenubar.h>
#include <qlabel.h>

class widgetStyler
{
public:
	static void applyStartCombatStyle(QPushButton* button);
	static void applyAddParticipantStyle(QPushButton* button);
	static void applySortParticipantsStyle(QPushButton* button);
	static void applyNextParticipantStyle(QPushButton* button);
	static void applypreviousParticipantStyle(QPushButton* button);
	static void applyRowBackground(QWidget* rowWidget);
	static void applyRowWidgetStyle(QLineEdit* nameEdit, QLineEdit* iniEdit, QLineEdit* timeEdit, QLineEdit* currentTurn, QPushButton* deleteButton);
	static void applyListWidgetTransparentStyle(QListWidget* listWidget);
	static void applyApplicationBackground(QWidget* mainWindow);
	static void applyMenuBarStyle(QMenuBar* menuBar);
	static void applyRoundLabelStyle(QLabel* label);
	static void applyRoundCounterLabelStyle(QLabel* label);
	static void applyQuitButtonStyle(QPushButton* button);
};


#include "combat_tracker_main.h"
#include "widgetStyler.h"

combat_tracker_main::combat_tracker_main(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    widgetStyler::applyStartCombatStyle(ui.startCombatButton);
    widgetStyler::applyListWidgetTransparentStyle(ui.listWidget);
    widgetStyler::applyApplicationBackground(this);
    widgetStyler::applyAddParticipantStyle(ui.addParticipant);
    widgetStyler::applySortParticipantsStyle(ui.sortParticipantsButton);
    widgetStyler::applyMenuBarStyle(ui.menuBar);
    widgetStyler::applyRoundLabelStyle(ui.label_2);
    ui.label_2->setAlignment(Qt::AlignCenter);
    ui.current_round_integer_label->setAlignment(Qt::AlignCenter);
    widgetStyler::applyRoundCounterLabelStyle(ui.current_round_integer_label);
    widgetStyler::applyQuitButtonStyle(ui.quitButton);

    setMinimumSize(450, 900);
    setMaximumSize(450, 900);

    current_round_integer = 0;
    ui.current_round_integer_label->setText(QString::number(current_round_integer));

    connect(ui.addParticipant, &QPushButton::clicked, this, &combat_tracker_main::addWidgetToList);
    connect(ui.startCombatButton, &QPushButton::clicked, this, &combat_tracker_main::startCombat);
    connect(ui.sortParticipantsButton, &QPushButton::clicked, this, &combat_tracker_main::sortParticipants);
    connect(ui.actionSave_participants, &QAction::triggered, this, &combat_tracker_main::saveParticipants);
    connect(ui.actionLoad_participants, &QAction::triggered, this, &combat_tracker_main::loadParticipants);
    connect(ui.quitButton, &QPushButton::clicked, this, &combat_tracker_main::onQuitButtonClicked);
}



void combat_tracker_main::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}


void combat_tracker_main::mouseMoveEvent(QMouseEvent* event)
{
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}


void combat_tracker_main::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        event->accept();
    }
}


QVector<QSharedPointer<Participant>> combat_tracker_main::collectParticipantsToList()
{
    QVector<QSharedPointer<Participant>> participantVector;
    for (int i = 0; i < ui.listWidget->count(); ++i) 
    {
        QListWidgetItem* item = ui.listWidget->item(i);
        QWidget* rowWidget = ui.listWidget->itemWidget(item);
        QSharedPointer<Participant> participant = rowWidget->property("participantPtr").value<QSharedPointer<Participant>>();

        int ini = participant->ini;
        participantVector.append(participant);
    }

    return participantVector;
}


void sortParticipantsByIniDescending(QVector<QSharedPointer<Participant>>& participants)
{
    std::sort(participants.begin(), participants.end(), [](const QSharedPointer<Participant>& a, const QSharedPointer<Participant>& b) {
        return a->ini > b->ini;  // Descending order
        });
}


void combat_tracker_main::sortParticipants()
{
    QVector<QSharedPointer<Participant>> participantVector = collectParticipantsToList();
    sortParticipantsByIniDescending(participantVector);
    // Optional: Detach and delete all widgets associated with items
    for (int i = 0; i < ui.listWidget->count(); ++i) {
        QListWidgetItem* item = ui.listWidget->item(i);
        QWidget* widget = ui.listWidget->itemWidget(item);
        if (widget) {
            ui.listWidget->removeItemWidget(item);  // Detach
            delete widget;  // Delete to prevent memory leaks
        }
    }
    ui.listWidget->clear();

    // Functio addWidgetToList(Participant) // Niinkuin addWidgetToList(), mutta luo rivin Participant olion tietojen pohjalta, nimi, ini, minute ja second
    for (auto participant : participantVector)
    {
        addParticipantWidgetToList(participant);
    }
}


void combat_tracker_main::saveParticipants()
{
    QVector<QSharedPointer<Participant>> participantVector = collectParticipantsToList();
    sortParticipantsByIniDescending(participantVector);

    QJsonArray jsonArray;
    for (const auto& participant : participantVector) {
        QJsonObject obj;
        obj["name"] = participant->name;
        obj["ini"] = participant->ini;
        jsonArray.append(obj);
    }

    QJsonDocument doc(jsonArray);

    // Launch native resource manager dialog
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Participants",
        QDir::homePath(),                    // Start in user's home directory
        "JSON Files (*.json);;All Files (*)",
        nullptr,
        QFileDialog::Options(QFileDialog::DontUseCustomDirectoryIcons)
    );

    // Add .json extension if user didn’t include one
    if (!fileName.isEmpty() && !fileName.endsWith(".json", Qt::CaseInsensitive)) {
        fileName += ".json";
    }

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson(QJsonDocument::Indented));
            file.close();
        }
        else {
            QMessageBox::warning(this, "Save Error", "Could not open file for writing.");
        }
    }
}


void combat_tracker_main::loadParticipants()
{
    // Native file open dialog
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Load Participants",
        QDir::homePath(),
        "JSON Files (*.json);;All Files (*)"
    );

    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Load Error", "Could not open file for reading.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (doc.isNull() || !doc.isArray()) {
        QMessageBox::warning(this, "Parse Error", "Failed to parse JSON: " + parseError.errorString());
        return;
    }

    QVector<QSharedPointer<Participant>> participantVector;

    QJsonArray array = doc.array();
    for (const QJsonValue& val : array) {
        if (!val.isObject()) continue;

        QJsonObject obj = val.toObject();
        QString name = obj["name"].toString();
        int ini = obj["ini"].toInt();

        QSharedPointer<Participant> p(new Participant(name, ini, "", ""));
        participantVector.append(p);
    }

    // Add loaded participants to the UI
    for (auto participant : participantVector) {
        addParticipantWidgetToList(participant);
    }
}


void combat_tracker_main::startCombat()
{
    if (ui.listWidget->count() == 0)
        return;  // If the list is empty, do nothing

    if (!isCombatStarted) {
        // If combat hasn't started yet, start it
        // Get the first item in the list
        QListWidgetItem* firstItem = ui.listWidget->item(0);
        if (!firstItem)
            return;

        // Retrieve the widget associated with this item
        QWidget* rowWidget = ui.listWidget->itemWidget(firstItem);
        if (!rowWidget)
            return;

        // Find the QLineEdit inside the widget
        QList<QLineEdit*> lineEdits = rowWidget->findChildren<QLineEdit*>();
        if (lineEdits.size() >= 4) {
            lineEdits[3]->setText("<");  // Set "<" in the 4th QLineEdit
        }

        // Change the button text to "Stop Combat"
        ui.startCombatButton->setText("Stop Combat");

        addTurnButtons();

        isCombatStarted = true;  // Mark combat as started
    }
    else {
        // If combat has started, stop it
        ui.startCombatButton->setText("Start Combat");

        // You can also add logic here to reset anything else necessary, e.g., removing turn buttons
        // Reset any UI elements related to the ongoing combat here

        isCombatStarted = false;  // Mark combat as stopped

        int count = ui.listWidget->count();
        if (count == 0) return;  // No widgets in the list

        // Find the widget with "<" in the fourth QLineEdit
        for (int i = 0; i < count; ++i) {
            QListWidgetItem* item = ui.listWidget->item(i);
            QWidget* rowWidget = ui.listWidget->itemWidget(item);
            if (!rowWidget) continue;

            QList<QLineEdit*> lineEdits = rowWidget->findChildren<QLineEdit*>();
            if (lineEdits.size() >= 4 && lineEdits[3]->text() == "<") {
                lineEdits[3]->clear();  // Remove "X" from current
            }
        }
        removeTurnButtons();
    }
}


void combat_tracker_main::addTurnButtons()
{
    if (!previousParticipantButton && !nextParticipantButton)
    {
        // Create buttons
        previousParticipantButton = new QPushButton("Previous Participant", this);
        nextParticipantButton = new QPushButton("Next Participant", this);

        // Get the grid layout (gridLayout_2)
        QGridLayout* gridLayout = qobject_cast<QGridLayout*>(ui.gridLayout_2);

        // Find the row and column of startCombatButton
        int row = -1, column = -1, rowSpan, columnSpan;
        for (int i = 0; i < gridLayout->count(); ++i) {
            QLayoutItem* item = gridLayout->itemAt(i);
            if (item && item->widget() == ui.startCombatButton) {
                gridLayout->getItemPosition(i, &row, &column, &rowSpan, &columnSpan);
                break;
            }
        }

        // Insert the new buttons in the row below startCombatButton
        int newRow = row + 1;
        gridLayout->addWidget(previousParticipantButton, newRow, column);
        gridLayout->addWidget(nextParticipantButton, newRow, column + 1);

        // Apply the style settings to buttons
        widgetStyler::applyNextParticipantStyle(nextParticipantButton);
        widgetStyler::applypreviousParticipantStyle(previousParticipantButton);
        // Update UI
        ui.startCombatButton->parentWidget()->update();

        // Connect button signals
        connect(previousParticipantButton, &QPushButton::clicked, this, &combat_tracker_main::previousParticipant);
        connect(nextParticipantButton, &QPushButton::clicked, this, &combat_tracker_main::nextParticipant);
    }
}


void combat_tracker_main::removeTurnButtons()
{
    if (previousParticipantButton) {
        delete previousParticipantButton;
        previousParticipantButton = nullptr;
    }

    if (nextParticipantButton) {
        delete nextParticipantButton;
        nextParticipantButton = nullptr;
    }

    // Optionally, you can call update to refresh the UI
    ui.startCombatButton->parentWidget()->update();
}


void combat_tracker_main::previousParticipant()
{
    int count = ui.listWidget->count();
    if (count == 0) return;  // No widgets in the list
    int currentIndex = -1;

    // Find the widget with "<" in the fourth QLineEdit
    for (int i = 0; i < count; ++i) 
    {
        QListWidgetItem* item = ui.listWidget->item(i);
        QWidget* rowWidget = ui.listWidget->itemWidget(item);
        QList<QLineEdit*> lineEdits = rowWidget->findChildren<QLineEdit*>();
        if (lineEdits.size() >= 4 && lineEdits[3]->text() == "<") 
        {
            currentIndex = i;
            lineEdits[3]->clear();  // Remove "X" from current
            break;
        }
    }

    // Determine the previous index (wrap around if needed)
    int previousIndex = (currentIndex <= 0) ? count - 1 : currentIndex - 1;
    if (previousIndex == count - 1)
    {
        current_round_integer -= 1;
        ui.current_round_integer_label->setText(QString::number(current_round_integer));
    }

    // Set "<" in the fourth field of the previous widget
    QListWidgetItem* previousItem = ui.listWidget->item(previousIndex);
    QWidget* previousRowWidget = ui.listWidget->itemWidget(previousItem);
    if (previousRowWidget) 
    {
        QList<QLineEdit*> prevLineEdits = previousRowWidget->findChildren<QLineEdit*>();
        if (prevLineEdits.size() >= 4) 
        {
            prevLineEdits[3]->setText("<");
        }
    }
}


void combat_tracker_main::nextParticipant()
{
    int count = ui.listWidget->count();
    if (count == 0) return;  // No widgets in the list
    int currentIndex = -1;

    // Find the widget with "<" in the fourth QLineEdit
    for (int i = 0; i < count; ++i) 
    {
        QListWidgetItem* item = ui.listWidget->item(i);
        QWidget* rowWidget = ui.listWidget->itemWidget(item);
        QList<QLineEdit*> lineEdits = rowWidget->findChildren<QLineEdit*>();
        if (lineEdits.size() >= 4 && lineEdits[3]->text() == "<") 
        {
            currentIndex = i;
            lineEdits[3]->clear();  // Remove "<" from the last label of the row
            break;
        }
    }

    // Determine the next index (wrap around if needed)
    int nextIndex = (currentIndex >= count - 1) ? 0 : currentIndex + 1;
    if (nextIndex == 0)
    {
        current_round_integer += 1;
        ui.current_round_integer_label->setText(QString::number(current_round_integer));
    }

    // Set "<" in the fourth field of the previous widget
    QListWidgetItem* previousItem = ui.listWidget->item(nextIndex);
    QWidget* previousRowWidget = ui.listWidget->itemWidget(previousItem);
    if (previousRowWidget) 
    {
        QList<QLineEdit*> prevLineEdits = previousRowWidget->findChildren<QLineEdit*>();
        if (prevLineEdits.size() >= 4) 
        {
            prevLineEdits[3]->setText("<");
        }
    }
}


void combat_tracker_main::addParticipantWidgetToList(QSharedPointer<Participant> & participant)
{
    // Create the row widget
    QWidget* rowWidget = createRowWidget(participant);

    // Store the participant pointer as a QVariant in the widget
    rowWidget->setProperty("participantPtr", QVariant::fromValue(participant));

    // Create QListWidgetItem
    QListWidgetItem* item = new QListWidgetItem(ui.listWidget);
    item->setSizeHint(rowWidget->sizeHint());

    // Add widget to QListWidget
    ui.listWidget->addItem(item);
    ui.listWidget->setItemWidget(item, rowWidget);
}


void combat_tracker_main::addWidgetToList()
{
    // Create a new Participant object
    QSharedPointer<Participant> participant = QSharedPointer<Participant>::create("Enter name", 0, "0", "0");
    participants.append(participant);

    // Create the row widget
    QWidget* rowWidget = createRowWidget(participant);

    // Store the participant pointer as a QVariant in the widget
    rowWidget->setProperty("participantPtr", QVariant::fromValue(participant));

    // Create QListWidgetItem
    QListWidgetItem* item = new QListWidgetItem(ui.listWidget);
    item->setSizeHint(rowWidget->sizeHint());

    // Add widget to QListWidget
    ui.listWidget->addItem(item);
    ui.listWidget->setItemWidget(item, rowWidget);
}


QWidget* combat_tracker_main::createRowWidget(QSharedPointer<Participant> participant)
{
    QWidget* rowWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(rowWidget);
    layout->setContentsMargins(5, 3, 3, 2);

    // Participant's name
    QLineEdit* nameEdit = new QLineEdit(rowWidget);
    if (participant->name == "Enter name") { nameEdit->setPlaceholderText(participant->name); }
    else { nameEdit->setText(participant->name); }
    nameEdit->setPlaceholderText(participant->name);
    nameEdit->setMaxLength(20);

    // Participant's initiative score
    QLineEdit* iniEdit = new QLineEdit(rowWidget);
    if (participant->ini == 0) { iniEdit->setPlaceholderText(QString::number(participant->ini)); }
    else { iniEdit->setText(QString::number(participant->ini)); }
    iniEdit->setValidator(new QIntValidator(0, 100, rowWidget));

    // Participant's stopwatch
    QLineEdit* timeEdit = new QLineEdit(rowWidget);
    timeEdit->setPlaceholderText(QString("%1:%2")
        .arg(participant->minute.toInt(), 2, 10, QChar('0'))
        .arg(participant->second.toInt(), 2, 10, QChar('0')));
    timeEdit->setReadOnly(true);

    // Indicator if it's current participant's turn at the moment. Empty means no, '<' means yes.
    QLineEdit* currentTurn = new QLineEdit(rowWidget);
    currentTurn->setPlaceholderText(" ");
    currentTurn->setReadOnly(true);

    // Delete button
    QPushButton* deleteButton = new QPushButton("X", rowWidget);
    deleteButton->setFixedWidth(24);

    // Connect delete button
    connect(deleteButton, &QPushButton::clicked, this, [this, rowWidget]() {
        for (int i = 0; i < ui.listWidget->count(); ++i) {
            QListWidgetItem* item = ui.listWidget->item(i);
            if (ui.listWidget->itemWidget(item) == rowWidget) {
                QListWidgetItem* removedItem = ui.listWidget->takeItem(i);
                delete removedItem;
                delete rowWidget;
                break;
            }
        }
        });

    // Connect user input fields to update Participant object
    connect(nameEdit, &QLineEdit::textChanged, [participant](const QString& text) {
        participant->name = text;
        });

    connect(iniEdit, &QLineEdit::textChanged, [participant](const QString& text) {
        participant->ini = text.toInt();
        });

    // Start a timer to update the time
    setupTimer(participant, timeEdit, currentTurn);

    // Set the width of the fields
    //nameEdit->setFixedWidth(100);
    iniEdit->setFixedWidth(70);
    timeEdit->setFixedWidth(70);
    currentTurn->setFixedWidth(30);

    // Add widgets to layout
    layout->addWidget(deleteButton);
    layout->addWidget(nameEdit);
    layout->addWidget(iniEdit);
    layout->addWidget(timeEdit);
    layout->addWidget(currentTurn);
    rowWidget->setLayout(layout);

    widgetStyler::applyRowBackground(rowWidget);
    widgetStyler::applyRowWidgetStyle(nameEdit, iniEdit, timeEdit, currentTurn, deleteButton);
    return rowWidget;
}


void combat_tracker_main::setupTimer(QSharedPointer<Participant> participant, QLineEdit* timeEdit, QLineEdit* currentTurn)
{
    QTimer* timer = new QTimer(this);

    // Use QPointer to safely track the QLineEdit widgets
    QPointer<QLineEdit> safeTimeEdit = timeEdit;
    QPointer<QLineEdit> safeCurrentTurn = currentTurn;

    connect(timer, &QTimer::timeout, this, [participant, safeTimeEdit, safeCurrentTurn]() {
        // Only proceed if widgets are still valid
        if (!safeCurrentTurn || !safeTimeEdit)
            return;

        if (safeCurrentTurn->text().trimmed() == "<") {
            participant->incrementTime();
            safeTimeEdit->setText(QString("%1:%2")
                .arg(participant->minute, 2, QChar('0'))  // Format with leading zero
                .arg(participant->second, 2, QChar('0')));
        }
        });

    timer->start(1000);
}


combat_tracker_main::~combat_tracker_main()
{
}


void combat_tracker_main::onQuitButtonClicked() 
{
    QApplication::quit();
}
#include "ElysiaUpdater.h"
#include <QtCore/QProcess>
#include <QtCore/QTimer>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtWidgets/QApplication>
#include <QtGui/QPixmap>
#include <functional>
#include <QDebug> // Added for qDebug

ElysiaUpdater::ElysiaUpdater(QWidget *parent)
    : QWidget(parent), process(nullptr), syncCallback(nullptr)
{
    // Set up assets path
    QString homeDir = QString::fromLocal8Bit(qgetenv("REAL_HOME").isEmpty() ? qgetenv("HOME") : qgetenv("REAL_HOME"));
    assetsPath = QDir(homeDir + "/.config/Elysia/assets/assets").absolutePath();
    setupUI();
    connectSignals();
    // Set background after UI is set up
    QTimer::singleShot(0, this, &ElysiaUpdater::setBackgroundByTheme);
}

ElysiaUpdater::~ElysiaUpdater()
{
    if (process) {
        process->kill();
        process->deleteLater();
    }
}

void ElysiaUpdater::setupUI()
{
    setWindowTitle("Elysia Updater");
    setFixedSize(1280, 720);
    setStyleSheet("background: transparent;");
    // Background label
    bg = new QLabel(this);
    bg->setScaledContents(true);
    bg->lower();
    // Main card
    card = new QFrame(this);
    card->setStyleSheet("QFrame { background-color: rgba(0, 0, 0, 0.3); border-radius: 26px; }");
    card->setGraphicsEffect(createShadow());
    layout = new QVBoxLayout(card);
    layout->setContentsMargins(30, 30, 30, 30);
    layout->setSpacing(20);
    // Output text edit
    output = new QTextEdit();
    output->setReadOnly(true);
    output->setStyleSheet(R"(
        QTextEdit {
            background-color: rgba(255,255,255,0.05);
            color: white;
            font-size: 14px;
            font-family: Monospace;
            border-radius: 10px;
            padding: 10px;
        }
    )");
    layout->addWidget(output);
    // Scroll area for updates (not used by ElysiaOS updates, but kept for consistency)
    scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("background: transparent;");
    scrollArea->setWidgetResizable(true);
    scrollWidget = new QWidget();
    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);
    scrollArea->hide();
    // Bottom container
    bottomContainer = new QWidget();
    bottomRow = new QHBoxLayout(bottomContainer);
    bottomRow->setContentsMargins(0, 0, 0, 0);
    bottomRow->setSpacing(10);
    // Info frame
    QFrame *infoFrame = new QFrame();
    infoFrame->setStyleSheet("QFrame { background: transparent; }");
    QHBoxLayout *infoLayout = new QHBoxLayout(infoFrame);
    QLabel *icon = new QLabel();
    QString iconPath = QDir(assetsPath).filePath("quest.png");
    QPixmap iconPixmap(iconPath);
    icon->setPixmap(iconPixmap.scaled(54, 54, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel *text = new QLabel("Info");
    text->setStyleSheet("color: white; font-size: 16px; font-weight: bold;");
    infoLayout->addWidget(icon);
    infoLayout->addWidget(text);
    infoLayout->setAlignment(Qt::AlignLeft);
    bottomRow->addWidget(infoFrame);
    bottomRow->addStretch();
    // Buttons - Create and add checkElysiaBtn before checkYayBtn
    // --- Add the new button ---
    checkElysiaBtn = new QPushButton("CHECK ELYSIAOS UPDATES"); 
    // -------------------------
    checkYayBtn = new QPushButton("CHECK YAY UPDATES");
    checkBtn = new QPushButton("CHECK FOR UPDATES");
    cancelBtn = new QPushButton("CLOSE");
    // Apply styles and sizes to all buttons
    for (QPushButton *btn : {checkElysiaBtn, checkYayBtn, checkBtn, cancelBtn}) { // Include new button
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(fancyButtonStyle(btn));
        btn->setFixedSize(200, 40);
    }
    // Add buttons in the desired order
    // --- Add the new button to the layout before checkYayBtn ---
    bottomRow->addWidget(checkElysiaBtn); 
    // ---------------------------------------------------------
    bottomRow->addWidget(checkYayBtn);
    bottomRow->addWidget(checkBtn);
    bottomRow->addWidget(cancelBtn);
    layout->addWidget(bottomContainer);
}

void ElysiaUpdater::connectSignals()
{
    connect(checkBtn, &QPushButton::clicked, this, &ElysiaUpdater::checkUpdates);
    connect(checkYayBtn, &QPushButton::clicked, this, &ElysiaUpdater::checkYayUpdates);
    // --- Connect the new button's signal to its slot ---
    connect(checkElysiaBtn, &QPushButton::clicked, this, &ElysiaUpdater::checkElysiaUpdates); 
    // --------------------------------------------------
    connect(cancelBtn, &QPushButton::clicked, this, &QWidget::close);
}

QString ElysiaUpdater::getUserTheme()
{
    return qEnvironmentVariable("GTK_THEME", "Adwaita");
}

QString ElysiaUpdater::fancyButtonStyle(QPushButton *btn)
{
    QString bg, textColor;
    if (btn->text() == "CLOSE") {
        bg = "#d2b48c";
        textColor = "#f0f0f0";
    } else {
        bg = "#a87c4f";
        textColor = "#ffffff";
    }
    return QString(R"(
        QPushButton {
            background-color: %1;
            border: none;
            border-radius: 10px;
            color: %2;
            font-size: 11px;
            font-family: ElysiaOSNew;
            font-weight: bold;
            padding: 6px 12px;
            letter-spacing: 1px;
        }
        QPushButton:hover {
            background-color: #b88c5f;
        }
        QPushButton:pressed {
            background-color: #8c6239;
        }
    )").arg(bg, textColor);
}

QGraphicsDropShadowEffect* ElysiaUpdater::createShadow()
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(25);
    shadow->setColor(QColor(0, 0, 0, 180));
    shadow->setOffset(0, 10);
    return shadow;
}

void ElysiaUpdater::resizeEvent(QResizeEvent *event)
{
    bg->setGeometry(0, 0, width(), height());
    int margin = 50;
    card->setGeometry(margin, margin, width() - margin * 2, height() - margin * 2);
    QWidget::resizeEvent(event);
}

void ElysiaUpdater::setBackgroundByTheme()
{
    try {
        QString theme = getUserTheme();
        qDebug() << "Theme detected:" << theme;
        QString bgFile = (theme == "ElysiaOS-HoC") ? "elysian-ui-hoc.png" : "elysian-ui.png";
        QString bgPath = QDir(assetsPath).filePath(bgFile);
        QPixmap bgPixmap(bgPath);
        bg->setPixmap(bgPixmap);
    } catch (...) {
        qDebug() << "Theme detection failed";
        QString bgPath = QDir(assetsPath).filePath("elysian-ui.png");
        QPixmap bgPixmap(bgPath);
        bg->setPixmap(bgPixmap);
    }
}

void ElysiaUpdater::disableButtons()
{
    checkBtn->setEnabled(false);
    checkYayBtn->setEnabled(false);
    // --- Disable the new button too ---
    checkElysiaBtn->setEnabled(false); 
    // ---------------------------------
}

void ElysiaUpdater::enableButtons()
{
    checkBtn->setEnabled(true);
    checkYayBtn->setEnabled(true);
    // --- Enable the new button too ---
    checkElysiaBtn->setEnabled(true); 
    // --------------------------------
}

void ElysiaUpdater::clearScrollLayout()
{
    updateButtons.clear();
    while (scrollLayout->count()) {
        QLayoutItem *child = scrollLayout->takeAt(0);
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
}

void ElysiaUpdater::enterUpdateMode(const QString &message)
{
    output->setText(message);
    scrollArea->hide();
    bottomContainer->hide();
    for (QPushButton *btn : updateButtons) {
        btn->hide();
    }
    // --- Hide the new button specifically during update mode ---
    checkElysiaBtn->hide(); 
    // ---------------------------------------------------------
    card->setStyleSheet("QFrame { background-color: rgba(0, 0, 0, 0.4); border-radius: 26px; }");
}

void ElysiaUpdater::exitUpdateMode()
{
    bottomContainer->show();
    for (QPushButton *btn : updateButtons) {
        btn->show();
    }
    // --- Show the new button again ---
    checkElysiaBtn->show(); 
    // --------------------------------
    card->setStyleSheet("QFrame { background-color: rgba(0, 0, 0, 0.3); border-radius: 26px; }");
}

void ElysiaUpdater::checkUpdates()
{
    if (!checkBtn->isEnabled()) {
        return;
    }
    disableButtons();
    clearScrollLayout();
    output->clear();
    output->setText("🔃 Syncing before checking for updates...");
    syncCallback = [this]() {
        QTimer::singleShot(500, this, &ElysiaUpdater::fetchUpdates);
    };
    syncDatabase(syncCallback);
}

void ElysiaUpdater::checkYayUpdates()
{
    if (!checkYayBtn->isEnabled()) {
        return;
    }
    disableButtons();
    clearScrollLayout();
    output->clear();
    output->setText("🔃 Checking for AUR (yay) updates...\n");
    QProcess yayProcess;
    yayProcess.start("yay", QStringList() << "-Qmu");
    yayProcess.waitForFinished();
    QString result = yayProcess.readAllStandardOutput();
    QStringList lines = result.trimmed().split('\n');
    // Filter out invalid lines
    QStringList validLines;
    for (const QString &line : lines) {
        if (!line.trimmed().isEmpty() &&
            !line.contains('[') && !line.contains('{') && !line.contains('~')) {
            validLines.append(line);
        }
    }
    if (validLines.isEmpty()) {
        output->setText("✅ All AUR packages are up to date.");
        enableButtons();
        return;
    }
    updates.clear();
    for (const QString &line : validLines) {
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (!parts.isEmpty()) {
            updates.append(parts.first());
        }
    }
    output->setText(QString("🌟 %1 AUR updates found:\n").arg(updates.size()));
    scrollLayout->setSpacing(10);
    for (const QString &pkg : updates) {
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);
        QLabel *label = new QLabel(pkg);
        label->setStyleSheet("color: white; font-size: 20px;");
        QPushButton *btn = new QPushButton(QString("Update Only %1").arg(pkg));
        btn->setStyleSheet(fancyButtonStyle(btn));
        connect(btn, &QPushButton::clicked, this, [this, pkg]() {
            enterUpdateMode(QString("⏳ Updating AUR package %1...\n").arg(pkg));
            runUpdate(QStringList() << "yay" << "-S" << "--noconfirm" << pkg);
        });
        rowLayout->addWidget(label);
        rowLayout->addStretch();
        rowLayout->addWidget(btn);
        scrollLayout->addWidget(rowWidget);
        updateButtons.append(btn);
    }
    QPushButton *updateAllBtn = new QPushButton("Update All AUR");
    updateAllBtn->setStyleSheet(fancyButtonStyle(updateAllBtn));
    updateAllBtn->setFixedHeight(40);
    connect(updateAllBtn, &QPushButton::clicked, this, &ElysiaUpdater::updateAllYay);
    scrollLayout->addWidget(updateAllBtn);
    updateButtons.append(updateAllBtn);
    scrollArea->show();
    enableButtons();
}

// --- New Method for ElysiaOS Updates ---
void ElysiaUpdater::checkElysiaUpdates()
{
    if (!checkElysiaBtn->isEnabled()) {
        return;
    }
    disableButtons();
    clearScrollLayout(); // Clear any previous update lists if shown
    scrollArea->hide();  // Hide the scroll area used by other checks
    output->clear();
    output->setText("🔄 Checking for ElysiaOS updates using git-elyos.sh...\n");

    // Ensure the process is clean
    if (process) {
        process->kill();
        process->deleteLater();
    }
    process = new QProcess(this);

    // Capture both stdout and stderr
    process->setProcessChannelMode(QProcess::MergedChannels);

    // Connect signals to display output
    connect(process, &QProcess::readyReadStandardOutput, this, &ElysiaUpdater::printOutput);
    connect(process, &QProcess::readyReadStandardError, this, &ElysiaUpdater::printOutput); // Also capture errors

    // Connect finished signal to re-enable buttons
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
                Q_UNUSED(exitCode)
                Q_UNUSED(exitStatus)
                output->append("\n✅ ElysiaOS update check finished.\nReturning to menu...");
                // Use a timer to ensure the final message is seen before resetting
                QTimer::singleShot(2000, this, [this]() {
                    resetToMainMenu(); // This will re-enable buttons
                });
            });

    // --- Start the script ---
    // Make sure the path to your script is correct.
    // If it's in the user's PATH, you can just use "git-elyos.sh"
    // Otherwise, provide the full path, e.g., "/home/username/scripts/git-elyos.sh"
    QString scriptPath = "git-elyos.sh"; // <-- Adjust this path if needed

    // Check if script exists (optional, but good practice)
    QFileInfo scriptInfo(scriptPath);
    if (scriptInfo.exists() && scriptInfo.isFile() && scriptInfo.isExecutable()) {
        process->start(scriptPath);
    } else {
        // Try finding it in a common location or PATH
        // This is a simple check, you might need a more robust way
        process->start("sh", QStringList() << "-c" << scriptPath); 
        // Or specify the full path directly if known:
        // process->start("/full/path/to/your/git-elyos.sh"); 
    }
    // ------------------------
}
// --- End of new method ---

void ElysiaUpdater::syncDatabase(std::function<void()> callback)
{
    output->append("🔃 Syncing package database...\n");
    if (process) {
        process->kill();
        process->deleteLater();
    }
    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output_text = process->readAllStandardOutput();
        output->insertPlainText(output_text);
    });
    connect(process, &QProcess::readyReadStandardError, this, [this]() {
        QString error_text = process->readAllStandardError();
        output->insertPlainText(error_text);
    });
    syncCallback = callback;
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &ElysiaUpdater::syncFinished);
    process->start("pkexec", QStringList() << "pacman" << "-Syyy" << "--noconfirm");
}

void ElysiaUpdater::syncFinished()
{
    if (syncCallback) {
        syncCallback();
        syncCallback = nullptr;
    }
}

void ElysiaUpdater::fetchUpdates()
{
    clearScrollLayout();
    QProcess checkProcess;
    checkProcess.start("checkupdates");
    checkProcess.waitForFinished();
    QString result = checkProcess.readAllStandardOutput();
    QStringList lines = result.trimmed().split('\n');
    if (lines.isEmpty() || (lines.size() == 1 && lines.first().isEmpty())) {
        output->setText("✅ System is up to date.");
        enableButtons();
        return;
    }
    updates.clear();
    for (const QString &line : lines) {
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (!parts.isEmpty()) {
            updates.append(parts.first());
        }
    }
    output->setText(QString("🔧 %1 updates found:\n").arg(updates.size()));
    scrollLayout->setSpacing(10);
    for (const QString &pkg : updates) {
        QWidget *rowWidget = new QWidget();
        QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);
        QLabel *label = new QLabel(pkg);
        label->setStyleSheet("color: white; font-size: 20px;");
        QPushButton *btn = new QPushButton(QString("Update Only %1").arg(pkg));
        btn->setStyleSheet(fancyButtonStyle(btn));
        connect(btn, &QPushButton::clicked, this, [this, pkg]() {
            enterUpdateMode(QString("⏳ Updating %1...\n").arg(pkg));
            syncDatabase([this, pkg]() {
                runUpdate(QStringList() << "pkexec" << "pacman" << "-S" << "--noconfirm" << pkg);
            });
        });
        rowLayout->addWidget(label);
        rowLayout->addStretch();
        rowLayout->addWidget(btn);
        scrollLayout->addWidget(rowWidget);
        updateButtons.append(btn);
    }
    QPushButton *updateAllBtn = new QPushButton("Update All");
    updateAllBtn->setStyleSheet(fancyButtonStyle(updateAllBtn));
    updateAllBtn->setFixedHeight(40);
    connect(updateAllBtn, &QPushButton::clicked, this, &ElysiaUpdater::updateAll);
    scrollLayout->addWidget(updateAllBtn);
    updateButtons.append(updateAllBtn);
    scrollArea->show();
    enableButtons();
}

void ElysiaUpdater::updatePackage()
{
    // This method is handled by lambda connections in fetchUpdates
}

void ElysiaUpdater::updatePackageYay()
{
    // This method is handled by lambda connections in checkYayUpdates
}

void ElysiaUpdater::updateAll()
{
    enterUpdateMode("⏳ Updating all packages...\n");
    runUpdate(QStringList() << "pkexec" << "pacman" << "-Syu" << "--noconfirm");
}

void ElysiaUpdater::updateAllYay()
{
    enterUpdateMode("⏳ Updating all AUR packages...\n");
    runUpdate(QStringList() << "yay" << "-Sua" << "--noconfirm");
}

void ElysiaUpdater::runUpdate(const QStringList &cmd)
{
    output->clear();
    if (process) {
        process->disconnect();
        process->kill();
        process->deleteLater();
    }
    process = new QProcess(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
    connect(process, &QProcess::readyReadStandardOutput, this, &ElysiaUpdater::printOutput);
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &ElysiaUpdater::updateFinished);
    process->start(cmd.first(), cmd.mid(1));
}

void ElysiaUpdater::printOutput()
{
    // --- Simplified output handling ---
    // Read all available output from the currently running process
    if (process) {
        QByteArray data = process->readAllStandardOutput();
        if (data.isEmpty()) {
             data = process->readAllStandardError();
        }
        if (!data.isEmpty()) {
            QString output_text = QString::fromLocal8Bit(data);
            // Move cursor to end and insert text
            output->moveCursor(QTextCursor::End);
            output->insertPlainText(output_text);
            // Auto-scroll to the bottom
            output->moveCursor(QTextCursor::End);
        }
    }
    // ----------------------------------
}


void ElysiaUpdater::updateFinished()
{
    output->append("\n✅ Update finished!\nReturning to menu...");
    exitUpdateMode();
    QTimer::singleShot(2000, this, &ElysiaUpdater::resetToMainMenu);
}

void ElysiaUpdater::resetToMainMenu()
{
    output->clear();
    clearScrollLayout();
    bottomContainer->show();
    enableButtons(); // This is the key part that re-enables all buttons
}

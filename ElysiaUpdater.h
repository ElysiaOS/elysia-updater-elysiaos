#ifndef ELYSIAUPDATER_H
#define ELYSIAUPDATER_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtCore/QTimer>
#include <QtCore/QProcess>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtGui/QPixmap>
#include <QtGui/QColor>
#include <QtGui/QTextCursor>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QResizeEvent>

class ElysiaUpdater : public QWidget
{
    Q_OBJECT

public:
    ElysiaUpdater(QWidget *parent = nullptr);
    ~ElysiaUpdater();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void setBackgroundByTheme();
    void checkUpdates();
    void checkElysiaUpdates();
    void checkYayUpdates();
    void updatePackage();
    void updatePackageYay();
    void updateAll();
    void updateAllYay();
    void printOutput();
    void updateFinished();
    void resetToMainMenu();
    void syncFinished();

private:
    // UI Components
    QLabel *bg;
    QFrame *card;
    QVBoxLayout *layout;
    QTextEdit *output;
    QScrollArea *scrollArea;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;
    QWidget *bottomContainer;
    QHBoxLayout *bottomRow;
    QPushButton *checkBtn;
    QPushButton *checkElysiaBtn;
    QPushButton *checkYayBtn;
    QPushButton *cancelBtn;
    
    // Data and Process Management
    QStringList updates;
    QProcess *process;
    QList<QPushButton*> updateButtons;
    QString assetsPath;
    
    // Helper Methods
    QString getUserTheme();
    QString fancyButtonStyle(QPushButton *btn);
    QGraphicsDropShadowEffect* createShadow();
    void disableButtons();
    void enableButtons();
    void clearScrollLayout();
    void enterUpdateMode(const QString &message);
    void exitUpdateMode();
    void syncDatabase(std::function<void()> callback);
    void fetchUpdates();
    void runUpdate(const QStringList &cmd);
    void setupUI();
    void connectSignals();
    
    // Callback storage for async operations
    std::function<void()> syncCallback;
};

#endif // ELYSIAUPDATER_H
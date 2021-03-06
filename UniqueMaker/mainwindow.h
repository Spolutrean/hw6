#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QFile>
#include <QFuture>
#include <QFutureWatcher>
#include <vector>
#include <unordered_map>
#include <QString>
#include <QStringList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static quint64 progress;
    static QMutex mutex;
    static QFutureWatcher<void> hashingWatcher;
    static QFutureWatcher<void> indexingWatcher;
    static std::map<std::pair<quint64, QByteArray>, QStringList> hashedFiles;
    static std::vector<std::pair<quint64, QString> > foundedFiles;
    std::vector<std::vector<QString> > distributedFiles;

private slots:
    void on_pushButton_clicked();
    void on_startScanning_clicked();
    void on_pushButton_2_clicked();
    void allFilesWasIndexed();

private:
    Ui::MainWindow *ui;
    static void findAllFilesInDirectory(QString const &curDirPath);
    void distributeFilesEvenly();
    void deleteFileWithUniqSize();
    void fillTreeWidget();
    static void getHashOfFile(QFile &file, QCryptographicHash &hashMaker);

    static void handleBlockOfFiles(const std::vector<QString>& block);
};

#endif // MAINWINDOW_H

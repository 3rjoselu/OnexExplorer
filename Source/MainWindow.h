#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Openers/NosCCInfOpener.h"
#include "Openers/NosTextOpener.h"
#include "Openers/NosZlibOpener.h"
#include "Ui/Previews/SingleImagePreview.h"
#include "Ui/Previews/SingleTextFilePreview.h"
#include "Ui/Settings.h"
#include <QDebug>
#include <QDropEvent>
#include <QFileDialog>
#include <QMainWindow>
#include <QMimeData>
#include <Source/Openers/JsonConfigOpener.h>

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    const QString VERSION = "v0.7.1";
public slots:
    void on_actionOpen_triggered();
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *prev);
    void replaceInfo(FileInfo *info);
    void on_actionReplace_triggered();
    void on_actionExport_triggered();
    void on_actionExport_to_raw_triggered();
    void on_actionReplace_with_raw_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExport_with_config_triggered();
    void on_actionImport_from_config_triggered();
    void on_actionApplyPatch_triggered();
    void on_actionSaveAllNos_triggered();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void filterItems();
    void onCustomMenuShow(const QPoint &point);
    void clearMenu();
    void on_actionClose_selected_triggered();
    void on_actionClose_all_triggered();
    void on_actionSettings_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void on_actionRename_triggered();
    void itemEdited(QTreeWidgetItem *item, int column);
private:
    Ui::MainWindow *ui;
    Settings *settings;
    QMenu *contextMenu = nullptr;
    NosTextOpener textOpener;
    NosZlibOpener zlibOpener;
    NosCCInfOpener ccinfOpener;
    JsonConfigOpener jsonOpener;
    void openFile(const QString &path);
    void handleOpenResults(OnexTreeItem *item, const QString &path);
    INosFileOpener *getOpener(const QByteArray &header);
    template<typename TreeFunction>
    void fileOperationOnSelectedItems(TreeFunction treeFunction, const QString &defaultPath, QString operationName, bool saveDialog,
                                      QString filter = QString());
    QString getSelectedDirectory(const QString &suggestion);
    QString getOpenFile(const QString &suggestion, const QString &filter);
    QStringList getOpenFiles(const QString &suggestion, const QString &filter);
    QString getSaveFile(const QString &suggestion, const QString &filter);
    void dropEvent(QDropEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    OnexTreeItem *getTreeRoot();
    QString neatPath(QString path);
};

#endif // MAINWINDOW_H

#include "OnexTreeItem.h"
#include <QCollator>

OnexTreeItem::OnexTreeItem(const QString &name, INosFileOpener *opener, QByteArray content)
        : name(name), opener(opener), content(content) {
    this->setText(0, name);
    this->setFlags(this->flags() | Qt::ItemIsEditable);
}

OnexTreeItem::~OnexTreeItem() = default;

QWidget *OnexTreeItem::getPreview() {
    return nullptr;
}

FileInfo *OnexTreeItem::getInfos() {
    FileInfo *infos = generateInfos();
    if (infos != nullptr)
        connect(this, SIGNAL(replaceInfo(FileInfo * )), infos, SLOT(replace(FileInfo * )));
    return infos;
}

bool OnexTreeItem::hasParent() {
    return QTreeWidgetItem::parent() != nullptr;
}

QString OnexTreeItem::getName() {
    return name;
}

QByteArray OnexTreeItem::getContent() {
    return content;
}

int OnexTreeItem::getContentSize() {
    return content.size();
}

bool OnexTreeItem::isEmpty() {
    return getContent().isEmpty();
}

QString OnexTreeItem::getExportExtension() {
    return "";
}

QString OnexTreeItem::getExportExtensionFilter() {
    if (getExportExtension() == ".png")
        return "PNG Image (*.png)";
    else if (getExportExtension() == ".txt")
        return "Text File (*.txt)";
    else if (getExportExtension() == ".lst")
        return "List File (*.lst)";
    else if (getExportExtension() == ".dat")
        return "DAT File (*.dat)";
    else if (getExportExtension() == ".obj")
        return "OBJ File (*.obj)";
    else if (getExportExtension() == ".json")
        return "JSON File (*.json)";
    return "All files (*.*)";
}

void OnexTreeItem::setName(QString name) {
    this->name = name;
    setText(0, name);
}

void OnexTreeItem::setContent(QByteArray content) {
    this->content = content;
}

int OnexTreeItem::onExport(QString directory) {
    if (childCount() > 0) {
        int count = 0;
        for (int i = 0; i != this->childCount(); ++i) {
            auto *item = dynamic_cast<OnexTreeItem *>(this->child(i));
            count += item->onExport(directory);
        }
        return count;
    } else {
        QString path = getCorrectPath(directory);
        return saveAsFile(path);
    }
}

int OnexTreeItem::onExportRaw(QString directory) {
    QString path = getCorrectPath(directory, ".bin");
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    if (file.write(this->getContent()) == -1) {
        return 0;
    }
    file.close();
    return 1;
}

int OnexTreeItem::onExportAsOriginal(QString path) {
    if (path.isEmpty())
        return 0;
    if (!path.endsWith(".NOS"))
        path += ".NOS";
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(nullptr, "Woops", "Couldn't open this file for writing");
        return 0;
    }
    if (file.write(opener->encrypt(this)) == -1) {
        QMessageBox::critical(nullptr, "Woops", "Couldn't write to this file");
        return 0;
    }
    file.close();
    QMessageBox::information(nullptr, "Yeah", "File exported into .NOS");
    return 1;
}

int OnexTreeItem::onReplace(QString directory) {
    int count = 0;
    if (this->childCount() > 0) {
        for (int i = 0; i < this->childCount(); i++) {
            auto *item = dynamic_cast<OnexTreeItem *>(this->child(i));
            count += item->onReplace(directory);
        }
        if (hasParent())
            afterReplace(QByteArray());
    }
    if (count > 0)
        return count;
    QString path = getCorrectPath(directory);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
        return afterReplace(file.readAll());
    else {
        QMessageBox::critical(nullptr, "Woops", "Couldn't open " + path);
        return 0;
    }
}

int OnexTreeItem::onReplaceRaw(QString directory) {
    QString path = getCorrectPath(directory, ".bin");
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
        file.close();
        return 1;
    }
    return 0;
}

int OnexTreeItem::afterReplace(QByteArray content) {
    emit replaceInfo(generateInfos());
    return 1;
}

QJsonObject OnexTreeItem::generateConfig() {
    QJsonObject jo = generateInfos()->toJson();

    if (childCount() > 0) {
        QJsonArray contentArray;
        for (int i = 0; i < childCount(); i++) {
            auto item = static_cast<OnexTreeItem *>(child(i));
            contentArray.append(item->generateConfig());
        }
        jo["content"] = contentArray;
    } else {
        QString path = this->getName();
        if (!path.endsWith(getExportExtension()))
            path += getExportExtension();
        jo["path"] = path;
    }
    return jo;
}

QString OnexTreeItem::getCorrectPath(QString input, QString extension) {
    if (extension.isEmpty())
        extension = getExportExtension();

    if (!input.endsWith(extension)) {
        input = input + this->getName();
        if (!input.endsWith(extension))
            input += extension;
    }
    return input;
}

FileInfo *OnexTreeItem::generateInfos() {
    FileInfo *infos = new FileInfo();

    if (hasParent() && isEmpty()) {
        infos->addReplaceButton("Load from File");
        infos->addReplaceRawButton("Load from raw File");
    } else if (hasParent()) {
        infos->addReplaceButton("Replace");
        infos->addReplaceRawButton("Replace with raw");
    }
    if (!hasParent()) {
        infos->addStringLineEdit("Archive", text(0))->setEnabled(false);
    }

    connect(this, SIGNAL(changeSignal(QString, QString)), infos, SLOT(update(QString, QString)));
    connect(this, SIGNAL(changeSignal(QString, int)), infos, SLOT(update(QString, int)));
    connect(this, SIGNAL(changeSignal(QString, float)), infos, SLOT(update(QString, float)));
    connect(this, SIGNAL(changeSignal(QString, bool)), infos, SLOT(update(QString, bool)));
    return infos;
}

int OnexTreeItem::saveAsFile(const QString &path, QByteArray content) {
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(content.isEmpty() ? getContent() : content);
        file.close();
        return 1;
    }
    return 0;
}

bool OnexTreeItem::operator<(const QTreeWidgetItem &other) const {
    int column = treeWidget()->sortColumn();
    static QCollator collator;
    collator.setNumericMode(true);
    return collator.compare(text(column), other.text(column)) < 0;
}

#ifndef INI_H
#define INI_H

#include <QObject>
#include <QSettings>
#include <QSize>
#include <QRect>
#include <QMenuBar>
#include <QSplitter>

class Ini : public QObject
{
    Q_OBJECT

public:
    static QVariant getValue(QString group, QString key, QVariant defaultValue = QVariant());
    static void setValue(QString group, QString key, QVariant value);

    static void saveGeometry(QWidget *widget, QString name);
    static void saveGeometry(QWidget *widget);
    static void loadGeometry(QWidget *widget, QString name);
    static void loadGeometry(QWidget *widget);

    static void saveMenu(QMenu *menu, QString name);
    static void loadMenu(QMenu *menu, QString name);
    static void saveMenu(QMenuBar *menuBar, QString name);
    static void loadMenu(QMenuBar *menuBar, QString name);

protected:
    static Ini *get();

    QVariant m_getValue(QString group, QString key, QVariant defaultValue = QVariant());
    void m_setValue(QString group, QString key, QVariant value);
    void m_setValueWithoutSync(QString group, QString key, QVariant value);

    void m_saveGeometry(QWidget *widget, QString name);
    void m_loadGeometry(QWidget *widget, QString name);

    void m_saveMenu(QMenu *menu, QString name);
    void m_loadMenu(QMenu *menu, QString name);
    void m_saveMenu(QMenuBar *menuBar, QString name);
    void m_loadMenu(QMenuBar *menuBar, QString name);

private:
    static Ini *m_singleton;

    QSettings *m_ini;
    QSize maxSize;
    QRect defaultRect;

    explicit Ini(QObject *parent = nullptr);
    ~Ini();

    QString getKey(QString group, QString key);

    void saveAction(QAction *action, QString name);
    void loadAction(QAction *action, QString name);
};

#endif // INI_H

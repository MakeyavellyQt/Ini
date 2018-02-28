#include <QApplication>
#include <QDesktopWidget>

#include "ini.h"

Ini *Ini::m_singleton = 0x0;


Ini::Ini(QObject *parent) :
    QObject(parent)
{
    m_ini = new QSettings(QApplication::organizationName(),
                          QApplication::applicationName());
    maxSize = QApplication::desktop()->size();
    defaultRect.setX(maxSize.width() / 4);
    defaultRect.setY(maxSize.height() / 4);
    defaultRect.setSize(maxSize / 2);
}

Ini::~Ini()
{
    delete m_ini;
}

QString Ini::getKey(QString group, QString key)
{
    return QString("/%1/%2").arg(group).arg(key);
}

void Ini::saveAction(QAction *action, QString name)
{
    if (action->isCheckable()) {
        m_setValue(name, action->objectName(), action->isChecked());
    }
}

void Ini::loadAction(QAction *action, QString name)
{
    if (action->isCheckable()) {
        action->setChecked(m_getValue(name, action->objectName(), false).toBool());
    }
}

QVariant Ini::getValue(QString group, QString key, QVariant defaultValue)
{
    return Ini::get()->m_getValue(group, key, defaultValue);
}

void Ini::setValue(QString group, QString key, QVariant value)
{
    Ini::get()->m_setValue(group, key, value);
}

void Ini::saveGeometry(QWidget *widget, QString name)
{
    Ini::get()->m_saveGeometry(widget, name);
}

void Ini::loadGeometry(QWidget *widget, QString name)
{
    Ini::get()->m_loadGeometry(widget, name);
}

void Ini::saveMenu(QMenu *menu, QString name)
{
    Ini::get()->m_saveMenu(menu, name);
}

void Ini::loadMenu(QMenu *menu, QString name)
{
    Ini::get()->m_loadMenu(menu, name);
}

void Ini::saveMenu(QMenuBar *menuBar, QString name)
{
    Ini::get()->m_saveMenu(menuBar, name);
}

void Ini::loadMenu(QMenuBar *menuBar, QString name)
{
    Ini::get()->m_loadMenu(menuBar, name);
}

Ini *Ini::get()
{
    if (!m_singleton) {
        m_singleton = new Ini();
    }
    return m_singleton;
}

QVariant Ini::m_getValue(QString group, QString key, QVariant defaultValue)
{
    return m_ini->value(getKey(group, key), defaultValue);
}

void Ini::m_setValue(QString group, QString key, QVariant value)
{
    m_ini->setValue(getKey(group, key), value);
    m_ini->sync();
}

void Ini::m_saveGeometry(QWidget *widget, QString name)
{
    m_setValue(name, "x", widget->window()->x());
    m_setValue(name, "y", widget->window()->y());
    m_setValue(name, "width", widget->window()->width());
    m_setValue(name, "height", widget->window()->height());
    m_setValue(name, "maximized", widget->window()->isMaximized());
}

void Ini::m_loadGeometry(QWidget *widget, QString name)
{
    int x = m_getValue(name, "x", defaultRect.x()).toInt();
    int y = m_getValue(name, "y", defaultRect.y()).toInt();
    int w = m_getValue(name, "width", defaultRect.width()).toInt();
    int h = m_getValue(name, "height", defaultRect.height()).toInt();
    bool isMaximized = m_getValue(name, "maximized", false).toBool();
    if (w > maxSize.width())        { w = maxSize.width();      }
    if (h > maxSize.height())       { h = maxSize.height();     }
    if (x + w > maxSize.width())    { x = maxSize.width() - w;  }
    if (y + h > maxSize.height())   { y = maxSize.height() - h; }
    widget->window()->setGeometry(x, y, w, h);
    if (isMaximized) {
        widget->window()->setWindowState(Qt::WindowMaximized);
    }
}

void Ini::m_saveMenu(QMenu *menu, QString name)
{
    foreach (QAction *action, menu->actions()) {
        if (action->menu()) {
            m_saveMenu(action->menu(), name);
        } else {
            saveAction(action, name);
        }
    }
}

void Ini::m_loadMenu(QMenu *menu, QString name)
{
    foreach (QAction *action, menu->actions()) {
        if (action->menu()) {
            m_loadMenu(action->menu(), name);
        } else {
            loadAction(action, name);
        }
    }
}

void Ini::m_saveMenu(QMenuBar *menuBar, QString name)
{
    foreach (QObject *act, menuBar->children()) {
        if (act->inherits("QMenu")) {
            QMenu *menu = static_cast<QMenu*>(act);
            m_saveMenu(menu, name);
        } else if (act->inherits("QAction")) {
            QAction *action = static_cast<QAction*>(act);
            saveAction(action, name);
        }
    }
}

void Ini::m_loadMenu(QMenuBar *menuBar, QString name)
{
    foreach (QObject *act, menuBar->children()) {
        if (act->inherits("QMenu")) {
            QMenu *menu = static_cast<QMenu*>(act);
            m_loadMenu(menu, name);
        } else if (act->inherits("QAction")) {
            QAction *action = static_cast<QAction*>(act);
            loadAction(action, name);
        }
    }
}

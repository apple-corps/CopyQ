/*
    Copyright (c) 2013, Lukas Holecek <hluk@email.cz>

    This file is part of CopyQ.

    CopyQ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CopyQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CopyQ.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ITEMEDITORWIDGET_H
#define ITEMEDITORWIDGET_H

#include <QPersistentModelIndex>
#include <QSharedPointer>
#include <QWidget>

class ItemWidget;
class QAbstractItemModel;
class QPlainTextEdit;

/**
 * Internal editor widget for items.
 */
class ItemEditorWidget : public QWidget
{
    Q_OBJECT
public:
    ItemEditorWidget(const QSharedPointer<ItemWidget> &itemWidget, const QModelIndex &index,
                     bool editNotes, const QFont &font, const QPalette &palette, bool saveOnReturnKey,
                     QWidget *parent = NULL);

    bool isValid() const;

    void commitData(QAbstractItemModel *model) const;

    bool hasChanges() const;

signals:
    void save();
    void cancel();
    void invalidate();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void onItemWidgetDestroyed();
    void saveAndExit();

private:
    QWidget *createEditor(const ItemWidget *itemWidget);
    void initEditor(QWidget *editor, const QFont &font, const QPalette &palette);

    QSharedPointer<ItemWidget> m_itemWidget;
    QPersistentModelIndex m_index;
    QWidget *m_editor;
    QPlainTextEdit *m_noteEditor;
    bool m_saveOnReturnKey;
};

#endif // ITEMEDITORWIDGET_H

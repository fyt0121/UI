#ifndef F_MAINWINWITHVBAR_H
#define F_MAINWINWITHVBAR_H

#include "VerBarWidget.h"
#include <QIcon>
#include <QWidget>
#include <QBoxLayout>
#include <QAction>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
QT_END_NAMESPACE

class FMainWinWithVBar : public QWidget
{
    Q_OBJECT

public:

    enum FCentralLayoutType {
        FHBoxLayout = 0x1,
        FVBoxLayout = 0x2
    };

    FMainWinWithVBar(QWidget *parent = 0, FCentralLayoutType layoutType = FHBoxLayout);
    ~FMainWinWithVBar();

    inline void addCentralWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = 0){
        m_centralLayout->addWidget(widget, stretch, alignment);
    }

    inline void addCentralLayout(QLayout *layout, int stretch = 0){
        m_centralLayout->addLayout(layout, stretch);
    }

    inline void insertTab(int index, const QIcon &icon, const QString &label){
        m_verTabBar->insertTab(index, icon, label);
    }

    inline void insertActionToBar(int index, QAction *action){
        m_toolBar->insertAction(index, action);
    }

    void removeTab(int index);
//    void setBackgroundBrush(const QBrush &brush);
//    void addCornerWidget(QWidget *widget);
//    void insertCornerWidget(int pos, QWidget *widget);
//    int cornerWidgetCount() const;
    //void setTabToolTip(int index, const QString &toolTip);

//    void paintEvent(QPaintEvent *event);

//    int currentIndex() const;

    void setTabEnabled(int index, bool enable);
    bool isTabEnabled(int index) const;

signals:
//    void currentAboutToShow(int index);
//    void currentChanged(int index);

public slots:
//    void setCurrentIndex(int index);
//    void setSelectionWidgetHidden(bool hidden);

private slots:
//    void showWidget(int index);

private:
    QHBoxLayout *m_mainLayout;
    QBoxLayout *m_centralLayout;
    FVerActionBar *m_toolBar;
    FVerTabBar *m_verTabBar;
};

#endif // F_MAINWINWITHVBAR_H

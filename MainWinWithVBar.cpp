
#include "MainWinWithVBar.h"
#include "Utils/stylehelper.h"
//#include <utils/styledbar.h>

#include "codeeditor.h"

#include <QDebug>


#include <QFileSystemModel>
#include <QTreeView>

//#include <QColorDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>

FMainWinWithVBar::FMainWinWithVBar(QWidget *parent, FCentralLayoutType layoutType)
    : QWidget(parent),
      m_mainLayout(new QHBoxLayout(this)),
      m_toolBar(new FVerActionBar(this)),
      m_verTabBar(new FVerTabBar(this))
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    Utils::StyleHelper::setBaseColor(QColor(0, 0, 0));

    if (FHBoxLayout == layoutType){
        m_centralLayout = new QHBoxLayout;
    }else if (FHBoxLayout == layoutType){
        m_centralLayout = new QVBoxLayout;
    }else{
        m_centralLayout = new QHBoxLayout;
    }
    m_centralLayout->setMargin(0);
    m_centralLayout->setSpacing(1);

    QVBoxLayout *vBarLayout = new QVBoxLayout;
    vBarLayout->setSpacing(0);
    vBarLayout->setMargin(0);

    vBarLayout->addWidget(m_toolBar);
    vBarLayout->addWidget(m_verTabBar);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    m_mainLayout->addLayout(vBarLayout);
    m_mainLayout->addLayout(m_centralLayout);
    setLayout(m_mainLayout);

    //connect(m_verTabBar, SIGNAL(currentChanged(int)), this, SLOT(showWidget(int)));

    // test code begin
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/im/images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/im/images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
    QAction  *actionNext = new QAction(this);
    actionNext->setIcon(icon1);
    actionNext->setProperty("bottomTitle","Next");
    QAction  *actionPre = new QAction(this);
    actionPre->setProperty("bottomTitle","Pre");
    actionPre->setIcon(icon2);

    insertActionToBar(0, actionPre);
    insertActionToBar(1, actionNext);

    insertTab(0, icon1, "Pre");
    insertTab(1, icon2, "Next");

    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath("");
    QTreeView *tree = new QTreeView(this);
    tree->setModel(model);

    // Demonstrating look and feel features
    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(true);

    QVBoxLayout *vDirLayout = new QVBoxLayout;
    vDirLayout->addWidget(tree);
    this->addCentralLayout(vDirLayout);
     this->addCentralWidget(new CodeEditor);
}

FMainWinWithVBar::~FMainWinWithVBar()
{
    delete m_mainLayout;
    delete m_centralLayout;
    delete m_toolBar;
    delete m_verTabBar;
}

void FMainWinWithVBar::removeTab(int index)
{
    m_verTabBar->removeTab(index);
}

//int FMainWinWithVBar::currentIndex() const
//{
//    return m_verTabBar->currentIndex();
//}

//void FMainWinWithVBar::setCurrentIndex(int index)
//{
//    if (m_verTabBar->isTabEnabled(index))
//        m_verTabBar->setCurrentIndex(index);
//}

//void FMainWinWithVBar::showWidget(int index)
//{
////    emit currentAboutToShow(index);
//    emit currentChanged(index);
//}

void FMainWinWithVBar::setTabEnabled(int index, bool enable)
{
    m_verTabBar->setTabEnabled(index, enable);
}

bool FMainWinWithVBar::isTabEnabled(int index) const
{
    return m_verTabBar->isTabEnabled(index);
}



#include "VerBarWidget.h"
#include "Utils/stylehelper.h"
#include "Utils/styledbar.h"

#include <QDebug>

#include <QColorDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QStyleFactory>
#include <QPainter>
#include <QSplitter>
#include <QStackedLayout>
#include <QStatusBar>
#include <QToolButton>
#include <QToolTip>
#include <QAnimationGroup>
#include <QPropertyAnimation>
#include <QStyleOption>

FActionButton::FActionButton(QWidget *parent)
    : QToolButton(parent), m_fader(0)
{
    m_hasForceVisible = false;
    setAttribute(Qt::WA_Hover, true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void FActionButton::forceVisible(bool visible)
{
    m_hasForceVisible = true;
    setVisible(visible);
}

bool FActionButton::event(QEvent *e)
{
    switch(e->type()) {
    case QEvent::Enter:
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(125);
            animation->setEndValue(1.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    case QEvent::Leave:
        {
            QPropertyAnimation *animation = new QPropertyAnimation(this, "fader");
            animation->setDuration(125);
            animation->setEndValue(0.0);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    default:
        return QToolButton::event(e);
    }
    return false;
}

void FActionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    // draw borders
//    bool isTitledAction = defaultAction()->property("titledAction").toBool();

#ifndef Q_OS_MAC // Mac UIs usually don't hover
    if (m_fader > 0 && isEnabled() && !isDown() && !isChecked()) {
        painter.save();
        int fader = int(40 * m_fader);
        QLinearGradient grad(rect().topLeft(), rect().topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(255, 255, 255, fader));
        grad.setColorAt(1, Qt::transparent);
        painter.fillRect(rect(), grad);
        painter.setPen(QPen(grad, 1.0));
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.restore();
    } else
#endif
    if (isDown() || isChecked()) {
        painter.save();
        QLinearGradient grad(rect().topLeft(), rect().topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(0, 0, 0, 50));
        grad.setColorAt(1, Qt::transparent);
        painter.fillRect(rect(), grad);
        painter.setPen(QPen(grad, 1.0));
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().topLeft(), rect().topRight());
        painter.drawLine(rect().topLeft() + QPoint(0,1), rect().topRight() + QPoint(0,1));
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        painter.drawLine(rect().topLeft() - QPoint(0,1), rect().topRight() - QPoint(0,1));
        painter.restore();
    }

//    QRect iconRect(0, 0, FACTION_ICON_SIZE, FACTION_ICON_SIZE);
//    // draw popup texts
//    if (isTitledAction) {

//        QFont normalFont(painter.font());
//        QRect centerRect = rect();
//        normalFont.setPointSizeF(Utils::StyleHelper::sidebarFontSize());
//        QFont boldFont(normalFont);
//        boldFont.setBold(true);
//        QFontMetrics fm(normalFont);
//        QFontMetrics boldFm(boldFont);
//        int lineHeight = boldFm.height();
//        int textFlags = Qt::AlignVCenter|Qt::AlignHCenter;

//        const QString projectName = defaultAction()->property("heading").toString();
//        if (!projectName.isNull())
//            centerRect.adjust(0, lineHeight + 4, 0, 0);

//        centerRect.adjust(0, 0, 0, -lineHeight*2 - 4);

//        iconRect.moveCenter(centerRect.center());
//        Utils::StyleHelper::drawIconWithShadow(icon(), iconRect, &painter, isEnabled() ? QIcon::Normal : QIcon::Disabled);
//        painter.setFont(normalFont);

//        QPoint textOffset = centerRect.center() - QPoint(iconRect.width()/2, iconRect.height()/2);
//        textOffset = textOffset - QPoint(0, lineHeight + 4);
//        QRectF r(0, textOffset.y(), rect().width(), lineHeight);
//        QColor penColor;
//        if (isEnabled())
//            penColor = Qt::white;
//        else
//            penColor = Qt::gray;
//        painter.setPen(penColor);

//        // draw project name
//        const int margin = 6;
//        const qreal availableWidth = r.width() - margin;
//        QString ellidedProjectName = fm.elidedText(projectName, Qt::ElideMiddle, availableWidth);
//        if (isEnabled()) {
//            const QRectF shadowR = r.translated(0, 1);
//            painter.setPen(QColor(30, 30, 30, 80));
//            painter.drawText(shadowR, textFlags, ellidedProjectName);
//            painter.setPen(penColor);
//        }
//        painter.drawText(r, textFlags, ellidedProjectName);

//        // draw build configuration name
//        textOffset = iconRect.center() + QPoint(iconRect.width()/2, iconRect.height()/2);
//        QRectF buildConfigRect[2];
//        buildConfigRect[0] = QRectF(0, textOffset.y() + 5, rect().width(), lineHeight);
//        buildConfigRect[1] = QRectF(0, textOffset.y() + 5 + lineHeight, rect().width(), lineHeight);
//        painter.setFont(boldFont);
////        QVector<QString> splitBuildConfiguration(2);
////        const QString buildConfiguration = defaultAction()->property("subtitle").toString();
////        if (boldFm.width(buildConfiguration) <= availableWidth) {
////            // text fits in one line
////            splitBuildConfiguration[0] = buildConfiguration;
////        } else {
////            splitBuildConfiguration = splitInTwoLines(buildConfiguration, boldFm, availableWidth);
////        }
////        // draw the two lines for the build configuration
////        for (int i = 0; i < 2; ++i) {
////            if (splitBuildConfiguration[i].isEmpty())
////                continue;
////            if (isEnabled()) {
////                const QRectF shadowR = buildConfigRect[i].translated(0, 1);
////                painter.setPen(QColor(30, 30, 30, 80));
////                painter.drawText(shadowR, textFlags, splitBuildConfiguration[i]);
////                painter.setPen(penColor);
////            }
////            painter.drawText(buildConfigRect[i], textFlags, splitBuildConfiguration[i]);
////        }

//        const QString buildConfiguration = defaultAction()->property("subtitle").toString();
//            if (isEnabled()) {
//                const QRectF shadowR = buildConfigRect[0].translated(0, 1);
//                painter.setPen(QColor(30, 30, 30, 80));
//                painter.drawText(shadowR, textFlags, buildConfiguration);
//                painter.setPen(penColor);
//            }
//            painter.drawText(buildConfigRect[0], textFlags, buildConfiguration);

//        // pop up arrow next to icon
//        if (!icon().isNull()) {
//            QStyleOption opt;
//            opt.initFrom(this);
//            opt.rect = rect().adjusted(rect().width() - 16, 0, -8, 0);
//            Utils::StyleHelper::drawArrow(QStyle::PE_IndicatorArrowRight, &painter, &opt);
//        }
//    } else {
//        iconRect.moveCenter(rect().center());
//        Utils::StyleHelper::drawIconWithShadow(icon(), iconRect, &painter, isEnabled() ? QIcon::Normal : QIcon::Disabled);
//    }

    QString bottomTitle(defaultAction()->property("bottomTitle").toString());
    QRect rect = this->rect();
    QRect textRect(rect);
    QRect iconRect(textRect);
    textRect.translate(0, -1);
    QFont boldFont(painter.font());
    boldFont.setPointSizeF(Utils::StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    painter.setFont(boldFont);
    painter.setPen(QColor(0, 0, 0, 110));
    int textFlags = Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap;
    painter.drawText(textRect, textFlags, bottomTitle);
    painter.setPen(Utils::StyleHelper::panelTextColor());

#ifndef Q_OS_MAC
    painter.save();
    QLinearGradient grad(rect.topLeft(), rect.topRight());
    grad.setColorAt(0, Qt::transparent);
    grad.setColorAt(0.5, QColor(255, 255, 255, 0));
    grad.setColorAt(1, Qt::transparent);
    painter.fillRect(rect, grad);
    painter.setPen(QPen(grad, 1.0));
    painter.drawLine(rect.topLeft(), rect.topRight());
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
    painter.restore();
#endif

    int textHeight = painter.fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, bottomTitle).height();
    iconRect.adjust(0, 4, 0, -textHeight);
    Utils::StyleHelper::drawIconWithShadow(icon(), iconRect, &painter, QIcon::Normal);

    painter.translate(0, -1);
    painter.drawText(textRect, textFlags, bottomTitle);
}


QSize FActionButton::sizeHint() const
{
    QSizeF buttonSize = iconSize().expandedTo(QSize(64, 38));
    if (defaultAction()->property("titledAction").toBool()) {
        QFont boldFont(font());
        boldFont.setPointSizeF(Utils::StyleHelper::sidebarFontSize());
        boldFont.setBold(true);
        QFontMetrics fm(boldFont);
        qreal lineHeight = fm.height();
        const QString projectName = defaultAction()->property("heading").toString();
        buttonSize += QSizeF(0, 10);
        if (!projectName.isEmpty())
            buttonSize += QSizeF(0, lineHeight + 2);

        buttonSize += QSizeF(0, lineHeight*2 + 2);
    }
    return buttonSize.toSize();
}

QSize FActionButton::minimumSizeHint() const
{
    return QSize(8, 8);
}

void FActionButton::actionChanged()
{
    // the default action changed in some way, e.g. it might got hidden
    // since we inherit a tool button we won't get invisible, so do this here
    if (!m_hasForceVisible) {
        if (QAction* action = defaultAction())
            setVisible(action->isVisible());
    }
}


FVerActionBar::FVerActionBar(QWidget *parent)
    : QWidget(parent),
      m_actionsLayout(new QVBoxLayout)
{
    m_actionsLayout->setMargin(0);
    m_actionsLayout->setSpacing(0);
    setLayout(m_actionsLayout);
    setContentsMargins(0,0,0,0);
}

void FVerActionBar::addProjectSelector(QAction *action)
{
    FActionButton* toolButton = new FActionButton(this);
    toolButton->setDefaultAction(action);
    connect(action, SIGNAL(changed()), toolButton, SLOT(actionChanged()));
    m_actionsLayout->insertWidget(0, toolButton);

}
void FVerActionBar::insertAction(int index, QAction *action)
{
    FActionButton *toolButton = new FActionButton(this);
    toolButton->setDefaultAction(action);
    connect(action, SIGNAL(changed()), toolButton, SLOT(actionChanged()));
    m_actionsLayout->insertWidget(index, toolButton);
}

QLayout *FVerActionBar::actionsLayout() const
{
    return m_actionsLayout;
}

void FVerActionBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    Q_UNUSED(event)
//    QColor light = Utils::StyleHelper::sidebarHighlight();
//    QColor dark = Utils::StyleHelper::sidebarShadow();
//    painter.setPen(dark);
//    painter.drawLine(rect().topLeft(), rect().topRight());
//    painter.setPen(light);
//    painter.drawLine(rect().topLeft() + QPoint(1,1), rect().topRight() + QPoint(0,1));

    QRect rect = this->rect();
    rect = style()->visualRect(layoutDirection(), geometry(), rect);
    Utils::StyleHelper::verticalGradient(&painter, rect, rect);
    painter.setPen(Utils::StyleHelper::borderColor());
    painter.drawLine(rect.topRight(), rect.bottomRight());
    painter.setPen(Utils::StyleHelper::sidebarHighlight());
    painter.drawLine(rect.bottomLeft(), rect.bottomRight());
}

QSize FVerActionBar::minimumSizeHint() const
{
    return sizeHint();
}

const int FVerTabBar::m_rounding = 22;
const int FVerTabBar::m_textPadding = 4;

void FRectTab::fadeIn()
{
    animator.stop();
    animator.setDuration(80);
    animator.setEndValue(40);
    animator.start();
}

void FRectTab::fadeOut()
{
    animator.stop();
    animator.setDuration(160);
    animator.setEndValue(0);
    animator.start();
}

void FRectTab::setFader(float value)
{
    m_fader = value;
    tabbar->update();
}

FVerTabBar::FVerTabBar(QWidget *parent)
    : QWidget(parent)
{
    m_hoverIndex = -1;
    m_currentIndex = -1;
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setStyle(QStyleFactory::create(QLatin1String("windows")));
    setMinimumWidth(qMax(2 * m_rounding, 40));
    setAttribute(Qt::WA_Hover, true);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true); // Needed for hover events
    m_triggerTimer.setSingleShot(true);

    // We use a zerotimer to keep the sidebar responsive
    connect(&m_triggerTimer, SIGNAL(timeout()), this, SLOT(emitCurrentIndex()));
}

FVerTabBar::~FVerTabBar()
{
    delete style();
}

QSize FVerTabBar::tabSizeHint(bool minimum) const
{
    QFont boldFont(font());
    boldFont.setPointSizeF(Utils::StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    QFontMetrics fm(boldFont);
    int spacing = 8;
    int width = 60 + spacing + 2;
    int maxLabelwidth = 0;
    for (int tab=0 ; tab<count() ;++tab) {
        int width = fm.width(tabText(tab));
        if (width > maxLabelwidth)
            maxLabelwidth = width;
    }
    int iconHeight = minimum ? 0 : 32;
    return QSize(qMax(width, maxLabelwidth + 4), iconHeight + spacing + fm.height());
}

void FVerTabBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);

    QRect rect = this->rect();
    rect = style()->visualRect(layoutDirection(), geometry(), rect);
    Utils::StyleHelper::verticalGradient(&p, rect, rect);
    p.setPen(Utils::StyleHelper::borderColor());
    p.drawLine(rect.topRight(), rect.bottomRight());
    p.setPen(Utils::StyleHelper::sidebarHighlight());
    p.drawLine(rect.bottomLeft(), rect.bottomRight());

    for (int i = 0; i < count(); ++i)
        if (i != currentIndex())
            paintTab(&p, i);

    // paint active tab last, since it overlaps the neighbors
    if (currentIndex() != -1)
        paintTab(&p, currentIndex());
}

// Handle hover events for mouse fade ins
void FVerTabBar::mouseMoveEvent(QMouseEvent *e)
{
    int newHover = -1;
    for (int i = 0; i < count(); ++i) {
        QRect area = tabRect(i);
        if (area.contains(e->pos())) {
            newHover = i;
            break;
        }
    }
    if (newHover == m_hoverIndex)
        return;

    if (validIndex(m_hoverIndex))
        m_tabs[m_hoverIndex]->fadeOut();

    m_hoverIndex = newHover;

    if (validIndex(m_hoverIndex)) {
        m_tabs[m_hoverIndex]->fadeIn();
        m_hoverRect = tabRect(m_hoverIndex);
    }
}

bool FVerTabBar::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        if (validIndex(m_hoverIndex)) {
            QString tt = tabToolTip(m_hoverIndex);
            if (!tt.isEmpty()) {
                QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(), tt, this);
                return true;
            }
        }
    }
    return QWidget::event(event);
}

// Resets hover animation on mouse enter
void FVerTabBar::enterEvent(QEvent *e)
{
    Q_UNUSED(e)
    m_hoverRect = QRect();
    m_hoverIndex = -1;
}

// Resets hover animation on mouse enter
void FVerTabBar::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)
    m_hoverIndex = -1;
    m_hoverRect = QRect();
    for (int i = 0 ; i < m_tabs.count() ; ++i) {
        m_tabs[i]->fadeOut();
    }
}

QSize FVerTabBar::sizeHint() const
{
    QSize sh = tabSizeHint();
    return QSize(sh.width(), sh.height() * m_tabs.count());
}

QSize FVerTabBar::minimumSizeHint() const
{
    QSize sh = tabSizeHint(true);
    return QSize(sh.width(), sh.height() * m_tabs.count());
}

QRect FVerTabBar::tabRect(int index) const
{
    QSize sh = tabSizeHint();

    if (sh.height() * m_tabs.count() > height())
        sh.setHeight(height() / m_tabs.count());

    return QRect(0, index * sh.height(), sh.width(), sh.height());

}

// This keeps the sidebar responsive since
// we get a repaint before loading the
// mode itself
void FVerTabBar::emitCurrentIndex()
{
    emit currentChanged(m_currentIndex);
}

void FVerTabBar::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    for (int index = 0; index < m_tabs.count(); ++index) {
        if (tabRect(index).contains(e->pos())) {

            if (isTabEnabled(index)) {
                m_currentIndex = index;
                update();
                m_triggerTimer.start(0);
            }
            break;
        }
    }
}

void FVerTabBar::paintTab(QPainter *painter, int tabIndex) const
{
    if (!validIndex(tabIndex)) {
        qWarning("invalid index");
        return;
    }
    painter->save();

    QRect rect = tabRect(tabIndex);
    bool selected = (tabIndex == m_currentIndex);
    bool enabled = isTabEnabled(tabIndex);

    if (selected) {
        //background
        painter->save();
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, QColor(255, 255, 255, 140));
        grad.setColorAt(1, QColor(255, 255, 255, 210));
        painter->fillRect(rect.adjusted(0, 0, 0, -1), grad);
        painter->restore();

        //shadows
        painter->setPen(QColor(0, 0, 0, 110));
        painter->drawLine(rect.topLeft() + QPoint(1,-1), rect.topRight() - QPoint(0,1));
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        painter->setPen(QColor(0, 0, 0, 40));
        painter->drawLine(rect.topLeft(), rect.bottomLeft());

        //highlights
        painter->setPen(QColor(255, 255, 255, 50));
        painter->drawLine(rect.topLeft() + QPoint(0, -2), rect.topRight() - QPoint(0,2));
        painter->drawLine(rect.bottomLeft() + QPoint(0, 1), rect.bottomRight() + QPoint(0,1));
        painter->setPen(QColor(255, 255, 255, 40));
        painter->drawLine(rect.topLeft() + QPoint(0, 0), rect.topRight());
        painter->drawLine(rect.topRight() + QPoint(0, 1), rect.bottomRight() - QPoint(0, 1));
        painter->drawLine(rect.bottomLeft() + QPoint(0,-1), rect.bottomRight()-QPoint(0,1));
    }

    QString tabText(this->tabText(tabIndex));
    QRect tabTextRect(tabRect(tabIndex));
    QRect tabIconRect(tabTextRect);
    tabTextRect.translate(0, -2);
    QFont boldFont(painter->font());
    boldFont.setPointSizeF(Utils::StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    painter->setFont(boldFont);
    painter->setPen(selected ? QColor(255, 255, 255, 160) : QColor(0, 0, 0, 110));
    int textFlags = Qt::AlignCenter | Qt::AlignBottom | Qt::TextWordWrap;
    if (enabled) {
        painter->drawText(tabTextRect, textFlags, tabText);
        painter->setPen(selected ? QColor(60, 60, 60) : Utils::StyleHelper::panelTextColor());
    } else {
        painter->setPen(selected ? Utils::StyleHelper::panelTextColor() : QColor(255, 255, 255, 120));
    }
#ifndef Q_OS_MAC
    if (!selected && enabled) {
        painter->save();
        int fader = int(m_tabs[tabIndex]->fader());
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, Qt::transparent);
        grad.setColorAt(0.5, QColor(255, 255, 255, fader));
        grad.setColorAt(1, Qt::transparent);
        painter->fillRect(rect, grad);
        painter->setPen(QPen(grad, 1.0));
        painter->drawLine(rect.topLeft(), rect.topRight());
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());
        painter->restore();
    }
#endif

    if (!enabled)
        painter->setOpacity(0.7);

    int textHeight = painter->fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, tabText).height();
    tabIconRect.adjust(0, 4, 0, -textHeight);
    Utils::StyleHelper::drawIconWithShadow(tabIcon(tabIndex), tabIconRect, painter, enabled ? QIcon::Normal : QIcon::Disabled);

    painter->translate(0, -1);
    painter->drawText(tabTextRect, textFlags, tabText);
    painter->restore();
}

void FVerTabBar::setCurrentIndex(int index) {
    if (isTabEnabled(index)) {
        m_currentIndex = index;
        update();
        emit currentChanged(m_currentIndex);
    }
}

void FVerTabBar::setTabEnabled(int index, bool enable)
{
    Q_ASSERT(index < m_tabs.size());
    Q_ASSERT(index >= 0);

    if (index < m_tabs.size() && index >= 0) {
        m_tabs[index]->enabled = enable;
        update(tabRect(index));
    }
}

bool FVerTabBar::isTabEnabled(int index) const
{
    Q_ASSERT(index < m_tabs.size());
    Q_ASSERT(index >= 0);

    if (index < m_tabs.size() && index >= 0)
        return m_tabs[index]->enabled;

    return false;
}

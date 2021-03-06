#include "bluestyle.h"
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include <QComboBox>
#include <QStyleFactory>
BlueStyle::BlueStyle():QProxyStyle(QStyleFactory::create("windows"))
{

}

BlueStyle::~BlueStyle()
{

}

void BlueStyle::polish(QPalette &palette)
{
    QColor brown(212, 140, 95);
    QColor beige(236, 182, 120);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/image/背景.jpg");
    QPixmap buttonImage(":/image/Button.jpg");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();
    palette = QPalette(/*brown*/Qt::cyan);
    //used for foreground text
    palette.setBrush(QPalette::BrightText, Qt::white);
    //used for filling text editors, item views, etc
    palette.setBrush(QPalette::Base, /*beige*/ Qt::cyan);
    palette.setBrush(QPalette::Highlight, Qt::darkGreen);
    setTexture(palette, QPalette::Button, buttonImage);
    setTexture(palette, QPalette::Mid, midImage);
    setTexture(palette, QPalette::Window, backgroundImage);
    //used for the background of most widgets
    QBrush brush = palette.background();
    brush.setColor(brush.color().dark());

    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
}
//鼠标盘旋状态 初始化给定窗口部件的外观
//该函数在每一个窗口完全创建之后的某个时刻并且是该窗口部件每一次创建后首次显示之前调用
void BlueStyle::polish(QWidget *widget)
{
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
    {
        widget->setAttribute(Qt::WA_Hover,true);
    }
}
//鼠标盘旋状态解除
void BlueStyle::unpolish(QWidget *widget)
{
    if (qobject_cast<QPushButton*>(widget) || qobject_cast<QComboBox*>(widget))
    {
        widget->setAttribute(Qt::WA_Hover,false);
    }
}
//返回给定像素的公制值
int BlueStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    switch (metric) {
    case PM_ComboBoxFrameWidth://Frame width of a combo box, defaults to PM_DefaultFrameWidth
        return 8;
    case PM_ScrollBarExtent://Frame width of a combo box, defaults to PM_DefaultFrameWidth
        return QProxyStyle::pixelMetric(metric, option, widget) + 4;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}
//用给定的option核painter来绘制 primitive element.
void BlueStyle::drawPrimitive(PrimitiveElement element,
                              const QStyleOption *option, //contains everything we need to know about the widget we want to draw on
                              QPainter *painter,
                              const QWidget *widget) const//QMacStyle uses it to animate default buttons  don't need
{
    switch (element) {
    case PE_PanelButtonCommand:
        {
            int delta = (option->state & State_MouseOver) ? 64 : 0;
            QColor slightlyOpaqueBlack(0, 0, 0, 63);
            QColor semiTransparentWhite(255, 255, 255, 127 + delta);
            QColor semiTransparentBlack(0, 0, 0, 127 - delta);

            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);
            QPainterPath roundRect = roundRectPath(option->rect);//vectorial specification of a shape 私有静态函数绘制圆角
            int radius = qMin(width, height) / 2;

            QBrush brush;
            bool darker;

            const QStyleOptionButton *buttonOption =
                    qstyleoption_cast<const QStyleOptionButton *>(option);//选择的元器件如果是按钮类型

            if (buttonOption
                    && (buttonOption->features & QStyleOptionButton::Flat)) {//平按钮
                brush = option->palette.background();//平按钮与背景同样
                darker = (option->state & (State_Sunken | State_On));//变成暗色的当按下或  Checked？
            } else {
                if (option->state & (State_Sunken | State_On)) {
                    brush = option->palette.mid();
                    darker = !(option->state & State_Sunken);
                } else {
                    brush = option->palette.button();
                    darker = false;
                }
            }

            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);//reduces the visual distortion 反模糊计数
            painter->fillPath(roundRect, brush);
            if (darker)
                painter->fillPath(roundRect, slightlyOpaqueBlack);

            int penWidth;
            if (radius < 10)
                penWidth = 3;
            else if (radius < 20)
                penWidth = 5;
            else
                penWidth = 7;

            QPen topPen(semiTransparentWhite, penWidth);
            QPen bottomPen(semiTransparentBlack, penWidth);

            if (option->state & (State_Sunken | State_On))
                qSwap(topPen, bottomPen);

            int x1 = x;
            int x2 = x + radius;
            int x3 = x + width - radius;
            int x4 = x + width;

            if (option->direction == Qt::RightToLeft) {
                qSwap(x1, x4);
                qSwap(x2, x3);
            }

            QPolygon topHalf;
            topHalf << QPoint(x1, y)
                    << QPoint(x4, y)
                    << QPoint(x3, y + radius)
                    << QPoint(x2, y + height - radius)
                    << QPoint(x1, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(topHalf, Qt::IntersectClip);
            painter->setPen(topPen);
            painter->drawPath(roundRect);

            QPolygon bottomHalf = topHalf;
            bottomHalf[0] = QPoint(x4, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(bottomHalf, Qt::IntersectClip);
            painter->setPen(bottomPen);
            painter->drawPath(roundRect);

            painter->setPen(option->palette.foreground().color());
            painter->setClipping(false);
            painter->drawPath(roundRect);

            painter->restore();
        }
        break;
    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}
// draw the text on a QPushButton in a bright color when the button is down or checked.

void BlueStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_PushButtonLabel:
        {
            QStyleOptionButton myButtonOption;
            const QStyleOptionButton *buttonOption =
                    qstyleoption_cast<const QStyleOptionButton *>(option);
            if (buttonOption) {
                myButtonOption = *buttonOption;
                if (myButtonOption.palette.currentColorGroup()
                        != QPalette::Disabled) {
                    if (myButtonOption.state & (State_Sunken | State_On)) {
                        myButtonOption.palette.setBrush(QPalette::ButtonText,
                                myButtonOption.palette.brightText());
                    }
                }
            }
            QProxyStyle::drawControl(element, &myButtonOption, painter, widget);
        }
        break;
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
    }

}

int BlueStyle::styleHint(StyleHint hint, const QStyleOption *option,const QWidget *widget,QStyleHintReturn *returnData) const
{
    switch (hint) {
    case SH_DitherDisabledText:
        return int(false);
    case SH_EtchDisabledText:
        return int(true);
    default:
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}

void BlueStyle::setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap)
{
    for (int i = 0; i < QPalette::NColorGroups; ++i) {
        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
    }
}

QPainterPath BlueStyle::roundRectPath(const QRect &rect)
{
    const int radius = /*qMin(rect.width(), rect.height()) / 2;*/ 3;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
/*    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);*/
    //带圆形倒角的按钮
    path.moveTo();
    path.closeSubpath();
    return path;
}


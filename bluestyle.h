#ifndef BLUESTYLE_H
#define BLUESTYLE_H

#include <QWidget>
#include <QProxyStyle>

class BlueStyle :public QProxyStyle
{
    Q_OBJECT
public:
    BlueStyle();
    ~BlueStyle();
    void polish(QPalette &palette) Q_DECL_OVERRIDE;//指定配色方案
    void polish(QWidget *)Q_DECL_OVERRIDE;//样式应用时调用
    void unpolish(QWidget *)Q_DECL_OVERRIDE;//动态改变样式，撤销polish的影响
    //返回像素值，影响窗口部件的绘制
    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const Q_DECL_OVERRIDE;
    //返回关于样式外观的提示 how to draw the widgets
    int styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const Q_DECL_OVERRIDE;
    //draw various fundamental graphical elements.
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,QPainter *painter, const QWidget *widge)const Q_DECL_OVERRIDE;
    //is a part of a widget that performs some action or displays information to the user
    void drawControl(ControlElement control, const QStyleOption *option,QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;
private:
  //  The setTexture() function is a private function that sets the texture for a certain color role,
  //  while preserving the existing color in the QBrush. A QBrush can hold both a solid color and a
  //  texture at the same time. The solid color is used for drawing text and other graphical elements
  //  where textures don't look good.
    static void setTexture(QPalette &palette, QPalette::ColorRole role,const QPixmap &pixmap);
    static QPainterPath roundRectPath(const QRect &rect);
};

#endif // BLUESTYLE_H

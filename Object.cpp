#include <Windows.h>
#include "glut.h"
#include "Object.h"
#include "RenderingUtils.h"


Object::Object(int _timeIndex, double _price)
: timeIndex(_timeIndex), price(_price)
{
}

bool Object::IsInScreen(int latestBarIndex, int numBarsToDraw)
{
    return (timeIndex < latestBarIndex && timeIndex > latestBarIndex - numBarsToDraw);
}


TextObj::TextObj(std::string _str, int timeIndex, double price)
: Object(timeIndex, price), str(_str)
{
}

void TextObj::Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue)
{
    color.SetOGLColor();
    
    float x = 1 - (latestBarIndex - timeIndex) / (float)numBarsToDraw;
    float y = (price - minValue) / (maxValue - minValue);

    Print(str, x, y);
}


OrderBar::OrderBar(int timeIndex, double price, double _takeProfit, double _stopLoss)
: Object(timeIndex, price), takeProfit(_takeProfit), stopLoss(_stopLoss)
{
}

void OrderBar::Render(int latestBarIndex, int numBarsToDraw, double minValue, double maxValue)
{
    color.SetOGLColor();
    
    float x1  = 1 - (latestBarIndex - timeIndex) / (float)numBarsToDraw;
    float x2  = 1 - (latestBarIndex - closeTimeIndex) / (float)numBarsToDraw;
    float y1 = (price      - minValue) / (maxValue - minValue);
    float y2 = (takeProfit - minValue) / (maxValue - minValue);
    float y3 = (stopLoss   - minValue) / (maxValue - minValue);

    DrawArrow(x1, y1, x1, y2, PixelsToWorldX(10), PixelsToWorldY(10));
    DrawLine(x1, y1, x1, y3);

    glColor4f(color.r, color.g, color.b, 0.2f);
    
    // if was profitable
    if ((takeProfit > price && closePrice > price) || (takeProfit < price && closePrice < price))
    {
        DrawTriangle(x1, y1, x1, y2, x2, y2);
    }
    else
    {
        DrawTriangle(x1, y1, x1, y3, x2, y3);
    }
}

void OrderBar::OrderClosed(int timeIndex, double price)
{
    closeTimeIndex = timeIndex;
    closePrice = price;
}
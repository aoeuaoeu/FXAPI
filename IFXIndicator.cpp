#include <cmath>
#include "IFXIndicator.h"
#include "RenderingUtils.h"


double IFXIndicator::GetSampleAtIndex(int n)
{
    if (n >= (int)values.size())
        return 0;
    return values[n];
}

void IFXIndicator::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    float lastPointX = -1; 
    float lastPointY = -1;

    float halfBoxWidth = PixelsToWorldX(2);
    float halfBoxHeight = PixelsToWorldY(2);

    ::SetColor(color);
    for (int i = 0; i < numBarsToDraw; ++ i)
    {
        if (i > index)
            break;

        double sample = GetSampleAtIndex(index - i);
        float x = 1 - i / (float)numBarsToDraw;
        float y = (sample - minValue) / (maxValue - minValue);

        if (lastPointX < 0)
        {
            lastPointX = x;
            lastPointY = y;
        }
        else
        {
            DrawLine(x, y, lastPointX, lastPointY);

            lastPointX = x;
            lastPointY = y;
        }

        DrawRectangle(x - halfBoxWidth, y - halfBoxHeight, x + halfBoxWidth, y + halfBoxHeight);
    }
}

double IFXIndicator::GetMinValueInRange(int start, int end)
{
    double minValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1 - start; i >= 0 && count < end - start; -- i, ++ count)
    {
        if (values[i] < minValue)
            minValue = values[i];
    }

    return minValue;
}

double IFXIndicator::GetMaxValueInRange(int start, int end)
{
    double maxValue = HUGE_VAL;

    int count = 0;
    for (int i = (int)values.size() - 1 - start; i >= 0 && count < end - start; -- i, ++ count)
    {
        if (values[i] > maxValue)
            maxValue = values[i];
    }

    return maxValue;
}

void IFXIndicator::SetColor(int r, int g, int b)
{
    color.SetColor(r, g, b);
}
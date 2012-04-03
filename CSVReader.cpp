#include "CSVReader.h"
#include <cassert>


CSVReader::CSVReader(std::string _filename, Timeframe timeFrame)
: DataReader(timeFrame), filename(_filename)
{
}

void CSVReader::Init()
{
    in.open(filename.c_str());
    assert(in.is_open());

    in.getline(buffer, 256);   // read the header
}

void CSVReader::Cleanup()
{
    DataReader::Cleanup();

    if (in.is_open())
        in.close();
}

double CSVReader::GetNextTick()
{
    in.getline(buffer, 256);

    // use CLOSE as tick price (5th column)
    int colIndex = 0;
    int begin, end;
    for (int i = 0; i < 256; ++ i)
    {
        if (buffer[i] == ';')
        {
            colIndex ++;
            if (colIndex == 4)
                begin = i + 1;
            else if (colIndex == 5)
            {
                end = i;
                break;
            }
        }
    }

    buffer[end] = '\0';
    double sample = atof(buffer + begin);
    buffer[end] = ';';

    PushDataSample(sample);

    return sample;
}

bool CSVReader::EndOfData()
{
    return in.eof();
}
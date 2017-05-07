#include "chop.h"
#include <QDebug>

void chop(Paintdata& data)
{
    QColor buffer = data.painter->pen().color();

    std::vector<line_info> line_data = form_info(data);
    for (size_t i = 0; i < data.lines.size(); ++i) {
        if (line_data[i].fully_visible()) {
            data.painter->setPen(QColor("red"));
            data.painter->drawLine(data.lines[i]);
        }
        else if (line_data[i].fully_invisible()) {
            data.painter->setPen(QColor("blue"));
            data.painter->drawLine(data.lines[i]);
        }
        else {
            data.painter->setPen(QColor("black"));
            data.painter->drawLine(data.lines[i]);
        }
    }

    data.painter->setPen(buffer);
}

std::vector<line_info> form_info(Paintdata& data)
{
    std::vector<line_info> result;

    for (QLine& line : data.lines) {
        line_info buffer(line, data.rectangle);
        result.push_back(buffer);
    }

    return result;
}

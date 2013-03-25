#include <math.h>
#include <QtGui>

#ifndef M_PI
#define M_PI 3.1415927
#endif

#include "PieView.h"

PieView::PieView(QWidget *parent)
    : QAbstractItemView(parent)
{
   horizontalScrollBar()->setRange(0, 0);
   verticalScrollBar()->setRange(0, 0);

   mMargin = 20;
   mTotalSize = 300;
   mPieSize = mTotalSize - 2*mMargin;
   mValidItems = 0;
   mTotalValue = 0.0;
   mRubberBand = 0;
   mStartAngle = 90.0;
   mKeyPosition = BOTTOM;
   
   // Setup title
   mTitle.setParent( this );
   QFont font;
   font.setPointSize( 13 );
   mTitle.setFont( font );
   mTitle.move( 5, 5 );
}

void PieView::setTitle( const QString& aTitle )
{
    mTitle.setText( aTitle );
}

void PieView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);

    mValidItems = 0;
    mTotalValue = 0.0;

    for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {

        QModelIndex index = model()->index(row, 1, rootIndex());
        double value = model()->data(index).toDouble();

        if (value > 0.0) {
            mTotalValue += value;
            mValidItems++;
        }
    }
    viewport()->update();
}

bool PieView::edit(const QModelIndex &index, EditTrigger trigger, QEvent *event)
{
    if (index.column() == 0)
        return QAbstractItemView::edit(index, trigger, event);
    else
        return false;
}

/*
    Returns the item that covers the coordinate given in the view.
*/

QModelIndex PieView::indexAt(const QPoint &point) const
{
    if (mValidItems == 0)
        return QModelIndex();

    // Transform the view coordinates into contents widget coordinates.
    int wx = point.x() + horizontalScrollBar()->value();
    int wy = point.y() + verticalScrollBar()->value();

    if (wx < mTotalSize) {
        double cx = wx - mTotalSize/2;
        double cy = mTotalSize/2 - wy; // positive cy for items above the center

        // Determine the distance from the center point of the pie chart.
        double d = pow(pow(cx, 2) + pow(cy, 2), 0.5);

        if (d == 0 || d > mPieSize/2)
            return QModelIndex();

        // Determine the angle of the point.
        double angle = (180 / M_PI) * acos(cx/d);
        if (cy < 0)
            angle = 360 - angle;

        // Find the relevant slice of the pie.
        double startAngle = mStartAngle;
        for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {

            QModelIndex index = model()->index(row, 1, rootIndex());
            double value = model()->data(index).toDouble();

            if (value > 0.0) {
                double sliceAngle = 360*value/mTotalValue;

                if (angle >= startAngle && angle < (startAngle + sliceAngle))
                    return model()->index(row, 1, rootIndex());

                startAngle += sliceAngle;
            }
        }
    } else {
        double itemHeight = QFontMetrics(viewOptions().font).height();
        int listItem = int((wy - mMargin) / itemHeight);
        int validRow = 0;

        for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {

            QModelIndex index = model()->index(row, 1, rootIndex());
            if (model()->data(index).toDouble() > 0.0) {

                if (listItem == validRow)
                    return model()->index(row, 0, rootIndex());

                // Update the list index that corresponds to the next valid row.
                validRow++;
            }
        }
    }

    return QModelIndex();
}

bool PieView::isIndexHidden(const QModelIndex & /*index*/) const
{
    return false;
}

/*
    Returns the rectangle of the item at position \a index in the
    model. The rectangle is in contents coordinates.
*/
QRect PieView::itemRect(const QModelIndex &index) const
{
    if (!index.isValid())
        return QRect();

    // Check whether the index's row is in the list of rows represented
    // by slices.
    QModelIndex valueIndex;

    if (index.column() != 1)
        valueIndex = model()->index(index.row(), 1, rootIndex());
    else
        valueIndex = index;

    if (model()->data(valueIndex).toDouble() > 0.0) {

        int listItem = 0;
        for (int row = index.row()-1; row >= 0; --row) {
            if (model()->data(model()->index(row, 1, rootIndex())).toDouble() > 0.0)
                listItem++;
        }

        double itemHeight;
        QRect rect;
        switch (index.column())
        {
        case 0:
            itemHeight = QFontMetrics(viewOptions().font).height();
            switch( mKeyPosition )
            {
            case RIGHT:
                rect = QRect(mTotalSize, int(mMargin + listItem*itemHeight), mTotalSize - mMargin*2, int(itemHeight));
                break;
            case BOTTOM:
                rect = QRect(mMargin, int(mTotalSize + listItem*itemHeight), mTotalSize - mMargin*2, int(itemHeight));
                break;
            }
            return rect;
        case 1:
            return viewport()->rect();
        }

    }
    return QRect();
}

QRegion PieView::itemRegion(const QModelIndex &index) const
{
    if (!index.isValid())
        return QRegion();

    if (index.column() != 1)
        return itemRect(index);

    if (model()->data(index).toDouble() <= 0.0)
        return QRegion();

    double startAngle = mStartAngle;
    for (int row = 0; row < model()->rowCount(rootIndex()); ++row) {

        QModelIndex sliceIndex = model()->index(row, 1, rootIndex());
        double value = model()->data(sliceIndex).toDouble();

        if (value > 0.0) {
            double angle = 360*value/mTotalValue;

            if (sliceIndex == index) {
                QPainterPath slicePath;
                slicePath.moveTo(mTotalSize/2, mTotalSize/2);
                slicePath.arcTo(mMargin, mMargin, mMargin+mPieSize, mMargin+mPieSize,
                                startAngle, angle);
                slicePath.closeSubpath();

                return QRegion(slicePath.toFillPolygon().toPolygon());
            }

            startAngle += angle;
        }
    }

    return QRegion();
}

int PieView::horizontalOffset() const
{
    return horizontalScrollBar()->value();
}

void PieView::mousePressEvent(QMouseEvent *event)
{
    QAbstractItemView::mousePressEvent(event);
    mOrigin = event->pos();
    if (!mRubberBand)
        mRubberBand = new QRubberBand(QRubberBand::Rectangle, viewport());
    mRubberBand->setGeometry(QRect(mOrigin, QSize()));
    mRubberBand->show();
}

void PieView::mouseMoveEvent(QMouseEvent *event)
{
    if (mRubberBand)
        mRubberBand->setGeometry(QRect(mOrigin, event->pos()).normalized());
    QAbstractItemView::mouseMoveEvent(event);
}

void PieView::mouseReleaseEvent(QMouseEvent *event)
{
    QAbstractItemView::mouseReleaseEvent(event);
    if (mRubberBand)
        mRubberBand->hide();
    viewport()->update();
}

QModelIndex PieView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                Qt::KeyboardModifiers /*modifiers*/)
{
    QModelIndex current = currentIndex();

    switch (cursorAction) {
        case MoveLeft:
        case MoveUp:
            if (current.row() > 0)
                current = model()->index(current.row() - 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(0, current.column(), rootIndex());
            break;
        case MoveRight:
        case MoveDown:
            if (current.row() < rows(current) - 1)
                current = model()->index(current.row() + 1, current.column(),
                                         rootIndex());
            else
                current = model()->index(rows(current) - 1, current.column(),
                                         rootIndex());
            break;
        default:
            break;
    }

    viewport()->update();
    return current;
}

void PieView::paintEvent(QPaintEvent *event)
{
    // Set size
    switch( mKeyPosition )
    {
    case RIGHT:
        mTotalSize = rect().width()/2;
        break;
    case BOTTOM:
        mTotalSize = rect().width();
        break;
    }
    mPieSize = mTotalSize - 2*mMargin;

    QItemSelectionModel *selections = selectionModel();
    QStyleOptionViewItem option = viewOptions();
    QStyle::State state = option.state;

    QBrush background = option.palette.base();
    QPen foreground(option.palette.color(QPalette::WindowText));
    QPen textPen(option.palette.color(QPalette::Text));
    QPen highlightedPen(option.palette.color(QPalette::HighlightedText));

    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), background);
    painter.setPen(foreground);

    // Viewport rectangles
    QRect pieRect = QRect(mMargin, mMargin, mPieSize, mPieSize);
    if (mValidItems > 0)
    {
        painter.save();
        painter.translate(pieRect.x() - horizontalScrollBar()->value(),
                          pieRect.y() - verticalScrollBar()->value());
        painter.drawEllipse(0, 0, mPieSize, mPieSize);
        double startAngle = mStartAngle;
        int row;

        for (row = 0; row < model()->rowCount(rootIndex()); ++row) {

            QModelIndex index = model()->index(row, 1, rootIndex());
            double value = model()->data(index).toDouble();

            if (value > 0.0) {
                double angle = 360*value/mTotalValue;

                QModelIndex colorIndex = model()->index(row, 0, rootIndex());
                QColor color = QColor(model()->data(colorIndex,
                                Qt::DecorationRole).toString());

                if (currentIndex() == index)
                    painter.setBrush(QBrush(color, Qt::Dense4Pattern));
                else if (selections->isSelected(index))
                    painter.setBrush(QBrush(color, Qt::Dense3Pattern));
                else
                    painter.setBrush(QBrush(color));

                painter.drawPie(0, 0, mPieSize, mPieSize, int(startAngle*16), int(angle*16));

                startAngle += angle;
            }
        }
        painter.restore();

        int keyNumber = 0;
        for (row = 0; row < model()->rowCount(rootIndex()); ++row)
        {
            QModelIndex index = model()->index(row, 1, rootIndex());
            double value = model()->data(index).toDouble();

            if (value > 0.0) {
                QModelIndex labelIndex = model()->index(row, 0, rootIndex());
                QStyleOptionViewItem option = viewOptions();
                option.rect = visualRect(labelIndex);
                if (selections->isSelected(labelIndex))
                    option.state |= QStyle::State_Selected;
                if (currentIndex() == labelIndex)
                    option.state |= QStyle::State_HasFocus;
                itemDelegate()->paint(&painter, option, labelIndex);
                keyNumber++;
            }
        }
    }
}

void PieView::resizeEvent(QResizeEvent * /* event */)
{
    updateGeometries();
}

int PieView::rows(const QModelIndex &index) const
{
    return model()->rowCount(model()->parent(index));
}

void PieView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    for (int row = start; row <= end; ++row) {

        QModelIndex index = model()->index(row, 1, rootIndex());
        double value = model()->data(index).toDouble();

        if (value > 0.0) {
            mTotalValue += value;
            mValidItems++;
        }
    }

    QAbstractItemView::rowsInserted(parent, start, end);
}

void PieView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    for (int row = start; row <= end; ++row) {

        QModelIndex index = model()->index(row, 1, rootIndex());
        double value = model()->data(index).toDouble();
        if (value > 0.0) {
            mTotalValue -= value;
            mValidItems--;
        }
    }
    QAbstractItemView::rowsAboutToBeRemoved(parent, start, end);
}

void PieView::scrollContentsBy(int dx, int dy)
{
    viewport()->scroll(dx, dy);
}

void PieView::scrollTo(const QModelIndex &index, ScrollHint)
{
    QRect area = viewport()->rect();
    QRect rect = visualRect(index);

    if (rect.left() < area.left())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + rect.left() - area.left());
    else if (rect.right() > area.right())
        horizontalScrollBar()->setValue(
            horizontalScrollBar()->value() + qMin(
                rect.right() - area.right(), rect.left() - area.left()));

    if (rect.top() < area.top())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + rect.top() - area.top());
    else if (rect.bottom() > area.bottom())
        verticalScrollBar()->setValue(
            verticalScrollBar()->value() + qMin(
                rect.bottom() - area.bottom(), rect.top() - area.top()));

    update();
}

/*
    Find the indices corresponding to the extent of the selection.
*/
void PieView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    // Use content widget coordinates because we will use the itemRegion()
    // function to check for intersections.
    QRect contentsRect = rect.translated(
                            horizontalScrollBar()->value(),
                            verticalScrollBar()->value()).normalized();

    int rows = model()->rowCount(rootIndex());
    int columns = model()->columnCount(rootIndex());
    QModelIndexList indexes;

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            QModelIndex index = model()->index(row, column, rootIndex());
            QRegion region = itemRegion(index);
            if (!region.intersect(contentsRect).isEmpty())
                indexes.append(index);
        }
    }

    if (indexes.size() > 0) {
        int firstRow = indexes[0].row();
        int lastRow = indexes[0].row();
        int firstColumn = indexes[0].column();
        int lastColumn = indexes[0].column();

        for (int i = 1; i < indexes.size(); ++i) {
            firstRow = qMin(firstRow, indexes[i].row());
            lastRow = qMax(lastRow, indexes[i].row());
            firstColumn = qMin(firstColumn, indexes[i].column());
            lastColumn = qMax(lastColumn, indexes[i].column());
        }

        QItemSelection selection(
            model()->index(firstRow, firstColumn, rootIndex()),
            model()->index(lastRow, lastColumn, rootIndex()));
        selectionModel()->select(selection, command);
    } else {
        QModelIndex noIndex;
        QItemSelection selection(noIndex, noIndex);
        selectionModel()->select(selection, command);
    }

    update();
}

void PieView::updateGeometries()
{
    horizontalScrollBar()->setPageStep(viewport()->width());
    horizontalScrollBar()->setRange(0, qMax(0, 2*mTotalSize - viewport()->width()));
    verticalScrollBar()->setPageStep(viewport()->height());
    verticalScrollBar()->setRange(0, qMax(0, mTotalSize - viewport()->height()));
}

int PieView::verticalOffset() const
{
    return verticalScrollBar()->value();
}

/*
    Returns the position of the item in viewport coordinates.
*/
QRect PieView::visualRect(const QModelIndex &index) const
{
    QRect rect = itemRect(index);
    if (rect.isValid())
        return QRect(rect.left() - horizontalScrollBar()->value(),
                     rect.top() - verticalScrollBar()->value(),
                     rect.width(), rect.height());
    else
        return rect;
}

/*
    Returns a region corresponding to the selection in viewport coordinates.
*/
QRegion PieView::visualRegionForSelection(const QItemSelection &selection) const
{
    int ranges = selection.count();

    if (ranges == 0)
        return QRect();

    QRegion region;
    for (int i = 0; i < ranges; ++i) {
        QItemSelectionRange range = selection.at(i);
        for (int row = range.top(); row <= range.bottom(); ++row) {
            for (int col = range.left(); col <= range.right(); ++col) {
                QModelIndex index = model()->index(row, col, rootIndex());
                region += visualRect(index);
            }
        }
    }
    return region;
}
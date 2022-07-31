#include "graphicalobject.h"
#include <cmath>

GraphicalObject::GraphicalObject()
    : posX(0.0)
    , posY(0.0)
    , scaleX(0.0)
    , scaleY(0.0)
    , rotation(0.0)
{
    createIdentityMatrix();
}

void GraphicalObject::draw(QPainter *qp)
{
    calculateTransVertices();

    size_t size = transVertices.size();

    for (size_t i = 0; i < size; i++)
    {
        if (i == 0)
        {
            continue;
        }
        qp->drawLine(transVertices[i - 1].x,
                     transVertices[i - 1].y,
                     transVertices[i].x,
                     transVertices[i].y);
    }
    qp->drawLine(transVertices[0].x,
                 transVertices[0].y,
                 transVertices[size - 1].x,
                 transVertices[size - 1].y);
}

void GraphicalObject::createIdentityMatrix()
{
    MatrixEntry entry;
    entry.x = 1;
    identityMatrix.push_back(entry);

    entry.x = 0;
    entry.y = 1;
    identityMatrix.push_back(entry);

    entry.y = 0;
    entry.z = 1;
    identityMatrix.push_back(entry);
}

void GraphicalObject::createTranslationMatrix()
{
    translationMatrix.clear();
    std::copy(identityMatrix.begin(), identityMatrix.end(), std::back_inserter(translationMatrix));
    translationMatrix[2].x = posX;
    translationMatrix[2].y = posY;
}

void GraphicalObject::createScaleMatrix()
{
    scaleMatrix.clear();
    std::copy(identityMatrix.begin(), identityMatrix.end(), std::back_inserter(scaleMatrix));
    scaleMatrix[0].x = scaleX;
    scaleMatrix[1].y = scaleY;
}

void GraphicalObject::createRotationMatrix()
{
    rotationMatrix.clear();
    double angleInRadians = rotation * 0.017453;

    std::copy(identityMatrix.begin(), identityMatrix.end(), std::back_inserter(rotationMatrix));
    rotationMatrix[0].x = cos(angleInRadians);
    rotationMatrix[0].y = sin(angleInRadians);
    rotationMatrix[1].x = -1 * sin(angleInRadians);
    rotationMatrix[1].y = cos(angleInRadians);
}

void GraphicalObject::calculateTransVertices()
{
    createTranslationMatrix();
    createScaleMatrix();
    createRotationMatrix();
    for (size_t i = 0; i < vertices.size(); i++)
    {
        MatrixEntry entry;
        entry.x = vertices[i].x;
        entry.y = vertices[i].y;
        entry.z = 1;

        //TO DO Переделать на работу с одной структурой
        // типа multipleMatrix(scaleResult, scaleResult, rotationMatrix) и протестировать

        MatrixEntry scaleResult;
        multipleMatrix(scaleResult, entry, scaleMatrix);

        MatrixEntry rotationResult;
        multipleMatrix(rotationResult, scaleResult, rotationMatrix);

        MatrixEntry translationResult;
        multipleMatrix(translationResult, rotationResult, translationMatrix);

        Point newPoint(translationResult.x, translationResult.y);
        transVertices.push_back(newPoint);
    }
}

void GraphicalObject::multipleMatrix(MatrixEntry &result,
                                     const MatrixEntry &entry,
                                     const std::vector<MatrixEntry> &matrix)
{
    result.x = matrix[0].x * entry.x + matrix[1].x * entry.y + entry.z * matrix[2].x;
    result.y = matrix[0].y * entry.x + matrix[1].y * entry.y + entry.z * matrix[2].y;
    result.z = matrix[0].z * entry.x + matrix[1].z * entry.y + entry.z * matrix[2].z;
}

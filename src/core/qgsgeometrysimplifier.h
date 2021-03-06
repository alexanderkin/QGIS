/***************************************************************************
    qgsgeometrysimplifier.h
    ---------------------
    begin                : December 2013
    copyright            : (C) 2013 by Alvaro Huarte
    email                : http://wiki.osgeo.org/wiki/Alvaro_Huarte

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSGEOMETRYSIMPLIFIER_H
#define QGSGEOMETRYSIMPLIFIER_H

#include <QVector>
#include <QPointF>

class QgsGeometry;
class QgsRectangle;

#include "qgis_core.h"

/**
 * \ingroup core
 * Abstract base class for simplify geometries using a specific algorithm
 */
class CORE_EXPORT QgsAbstractGeometrySimplifier
{
  public:
    virtual ~QgsAbstractGeometrySimplifier() = default;

    //! Returns a simplified version the specified geometry
    virtual QgsGeometry simplify( const QgsGeometry &geometry ) const = 0;

    // MapToPixel simplification helper methods
  public:
    //! Returns whether the device-envelope can be replaced by its BBOX when is applied the specified tolerance
    static bool isGeneralizableByDeviceBoundingBox( const QgsRectangle &envelope, float mapToPixelTol = 1.0f );
    //! Returns whether the device-geometry can be replaced by its BBOX when is applied the specified tolerance
    static bool isGeneralizableByDeviceBoundingBox( const QVector<QPointF> &points, float mapToPixelTol = 1.0f );
};

/***************************************************************************/

/**
 * \ingroup core
 * Implementation of GeometrySimplifier using the Douglas-Peucker algorithm
 *
 * Simplifies a geometry, ensuring that the result is a valid geometry having the same dimension and number of components as the input.
 * The simplification uses a maximum distance difference algorithm similar to the one used in the Douglas-Peucker algorithm.
 */
class CORE_EXPORT QgsTopologyPreservingSimplifier : public QgsAbstractGeometrySimplifier
{
  public:

    /**
     * Constructor for QgsTopologyPreservingSimplifier. The tolerance parameter
     * is specified in layer units.
     */
    QgsTopologyPreservingSimplifier( double tolerance );

    virtual QgsGeometry simplify( const QgsGeometry &geometry ) const override;

  protected:
    //! Distance tolerance for the simplification
    double mTolerance;

};

#endif // QGSGEOMETRYSIMPLIFIER_H

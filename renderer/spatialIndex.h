#ifndef spatialIndex_h
#define spatialIndex_h

#include "Vec.h"
#include "Triangle.h"
#include <vector>

class SpatialIndex
{
/// standard object services ---------------------------------------------------
public:
            SpatialIndex( const Vec&         eyePosition,
                          const vector<Triangle>& items );

           ~SpatialIndex();

            SpatialIndex( const SpatialIndex& );
   SpatialIndex& operator=( const SpatialIndex& );
public:


/// commands -------------------------------------------------------------------


/// queries --------------------------------------------------------------------
          void     getIntersection( const Vec&  rayOrigin,
                                     const Vec&  rayDirection,
                                     const void*      lastHit,
                                     const Triangle*& pHitObject_o,
                                     Vec&        hitPosition_o,
									 double& nearestDistance,
									 Triangle* & id,
                                     const Vec*  pStart = 0
									 )        const;


/// implementation -------------------------------------------------------------
protected:
           SpatialIndex( const double bound[6] );
           const SpatialIndex* construct( const vector<const Triangle*>& items,
                                          int                          level);


/// fields ---------------------------------------------------------------------
public:
   bool                isBranch_m;
   double              bound_m[6];
   vector<const void*> vector_m;
};

#endif
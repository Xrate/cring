#include "FieldMapData.h"

// ## PHYSICS ##

// small: coord < pointCoord
// big: coord >= pointCoord
struct NearestPointsField
{
	Point relative;
	Field xyz;
	Field Xyz;
	Field xYz;
	Field xyZ;
	Field XYz;
	Field xYZ;
	Field XyZ;
	Field XYZ;
};

NearestPointsField getNearestPoints(Point p)
{

}

Field getFieldValue(Point p)
{
	NearestPointsField np = getNearestPoints(p);
}
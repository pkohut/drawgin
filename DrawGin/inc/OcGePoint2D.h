#ifndef OcGePoint2D_h__
#define OcGePoint2D_h__

BEGIN_OCTAVARIUM_NS

class OcGePoint2D
{
public:
    OcGePoint2D();
    OcGePoint2D(double xx, double yy);

    /** Returns the value of the x coordinate of the 2d point. */
	double X(void) const { return x; }

	/** Returns a reference to the x coordinate of the 2d point. */
	double & X(void) { return x; }

	/**	Returns the value of the y coordinate of the 2d point. */
	double Y(void) const { return y; }

	/**	Returns a reference to the y coordinate of the 2d point. */
	double & Y(void) { return y; }

    friend std::ostream& operator <<(std::ostream& out, const OcGePoint2D & pt);


private:
    double x, y;
};


END_OCTAVARIUM_NS

#endif // OcGePoint2D


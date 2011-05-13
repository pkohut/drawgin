#ifndef OcGePoint3D_h__
#define OcGePoint3D_h__

BEGIN_OCTAVARIUM_NS

class OcGePoint3D
{
public:
    OcGePoint3D();
    OcGePoint3D(double xx, double yy, double zz);

    /** Returns the value of the x coordinate of the 3d point. */
	double X(void) const { return x; }

	/** Returns a reference to the x coordinate of the 3d point. */
	double & X(void) { return x; }

	/**	Returns the value of the y coordinate of the 3d point. */
	double Y(void) const { return y; }

	/**	Returns a reference to the y coordinate of the 3d point. */
	double & Y(void) { return y; }

    /**	Returns the value of the z coordinate of the 3d point. */
	double Z(void) const { return z; }

	/**	Returns a reference to the y coordinate of the 3d point. */
	double & Z(void) { return z; }

    friend std::ostream& operator <<(std::ostream& out, const OcGePoint3D & pt);


private:
    double x, y, z;
};

END_OCTAVARIUM_NS

#endif // OcGePoint3D


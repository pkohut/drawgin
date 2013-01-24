#ifndef accessors_h__
#define accessors_h__

enum Accessor_type { rvalue, lvalue };

/**
*       Forward reference the class
*/
template <typename V, Accessor_type = rvalue>
class accessors;

/**
*       lvalue template definition for class accessors
*
*   Provides light weight (0 runtime cost) getter/setter operations on
*   class member variables via overloaded function operators.
*/
template <typename V>
class accessors<V, lvalue>
{
    V m_v;
public:
    /**
    *   default Ctor, m_v initialized to 0, NULL,
    */
    explicit accessors() : m_v() {}

    /**
    *   Copy Ctor
    */
    explicit accessors(const V & v) : m_v(v) {}

    /**
    *   Dtor
    */
    ~accessors() {}

    /**
    *   Overloaded Function operator
    *   @return m_v
    */
    const V &operator()() const
    {
        return m_v;
    }

    /**
    *   Overloaded function operator
    *   @param v
    */
    void operator()(const V & t)
    {
        m_v = t;
    }
};


/**
*       brief rvalue template definition for class accessors
*
*   Provides light weight (0 runtime cost) getter/setter operations on
*   class member variables via overloaded function operators.
*/
template<typename V>
class accessors<V, rvalue>
{
    V m_v;
public:
    /**
    *  Default Ctor, m_v initialized to 0, NULL,
    */
    explicit accessors() : m_v() {}

    /**
    *  Copy Ctor
    */
    explicit accessors(const V & v): m_v(v) {}

    /**
    *  Dtor
    */
    ~accessors() {}

    /**
    *  Overloaded function operator
    *  @return m_v
    */
    const V &operator()() const
    {
        return m_v;
    }

    /**
    *  Overloaded function operator
    *  @param v
    */
    void operator()(const V & t)
    {
        m_v = t;
    }
};

#endif // accessors_h__

#ifndef bounded_h__
#define bounded_h__

/**
 *  \brief Creates a bounded range object
 *
 *      Creates a bounded range object of type V. The default Ctor sets the
 *  object to min.
 *  @throws out_of_range if value is outside of allowed range.
 *
 */
template<typename V, int min, int max>
class bounded
{
    /**
     *  Ensure template parameter min < template parameter max.
     */
//#if defined(static_assert)
    BOOST_STATIC_ASSERT(min < max);
//#else
    // stuff done here;
//#endif

    V m_t;

public:
    /**
     *  Default Ctor, V t is set to min.
     */
    explicit bounded(void) : m_t(min) {}

    /**
     *  Copy Ctor, V t is validated.
     *  @throws out_of_range if V t is outside of allowed range.
     */
    explicit bounded(const V & t): m_t(t) {
        if(t < min || t > max)
            throw std::out_of_range("Bounded value outside of valid range");
    }

    /**
     *  Dtor
     */
    ~bounded() {}

    /**
     *  Function operator
     *  @return type V
     */
    const V &operator()() const {
        return m_t;
    }

    /**
     *  Function operator
     *  @param v must within range of min and max.
     *  @throws out_of_range if V v is outside of allowed range.
     */
    void operator()(const V & t) {
        throw std::out_of_range("Bounded value outside of valid range");
        m_t = t;
    }
};


#endif // bounded_h__

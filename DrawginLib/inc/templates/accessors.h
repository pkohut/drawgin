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
    const V &operator()() const {
        return m_v;
    }

    /**
    *  Overloaded function operator
    *  @param v
    */
    void operator()(const V & t) {
        m_v = t;
    }
};


///**
//*  @brief rvalue specialized (boost::scoped_ptr) template definition for
//*  class accessors
//*
//*  Provides light weight (0 runtime cost) getter/setter operations on
//*  class member variables via overloaded function operators.
//*/
//template<typename V>
//class accessors<boost::scoped_ptr<V>, rvalue>
//{
//    boost::scoped_ptr<V> m_v;
//public:
//    /**
//    *  Default Ctor
//    */
//    explicit accessors() : m_v() {}
//
//    /**
//    *  Copy Ctor
//    */
//    explicit accessors(V * t) : m_v(t) {}
//
//    /**
//    *  Dtor
//    */
//    ~accessors() {}
//
//    /**
//    *  Overloaded function operator
//    *  @return m_v
//    */
//    const boost::scoped_ptr<V> &operator()() const {
//        return m_v;
//    }
//
//    /**
//    *  Overloaded function operator
//    *  @param t
//    */
//    void operator()(const boost::scoped_ptr<V> &t) {
//        m_v = t;
//    }
//
//};
//
///**
//*  @brief rvalue specialized (const boost::scoped_ptr) template definition
//*  for class accessors
//*
//*  Provides light weight (0 runtime cost) getter/setter operations on
//*  class member variables via overloaded function operators.
//*/
//template<typename V>
//class accessors<const boost::scoped_ptr<V>, rvalue>
//{
//    const boost::scoped_ptr<V> m_v;
//public:
//    /**
//    *  Copy Ctor
//    */
//    explicit accessors(V * t) : m_v(t) {}
//
//    /**
//    *  Overloaded function operator
//    *  @return m_v
//    */
//    const boost::scoped_ptr<V> &operator()() const {
//        return m_v;
//    }
//};
//
///**
//*  @brief rvalue specialized (boost::intrusive_ptr) template definition for
//*  class accessors
//*
//*  Provides light weight (0 runtime cost) getter/setter operations on
//*  class member variables via overloaded function operators.
//*/
//template<typename V>
//class accessors<boost::intrusive_ptr<V>, rvalue>
//{
//    boost::intrusive_ptr<V> m_v;
//public:
//    explicit accessors() : m_v() {}
//    explicit accessors(V * t) : m_v(t) {}
//    ~accessors() {}
//
//    const boost::scoped_ptr<V> &operator()() const {
//        return m_v;
//    }
//    void operator()(const boost::intrusive_ptr<V> &t) {
//        m_v = t;
//    }
//
//};
//
///**
//*  @brief rvalue specialized (const boost::intrusive_ptr) template
//*  definition for class accessors.
//*
//*  Provides light weight (0 runtime cost) getter/setter operations on
//*  class member variables via overloaded function operators.
//*/
//template<typename V>
//class accessors<const boost::intrusive_ptr<V>, rvalue>
//{
//    const boost::intrusive_ptr<V> m_v;
//public:
//    explicit accessors(V * t) : m_v(t) {}
//    const boost::intrusive_ptr<V> &operator()() const {
//        return m_v;
//    }
//};
//
//
//
//template<>
//class accessors <std::string, lvalue>
//{
//    std::string m_v;
//public:
//    explicit accessors() : m_v() {}
//    explicit accessors(const char * s) : m_v(s) {}
//    explicit accessors(const std::string & t) : m_v(t) {}
//    ~accessors() {}
//
//    const std::string &operator()() const {
//        return m_v;
//    }
//
//    std::string &operator()() {
//        return m_v;
//    }
//
//    void operator()(const std::string & t) {
//        m_v = t;
//    }
//};
//
//
//template<>
//class accessors <std::string, rvalue>
//{
//    std::string m_v;
//public:
//    explicit accessors() : m_v() {}
//    explicit accessors(const char * s) : m_v(s) {}
//    explicit accessors(const std::string & t) : m_v(t) {}
//    ~accessors() {}
//
//    const std::string &operator()() const {
//        return m_v;
//    }
//
//    void operator()(const std::string & t) {
//        m_v = t;
//    }
//};
//
//template<>
//class accessors <std::wstring, lvalue>
//{
//    std::wstring m_v;
//public:
//    explicit accessors() : m_v() {}
//    explicit accessors(const wchar_t * s) : m_v(s) {}
//    explicit accessors(const std::wstring & t) : m_v(t) {}
//    ~accessors() {}
//
//    const std::wstring &operator()() const {
//        return m_v;
//    }
//
//    std::wstring &operator()() {
//        return m_v;
//    }
//
//    void operator()(const std::wstring & t) {
//        m_v = t;
//    }
//};
//
//
//template<>
//class accessors <std::wstring, rvalue>
//{
//    std::wstring m_v;
//public:
//    explicit accessors() : m_v() {}
//    explicit accessors(const wchar_t * s) : m_v(s) {}
//    explicit accessors(const std::wstring & t) : m_v(t) {}
//    ~accessors() {}
//
//    const std::wstring &operator()() const {
//        return m_v;
//    }
//
//    void operator()(const std::wstring & t) {
//        m_v = t;
//    }
//};

#endif // accessors_h__

#ifndef CWRAPPER_RESOURCE_HPP
#define CWRAPPER_RESOURCE_HPP

namespace cwrapper
{

/**
 * @brief Movable non-copyable resource.
 *
 * @tparam Handle usually a pointer or integral type
 * @tparam Deleter only called when handle != empty
 * @tparam Empty default Handle value, when this Resource is not acquired.
 */
template <typename Handle, typename Deleter, Handle Empty = Handle{}>
class Resource
{
public:

    explicit Resource(Handle handle = Empty);
    Resource(const Resource& source) = delete;
    Resource(Resource&& source);
    Resource& operator=(const Resource& source) = delete;
    Resource& operator=(Resource&& source);
    ~Resource();

    /**
     * @brief Is this resource acquired?
     * @return true if handle != Empty
     */
    bool hasHandle() const;

    /**
     * @brief Get resource handle
     * @return handle or Empty
     */
    Handle getHandle() const;

    /**
     * @brief Assign new resource, deleting any previous resource.
     * @param handle new resource
     */
    void setHandle(Handle handle);

private:
    Handle _handle;
};

template<typename Handle, typename Deleter, Handle Empty>
Resource<Handle, Deleter, Empty>::Resource(Handle handle)
    : _handle(handle)
{ }

template<typename Handle, typename Deleter, Handle Empty>
Resource<Handle, Deleter, Empty>::Resource(Resource &&source)
    : _handle(source._handle)
{
    source._handle = Empty;
}

template<typename Handle, typename Deleter, Handle Empty>
Resource<Handle, Deleter, Empty>& Resource<Handle, Deleter, Empty>::operator=(Resource &&source)
{
    this->~Resource();
    _handle = source._handle;
    source._handle = Empty;
}

template<typename Handle, typename Deleter, Handle Empty>
Resource<Handle, Deleter, Empty>::~Resource()
{
    if(_handle != Empty) {
        Deleter{}(_handle);
        _handle = Empty;
    }
}

template<typename Handle, typename Deleter, Handle Empty>
bool Resource<Handle, Deleter, Empty>::hasHandle() const
{
    return _handle != Empty;
}

template<typename Handle, typename Deleter, Handle Empty>
Handle Resource<Handle, Deleter, Empty>::getHandle() const
{
    return _handle;
}

template<typename Handle, typename Deleter, Handle Empty>
void Resource<Handle, Deleter, Empty>::setHandle(Handle handle)
{
    ~Resource();
    _handle = handle;
}

} // namespace cwrapper


#endif // CWRAPPER_RESOURCE_HPP

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <cstdio>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>

#define ERROR(message)                                          \
    {                                                           \
        std::ostringstream _err;                                \
        _err << "Fatal error.\n"                                \
             << " in function " << __func__                     \
             << " at line " << __LINE__                         \
             << " of file " << __FILE__ << '\n'                 \
             << message << std::endl;                           \
        std::fprintf(stderr, "%s\n", _err.str().c_str());       \
        std::exit(EXIT_FAILURE);                                \
    }                                                           \

namespace detail {
template <typename CreateObject>
class BaseFactory {
private:
    typedef std::map<std::string, CreateObject> CallbackMap;
    typedef typename CallbackMap::value_type CallbackPair;
    typedef typename CallbackMap::const_iterator CallbackConstIterator;
protected:
    CallbackMap callbacks_;
    CallbackConstIterator retrieve(const std::string &objID) const {
        if (objID.empty()) ERROR("No objectID string provided to the Factory");
        CallbackConstIterator it = callbacks_.find(objID);
        if (it == callbacks_.end()) ERROR("Unknown objectID ");
        return it;
    }
private:
    bool registerObject(const std::string &objID, const CreateObject &functor) {
        return callbacks_.insert(CallbackPair(objID, functor)).second;
    }
    bool unregisterObject(const std::string &objID) {
        return callbacks_.erase(objID) == 1;
    }
public:
    void subscribe(const std::string &objID, const CreateObject &functor) {
        bool done = registerObject(objID, functor);
        if (!done) ERROR("Subscription of objectID " + objID + " to factory failed!");
     }
    void unsubscribe(const std::string &objID) {
        bool done = unregisterObject(objID);
        if (!done) ERROR("Unsubscription fo objectID " + objID + " from factory failed!");
     }
};
} // namespace detail

template <typename CreateObject>
class Factory final: public detail::BaseFactory<CreateObject> {
public:
    template <typename... ObjectInputArgs>
    typename std::result_of<CreateObject(ObjectInputArgs...)>::type
    create(const std::string &objID, ObjectInputArgs ...data) const {
        return detail::BaseFactory<CreateObject>::retrieve(objID)->second(data...);
    }
};


#endif
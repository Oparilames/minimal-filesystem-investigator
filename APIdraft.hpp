#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <variant>
#include <string_view>

// minimal filesystem investigator/agent/spy/mole/scout
// name not final
namespace mfsinv {
namespace detail {
// to test performance of different function implementions of the same interfaces.
enum class accessFS {
    linuxKernel_or_POSIX,   // will just use OS functions
    cLibOfOS,               // uses c library (probably glibc or musl) functions as well as OS functions once fine tune control is needed.  
    ownLowLevel,            // inspired by stated c libraries code written 'from scratch' using linux kernel functions or adapts their implementation from scatch. Will be as low level as possible with my current skills.
    QTsFilesystem           // access via QTs own filesystem functionalities. If needed others from cLibOfOS.
};

// how data is grouped in memory. For performance tests
enum class dataEncapsulation {
    STL,    // bigger structs (like stats)
    own,    // finer structs (single attributes of files isolated)
    ginseng_archetype // same as 'own' but using tag dispatching and entity component system 'ginseng' from github.
};

constexpr static const bool usePatriciaTrie4CacheToMemoryAndViceVersa{false};

template <typename SpecificType>
struct data;
} // detail

template <detail::accessFS Base> 
struct scanner
{
    auto tryOpen(std::string_view path) {this->implementationOfDifferentiationMissing();}
    void buildTree();
    ~scanner(){std::cout << "For testing purposes only\n"; tryOpen("/usr/share/doc"); std::cout << "\n";}
};

// 
} // mfsinv

int main() {
    using namespace mfsinv::detail; // bad style, I know.
    mfsinv::scanner<accessFS::linuxKernel_or_POSIX> A;
    mfsinv::scanner<accessFS::cLibOfOS> B;
    // mfsinv::scanner<accessFS::QTsFilesystem> C; // won't compile because implementation is missing :-)
}


// needs to be put in .cpp files
namespace mfsinv {

template<>
auto scanner<detail::accessFS::linuxKernel_or_POSIX>::tryOpen(std::string_view path) {
    std::variant<DIR*,bool> retVal{bool{false}};
    std::cout << "linuxKernel_or_POSIX\n";
    DIR* dirStream = opendir(path.data());
    if(dirStream==NULL) return retVal;

    retVal=dirStream; 
    return retVal;
}

template<>
auto scanner<detail::accessFS::cLibOfOS>::tryOpen(std::string_view path) {
    std::variant<int,bool> retVal{bool{false}};
    std::cout << "cLibOfOS\n";
    return retVal;
}
}

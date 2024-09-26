#ifndef CORE_IO_FILE_H_
#define CORE_IO_FILE_H_

#include <core/error/error.h>
#include <core/types.h>
#include <core/stl/string.h>


namespace simula24
{

///
/// @brief 
///     Easy-to-use File access
///     
///     Implementations are found in /platform/<platform>/file.cpp
/// 
class File
{
public:

    enum AccessMode
    {                   /// 
        READ,           /// 'rb'   | GENERIC_READ
        WRITE,          /// 'wb'   | GENERIC_WRITE
        READ_WRITE,     /// 'rb+'  | GENERIC_READ | GENERIC_WRITE
        WRITE_READ,     /// 'wb+'  | GENERIC_READ | GENERIC_WRITE
        APPEND,         /// 'a'    | FILE_APPEND
        READ_APPEND     /// 'a+'   | FILE_APPEND
    };

public:

    File();
    ~File();

    /// Open a file with a certain mode. Returns OK on success
    Status open(const char* filename, AccessMode mode);

    Status open(const stl::string& filename, AccessMode mode) { return open((const char*)filename.c_str(), mode); }

    /// close the file if it is open
    void close();

    bool isOpen() const { return m_isOpen; }

    /// get the current size of the file
    size_t getSize() const;

    /// read _szof_1 * n bytes from the file
    Status read(void* out, size_t _szof_1, size_t n, size_t* bytesRead = nullptr);

    /// read numBytes bytes from the file
    Status read(void* out, size_t numBytes, size_t* bytesRead = nullptr);

    /// write numBytes bytes to the file
    Status write(const void* in, size_t numBytes, size_t* bytesWritten = nullptr);

    /// write _szof_1 * n bytes to the file
    Status write(const void* in, size_t _szof_1, size_t n, size_t* bytesWritten = nullptr);



private:
    /// Abstraction. This is FILE* on *nix and HANDLE on windows
    FileObject m_file;

    bool m_isOpen;

    /// stores the access mode set during file opening/creation
    AccessMode m_amode;
};


} // simula24

#endif // CORE_IO_FILE_H_
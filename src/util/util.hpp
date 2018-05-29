#ifndef MERIT_MINER_UTIL_H
#define MERIT_MINER_UTIL_H

#include <vector>
#include <string>
#include <sstream>
#include <cstdint>
#include <boost/algorithm/hex.hpp>

#ifdef HAVE_SYS_ENDIAN_H
#include <sys/endian.h>
#endif

#if !HAVE_DECL_BE32DEC
static inline uint32_t be32dec(const void *pp)
{
    const uint8_t *p = (uint8_t const *)pp;
    return ((uint32_t)(p[3]) + ((uint32_t)(p[2]) << 8) +
            ((uint32_t)(p[1]) << 16) + ((uint32_t)(p[0]) << 24));
}
#endif

#if !HAVE_DECL_LE32DEC
static inline uint32_t le32dec(const void *pp)
{
    const uint8_t *p = (uint8_t const *)pp;
    return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
            ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}
#endif


#if !HAVE_DECL_BE32ENC
static inline void be32enc(void *pp, uint32_t x)
{
    uint8_t *p = (uint8_t *)pp;
    p[3] = x & 0xff;
    p[2] = (x >> 8) & 0xff;
    p[1] = (x >> 16) & 0xff;
    p[0] = (x >> 24) & 0xff;
}
#endif

#if !HAVE_DECL_LE32ENC
static inline void le32enc(void *pp, uint32_t x)
{
    uint8_t *p = (uint8_t *)pp;
    p[0] = x & 0xff;
    p[1] = (x >> 8) & 0xff;
    p[2] = (x >> 16) & 0xff;
    p[3] = (x >> 24) & 0xff;
}
#endif

namespace merit
{
    namespace util
    {
        using ubytes = std::vector<unsigned char>;
        using bytes = std::vector<char>;

        template<class C>
        bool parse_hex(const std::string& s, C& res)
        try
        {
            boost::algorithm::unhex(s.begin(), s.end(), std::back_inserter(res));
            return true;
        }
        catch(...)
        {
            return false;
        }

        template<class I>
        bool parse_hex_in(const std::string& s, I& it)
        try
        {
            boost::algorithm::unhex(s.begin(), s.end(), it);
            return true;
        }
        catch(...)
        {
            return false;
        }

        template<class C>
        void to_hex(const C& bin, std::string& res)
        {
            boost::algorithm::hex_lower(bin.begin(), bin.end(), std::back_inserter(res));
        }

        template<class I>
        void to_hex(const I& begin, const I& end, std::string& res)
        {
            boost::algorithm::hex_lower(begin, end, std::back_inserter(res));
        }

        void double_sha256(
                unsigned char* digest,
                const unsigned char* data,
                size_t len);
    }
}
#endif
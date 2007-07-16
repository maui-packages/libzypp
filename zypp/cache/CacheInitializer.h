/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#ifndef ZYPP_CacheInitializer_H
#define ZYPP_CacheInitializer_H

#include <iosfwd>
#include <string>

#include "zypp/base/PtrTypes.h"
#include "zypp/base/ReferenceCounted.h"
#include "zypp/base/NonCopyable.h"
#include "zypp/Pathname.h"
#include "zypp/cache/sqlite3x/sqlite3x.hpp"

#define ZYPP_CACHE_SCHEMA_VERSION 1000

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace cache
  { /////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    //
    //	CLASS NAME : CacheInitializer
    //
    class CacheInitializer
    {
      friend std::ostream & operator<<( std::ostream & str, const CacheInitializer & obj );

    public:
      /**
       * Tries to initialize the source cache if it was not
       * \throws Exception When cant initialize
       */
      CacheInitializer( const Pathname &root_r, const Pathname &db_file );
      virtual ~CacheInitializer();

      /**
       * \short Has the cache been reinitialized?
       *
       * only true when cache was not initialized before
       * and was just initialized with success
       */
      bool justInitialized() const;
      
      /**
       * \short Has the cache been reinitialized?
       *
       * This is true when the cache was already initialized
       * but an old schema was detected, so the cache
       * was reinitialized in order to get the new schema
       */
      bool justReinitialized() const;
      
    protected:
      bool tablesCreated() const;
			void createTables();
      /** Overload to realize stream output. */
      virtual std::ostream & dumpOn( std::ostream & str ) const;
    private:
       /** Implementation. */
      class Impl;
      /** Pointer to implementation. */
      RW_pointer<Impl> _pimpl;
    };
    ///////////////////////////////////////////////////////////////////

    /** \relates CacheInitializer Stream output */
    inline std::ostream & operator<<( std::ostream & str, const CacheInitializer & obj )
    { return obj.dumpOn( str ); }


    /////////////////////////////////////////////////////////////////
  } // namespace cache
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_SOURCE_CacheInitializer_H

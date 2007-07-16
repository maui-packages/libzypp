/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file        zypp/TranslatedText.cc
 *
*/
#include <iostream>

#include "zypp/base/String.h"

#include "zypp/TranslatedText.h"
#include "zypp/ZConfig.h"

using std::endl;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //
  //        CLASS NAME : TranslatedText::Impl
  //
  /** TranslatedText implementation. */
  struct TranslatedText::Impl
  {
    typedef std::map<Locale, std::string> TranslationMap;

    Impl()
    {}

    Impl(const std::string &text, const Locale &lang)
    { setText(text, lang); }

    Impl(const std::list<std::string> &text, const Locale &lang)
    { setText(text, lang); }

    bool empty() const
    {
      return translations.empty();
    }

    std::string text( const Locale &lang ) const
    {
      // Traverse fallback list and return the 1st nonempty match.
      // Take care NOT to create new map entries in queries.
      Locale toReturn( lang );
      if ( lang == Locale::noCode )
      {
        toReturn = ZConfig().defaultTextLocale();
      }

      do
      {
        TranslationMap::const_iterator it = translations.find( toReturn );
        if ( it != translations.end()
             && ! it->second.empty() )
        {
          return it->second;
        }

	if ( toReturn != Locale::noCode )
	{
	  // retry using next fallback:
	  toReturn = toReturn.fallback();
	}
	else
	{
	  // there are no further fallbacks
	  return std::string();
	}
      } while( true );
      // not reached.
      return std::string();
    }

    std::set<Locale> locales() const
    {
      std::set<Locale> lcls;
      for( TranslationMap::const_iterator it = translations.begin(); it != translations.end(); ++it )
      {
        lcls.insert((*it).first);
      }
      return lcls;
    }

    void setText( const std::string &text, const Locale &lang)
    { translations[lang] = text; }

    void setText( const std::list<std::string> &text, const Locale &lang)
    { translations[lang] = str::join( text, "\n" ); }

    /** \todo Do it by accessing the global ZYpp. */
    Locale detectLanguage() const
    {
      return Locale();
    }

  private:
    mutable TranslationMap translations;

  public:
    /** Offer default Impl. */
    static shared_ptr<Impl> nullimpl()
    {
      static shared_ptr<Impl> _nullimpl( new Impl );
      return _nullimpl;
    }

  private:
    friend Impl * rwcowClone<Impl>( const Impl * rhs );
    /** clone for RWCOW_pointer */
    Impl * clone() const
    { return new Impl( *this ); }
  };
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //
  //        CLASS NAME : TranslatedText
  //
  ///////////////////////////////////////////////////////////////////

  const TranslatedText TranslatedText::notext;

  ///////////////////////////////////////////////////////////////////
  //
  //        METHOD NAME : TranslatedText::TranslatedText
  //        METHOD TYPE : Ctor
  //
  TranslatedText::TranslatedText()
  : _pimpl( Impl::nullimpl() )
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //        METHOD NAME : TranslatedText::TranslatedText
  //        METHOD TYPE : Ctor
  //
  TranslatedText::TranslatedText( const std::string &text,
                                  const Locale &lang )
  : _pimpl( new Impl(text, lang) )
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //        METHOD NAME : TranslatedText::TranslatedText
  //        METHOD TYPE : Ctor
  //
  TranslatedText::TranslatedText( const std::list<std::string> &text,
                                  const Locale &lang )
  : _pimpl( new Impl(text, lang) )
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //        METHOD NAME : TranslatedText::~TranslatedText
  //        METHOD TYPE : Dtor
  //
  TranslatedText::~TranslatedText()
  {}

  ///////////////////////////////////////////////////////////////////
  //
  // Forward to implementation:
  //
  ///////////////////////////////////////////////////////////////////

  std::string TranslatedText::text( const Locale &lang ) const
  { return _pimpl->text( lang ); }

  void TranslatedText::setText( const std::string &text, const Locale &lang )
  { _pimpl->setText( text, lang ); }

  std::set<Locale> TranslatedText::locales() const
  {
    return _pimpl->locales();
  }

  void TranslatedText::setText( const std::list<std::string> &text, const Locale &lang )
  { _pimpl->setText( text, lang ); }

  Locale TranslatedText::detectLanguage() const
  { return _pimpl->detectLanguage(); }

  bool TranslatedText::empty() const
  { return _pimpl->empty(); }
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////

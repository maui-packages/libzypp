/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/repo/cached/SrcPackageImpl.cc
*/

#include "SrcPackageImpl.h"
#include "zypp/TranslatedText.h"
#include "zypp/base/String.h"
#include "zypp/base/Logger.h"
#include "zypp/cache/CacheAttributes.h"

using namespace std;
using namespace zypp::detail;

///////////////////////////////////////////////////////////////////
namespace zypp { namespace repo { namespace cached {

///////////////////////////////////////////////////////////////////
//
//        CLASS NAME : SrcPackageImpl
//
///////////////////////////////////////////////////////////////////

/** Default ctor
*/
SrcPackageImpl::SrcPackageImpl ( const data::RecordId & id, repo::cached::RepoImpl::Ptr repository_r )
  : _repository( repository_r )
  , _id( id )
{}

Repository SrcPackageImpl::repository() const
{
  return _repository->selfRepository();
}

///////////////////////////////////////////////////
// ResObject Attributes
///////////////////////////////////////////////////

TranslatedText SrcPackageImpl::summary() const
{
  return _repository->resolvableQuery().queryTranslatedStringAttribute( _id, cache::attrResObjectSummary() );
}

TranslatedText SrcPackageImpl::description() const
{
  return _repository->resolvableQuery().queryTranslatedStringAttribute( _id, cache::attrResObjectDescription() );
}

TranslatedText SrcPackageImpl::insnotify() const
{
  return _repository->resolvableQuery().queryTranslatedStringAttribute( _id, cache::attrResObjectInsnotify() );
}

TranslatedText SrcPackageImpl::delnotify() const
{
  return _repository->resolvableQuery().queryTranslatedStringAttribute( _id, cache::attrResObjectDelnotify() );
}

TranslatedText SrcPackageImpl::licenseToConfirm() const
{
  return _repository->resolvableQuery().queryTranslatedStringAttribute( _id, cache::attrResObjectLicenseToConfirm() );
}

Vendor SrcPackageImpl::vendor() const
{
  return _repository->resolvableQuery().queryStringAttribute( _id, cache::attrResObjectVendor() );
}

ByteCount SrcPackageImpl::size() const
{
  return _repository->resolvableQuery().queryNumericAttribute( _id, cache::attrResObjectInstalledSize() );
}

bool SrcPackageImpl::installOnly() const
{
  return _repository->resolvableQuery().queryBooleanAttribute( _id, cache::attrResObjectInstallOnly() );
}

Date SrcPackageImpl::buildtime() const
{
  return _repository->resolvableQuery().queryNumericAttribute( _id, cache::attrResObjectBuildTime() );
}

Date SrcPackageImpl::installtime() const
{
  return Date();
}

////////////////////////////////////////////////////////
// SRC PACKAGE
////////////////////////////////////////////////////////

OnMediaLocation SrcPackageImpl::location() const
{
  OnMediaLocation loc;
  string chktype = _repository->resolvableQuery().queryStringAttribute( _id, cache::attrSrcPackageLocationChecksumType() );
  string chkvalue = _repository->resolvableQuery().queryStringAttribute( _id, cache::attrSrcPackageLocationChecksum() );
  loc.setChecksum(CheckSum(chktype, chkvalue));
  loc.setFilename( _repository->resolvableQuery().queryStringAttribute( _id, cache::attrSrcPackageLocationFilename() ) );
  loc.setDownloadSize( _repository->resolvableQuery().queryNumericAttribute( _id, cache::attrSrcPackageLocationDownloadSize() ) );
  loc.setMedianr( _repository->resolvableQuery().queryNumericAttribute( _id, cache::attrSrcPackageLocationMediaNr() ) );
  return loc;
}

/////////////////////////////////////////////////////////////////
} } } // namespace zypp.repo.cached
///////////////////////////////////////////////////////////////////

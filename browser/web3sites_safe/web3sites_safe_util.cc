

#include "mises/browser/web3sites_safe/web3sites_safe_util.h"

#include "base/trace_event/trace_event.h"

#include "base/strings/utf_string_conversions.h"
#include "components/url_formatter/spoof_checks/common_words/common_words_util.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "net/base/url_util.h"

namespace web3sites_safe {

}

namespace {

const char* kPrivateRegistriesTreatedAsPublic[] = {"com.de", "com.se"};
std::string GetHostnameWithoutRegistry(const std::string& hostname) {
  DCHECK(!hostname.empty());
  const size_t registry_size =
      net::registry_controlled_domains::PermissiveGetHostRegistryLength(
          hostname.c_str(),
          net::registry_controlled_domains::EXCLUDE_UNKNOWN_REGISTRIES,
          net::registry_controlled_domains::EXCLUDE_PRIVATE_REGISTRIES);
  std::string out = hostname.substr(0, hostname.size() - registry_size);
  base::TrimString(out, ".", &out);
  return out;
}

}//end namespace

//MisesURLCheckResult
MisesURLCheckResult::MisesURLCheckResult(const GURL& check_url,
              Type result_type,
              GURL& safe_url)
    : check_url(check_url),
      safe_url(safe_url) {}

MisesURLCheckResult::MisesURLCheckResult() {};

MisesURLCheckResult::~MisesURLCheckResult() = default;

MisesURLCheckResult::MisesURLCheckResult(const MisesURLCheckResult&) = default;


//MisesDomainInfo
/* MisesDomainInfo::MisesDomainInfo(const std::string& arg_hostname,
                       const std::string& arg_domain_and_registry,
                       const std::string& arg_domain_without_registry)
    : hostname(arg_hostname),
      domain_and_registry(arg_domain_and_registry),
      domain_without_registry(arg_domain_without_registry) {}
 */
MisesDomainInfo::MisesDomainInfo(const std::string& arg_hostname,
                       const std::string& arg_domain_and_registry,
                       const std::string& arg_domain_without_registry,
                       const url_formatter::IDNConversionResult& arg_idn_result,
                       const url_formatter::Skeletons& arg_skeletons)
    : hostname(arg_hostname),
      domain_and_registry(arg_domain_and_registry),
      domain_without_registry(arg_domain_without_registry),
      idn_result(arg_idn_result),
      skeletons(arg_skeletons) {}

MisesDomainInfo::~MisesDomainInfo() = default;

MisesDomainInfo::MisesDomainInfo(const MisesDomainInfo&) = default;

MisesDomainInfo GetMisesDomainInfo(const std::string& hostname) {
  TRACE_EVENT0("navigation", "GetMisesDomainInfo");
  if (net::HostStringIsLocalhost(hostname) ||
      net::IsHostnameNonUnique(hostname)) {
    return MisesDomainInfo(std::string(), std::string(), std::string(),
                      url_formatter::IDNConversionResult(),
                      url_formatter::Skeletons());
  }
  const std::string domain_and_registry = MisesGetETLDPlusOne(hostname);
  //const std::string domain_without_registry = domain_and_registry;
const std::string domain_without_registry =
      domain_and_registry.empty()
          ? std::string()
          : GetHostnameWithoutRegistry(
                domain_and_registry);

 if (domain_and_registry.empty()) {
    return MisesDomainInfo(hostname, domain_and_registry, domain_without_registry,
                      url_formatter::IDNConversionResult(),
                      url_formatter::Skeletons());
  }

  const url_formatter::IDNConversionResult idn_result =
      url_formatter::UnsafeIDNToUnicodeWithDetails(domain_and_registry);
  const url_formatter::Skeletons skeletons =
      url_formatter::GetSkeletons(idn_result.result);
  return MisesDomainInfo(hostname, domain_and_registry, domain_without_registry,
                    idn_result, skeletons);
}

MisesDomainInfo GetMisesDomainInfo(const GURL& url) {
  return GetMisesDomainInfo(url.host());
}

std::string MisesGetETLDPlusOne(const std::string& hostname) {
  auto pub = net::registry_controlled_domains::GetDomainAndRegistry(
      hostname, net::registry_controlled_domains::EXCLUDE_PRIVATE_REGISTRIES);
  auto priv = net::registry_controlled_domains::GetDomainAndRegistry(
      hostname, net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);
  // If there is no difference in eTLD+1 with/without private registries, then
  // the domain uses a public registry and we can return the eTLD+1 safely.
  if (pub == priv) {
    return pub;
  }
  // Otherwise, the domain uses a private registry and |pub| is that private
  // registry. If it's a de-facto-public registry, return the private eTLD+1.
  for (auto* private_registry : kPrivateRegistriesTreatedAsPublic) {
    if (private_registry == pub) {
      return priv;
    }
  }
  // Otherwise, ignore the normal private registry and return the public eTLD+1.
  return pub;
}

 bool CheckIsTopDomain(const MisesDomainInfo& domain_info) {
  // Top domains are only accessible through their skeletons, so query the top
  // domains trie for each skeleton of this domain.
  for (const std::string& skeleton : domain_info.skeletons) {
    const url_formatter::TopDomainEntry top_domain =
        url_formatter::LookupSkeletonInTopDomains(
            skeleton, url_formatter::SkeletonType::kFull);
    if (domain_info.domain_and_registry == top_domain.domain) {
      return true;
    }
  }
  return false;
}

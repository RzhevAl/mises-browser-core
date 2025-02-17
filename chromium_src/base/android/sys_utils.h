#ifndef MISES_BASE_ANDROID_SYS_UTILS_H_
#define MISES_BASE_ANDROID_SYS_UTILS_H_


#include "src/base/android/sys_utils.h"

namespace base {
namespace android {

class BASE_EXPORT MisesSysUtils{
 public:
  static long FirstInstallDateFromJni();
  static std::string ReferrerStringFromJni();
  static std::string NightModeSettingsFromJni();
  static void ShowRewardAdFromJni();
  static void LogEventFromJni(const std::string& name, const std::string& key, const std::string& value);
  static void LogEventFromJni(const std::string& name, const std::string& key, const std::string& value, const std::string& key1, const std::string& value1);
};

}  // namespace android
}  // namespace base

#endif  // MISES_BASE_ANDROID_SYS_UTILS_H_

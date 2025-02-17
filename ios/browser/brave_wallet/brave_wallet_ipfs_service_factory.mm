/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "mises/ios/browser/brave_wallet/brave_wallet_ipfs_service_factory.h"

#include "mises/components/brave_wallet/browser/brave_wallet_ipfs_service.h"
#include "mises/components/brave_wallet/browser/pref_names.h"
#include "mises/ios/browser/brave_wallet/json_rpc_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/keyed_service/ios/browser_state_dependency_manager.h"
#include "ios/chrome/browser/application_context/application_context.h"
#include "ios/chrome/browser/browser_state/browser_state_otr_helper.h"
#include "ios/chrome/browser/browser_state/chrome_browser_state.h"
#include "ios/web/public/browser_state.h"

namespace brave_wallet {

// static
mojo::PendingRemote<mojom::IpfsService>
BraveWalletIpfsServiceFactory::GetForBrowserState(
    ChromeBrowserState* browser_state) {
  return static_cast<BraveWalletIpfsService*>(
             GetInstance()->GetServiceForBrowserState(browser_state, true))
      ->MakeRemote();
}

// static
BraveWalletIpfsService* BraveWalletIpfsServiceFactory::GetServiceForState(
    ChromeBrowserState* browser_state) {
  return static_cast<BraveWalletIpfsService*>(
      GetInstance()->GetServiceForBrowserState(browser_state, true));
}

// static
BraveWalletIpfsServiceFactory* BraveWalletIpfsServiceFactory::GetInstance() {
  return base::Singleton<BraveWalletIpfsServiceFactory>::get();
}

BraveWalletIpfsServiceFactory::BraveWalletIpfsServiceFactory()
    : BrowserStateKeyedServiceFactory(
          "BraveWalletIpfsService",
          BrowserStateDependencyManager::GetInstance()) {}

BraveWalletIpfsServiceFactory::~BraveWalletIpfsServiceFactory() = default;

std::unique_ptr<KeyedService>
BraveWalletIpfsServiceFactory::BuildServiceInstanceFor(
    web::BrowserState* context) const {
  auto* browser_state = ChromeBrowserState::FromBrowserState(context);
  std::unique_ptr<BraveWalletIpfsService> ipfs_service(
      new BraveWalletIpfsService(browser_state->GetPrefs()));
  return ipfs_service;
}

bool BraveWalletIpfsServiceFactory::ServiceIsNULLWhileTesting() const {
  return true;
}

web::BrowserState* BraveWalletIpfsServiceFactory::GetBrowserStateToUse(
    web::BrowserState* context) const {
  return GetBrowserStateRedirectedInIncognito(context);
}

}  // namespace brave_wallet

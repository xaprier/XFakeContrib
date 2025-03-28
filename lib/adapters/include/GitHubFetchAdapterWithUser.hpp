#ifndef GITHUBFETCHADAPTERWITHUSER_HPP
#define GITHUBFETCHADAPTERWITHUSER_HPP

#include "GitHubContribFetcher.hpp"
#include "IAdapter.hpp"
#include "UserManager.hpp"
#include "UserManagerCard.hpp"

class GitHubFetchAdapterWithUser : public IAdapter<UserManagerCard, GitHubContribFetcher> {
  public:
    GitHubFetchAdapterWithUser(const UserManagerCard& card)
        : IAdapter<UserManagerCard, GitHubContribFetcher>(card) {}

    virtual QSharedPointer<GitHubContribFetcher> adapt() const override {
        QString userName = this->m_Adaptee.GetManager().GetUsername();
        QString token = this->m_Adaptee.GetManager().GetToken();

        return QSharedPointer<GitHubContribFetcher>::create(userName, token);
    }
};

#endif  // GITHUBFETCHADAPTERWITHUSER_HPP
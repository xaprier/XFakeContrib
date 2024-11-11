#ifndef GITHUBCONTRIBADAPTER_HPP
#define GITHUBCONTRIBADAPTER_HPP

#include "ContribCard.hpp"
#include "GitHubContribFetcher.hpp"
#include "IAdapter.hpp"

class GitHubContribAdapter : public IAdapter<GitHubContribFetcher, ContribCard> {
  public:
    GitHubContribAdapter(const GitHubContribFetcher& fetcher)
        : IAdapter<GitHubContribFetcher, ContribCard>(fetcher) {}

    virtual QSharedPointer<ContribCard> adapt() const override {
        // get requirements from fetcher
        auto contributions = m_Adaptee.GetContribs();

        return QSharedPointer<ContribCard>::create(contributions);
    }
};

#endif  // GITHUBCONTRIBADAPTER_HPP

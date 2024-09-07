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
        // create inputs for adaptee
        QDate firstContribDate;

        // get requirements from fetcher
        auto contributions = m_Adaptee.GetContribs();
        auto totalContributions = m_Adaptee.GetTotalContribs();

        if (!contributions.empty()) {
            firstContribDate = contributions.begin()->first;
        }

        return QSharedPointer<ContribCard>::create(contributions, totalContributions, firstContribDate);
    }
};

#endif  // GITHUBCONTRIBADAPTER_HPP

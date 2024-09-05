#ifndef GITHUBCONTRIBADAPTER_HPP
#define GITHUBCONTRIBADAPTER_HPP

#include <memory>

#include "ContribCard.hpp"
#include "ContribTotal.hpp"
#include "GitHubContribFetcher.hpp"
#include "IAdapter.hpp"

class GitHubContribAdapter : public IAdapter<ContribCard> {
  public:
    GitHubContribAdapter(const GitHubContribFetcher& fetcher)
        : m_Fetcher(fetcher) {}

    virtual QSharedPointer<ContribCard> adapt() const override {
        // create inputs for adaptee
        QDate firstContribDate;

        // get requirements from fetcher
        auto contributions = m_Fetcher.GetContribs();
        auto totalContributions = m_Fetcher.GetTotalContribs();

        if (!contributions.empty()) {
            firstContribDate = contributions.begin()->first;
        }

        qDebug() << "firstContribDate" << firstContribDate;

        // todo: totalContributions'ı ContribCard ile kullanılabilir hale getirip parametre olarak ver.
        return QSharedPointer<ContribCard>::create(contributions, firstContribDate);
    }

  private:
    const GitHubContribFetcher& m_Fetcher;
};

#endif  // GITHUBCONTRIBADAPTER_HPP

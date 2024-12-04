#ifndef REPOSITORYCARD_HPP
#define REPOSITORYCARD_HPP

#include <QWidget>

#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"
#include "RepositoryCardConnections.hpp"
#include "Settings.hpp"

namespace Ui {
class RepositoryCardUI;
}

class RepositoryCard : public QWidget {
  public:
    RepositoryCard(QWidget *parent = nullptr);
    ~RepositoryCard();

  private:
    void _LoadRepositories();

  private:
    RepositoryCardConnections *m_Connections;
    GitRepository *m_Repository;
    GitChangeHandler *m_Handler;
    Settings *m_Settings;
    Ui::RepositoryCardUI *m_Ui;
};

#endif  // REPOSITORYCARD_HPP